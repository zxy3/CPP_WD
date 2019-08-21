///
/// @file    EventLoop.cc
/// @author  lemon(haohb13@gmail.com)
/// @date    2019-05-08 11:06:33
///
#include "EventLoop.h"
#include "Acceptor.h"
#include "TcpConnection.h"

#include <assert.h>

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{
// 生命周期用eventloop来控制
EventLoop::EventLoop(Acceptor &acceptor)
	: _efd(createEpollFd()), _acceptor(acceptor), _eventList(1024), _isLooping(false)
{
	// 1024 vector中构造函数会创建1024个元素
	addEpollFdRead(_acceptor.fd());
}
// wait fd
void EventLoop::loop()
{
	_isLooping = true;
	while (_isLooping)
	{
		waitEpollFd();
	}
}

void EventLoop::unloop()
{
	if (_isLooping)
		_isLooping = false;
}

void EventLoop::waitEpollFd()
{
	int nready;
	// 中断信息不管他
	do
	{
		nready = epoll_wait(_efd, &*_eventList.begin(), _eventList.size(), 5000);
	} while (nready == -1 && errno == EINTR);

	if (nready == -1)
	{
		perror("epoll_wait");
		return;
	}
	else if (nready == 0)
	{
		cout << ">> epoll_wait timeout!" << endl;
	}
	else
	{
		// 轮询处理
		if (nready == _eventList.size())
		{
			_eventList.resize(2 * nready);
		}

		for (int idx = 0; idx != nready; ++idx)
		{
			int fd = _eventList[idx].data.fd;
			if (fd == _acceptor.fd())
			{
				//处理新连接
				if (_eventList[idx].events & EPOLLIN)
				{
					handleNewConnection();
				}
			}
			else
			{
				//处理消息
				if (_eventList[idx].events & EPOLLIN)
				{
					handleMessage(fd);
				}
			}
		}
	}
}

void EventLoop::handleNewConnection()
{
	int peerfd = _acceptor.accept();
	addEpollFdRead(peerfd);
	TcpConnectionPtr conn(new TcpConnection(peerfd));
	conn->setConnectionCallback(_onConnection);
	conn->setMessageCallback(_onMessage);
	conn->setCloseCallback(_onClose);

	_conns.insert(std::make_pair(peerfd, conn));

	conn->handleConnectionCallback();
}

void EventLoop::handleMessage(int fd)
{
	bool isClosed = isConnectionClosed(fd);
	auto iter = _conns.find(fd);
	assert(iter != _conns.end()); //运行时断言

	if (!isClosed)
	{
		iter->second->handleMessageCallback();
	}
	else
	{
		delEpollFdRead(fd);
		iter->second->handleCloseCallback();
		_conns.erase(iter);
	}
}

bool EventLoop::isConnectionClosed(int fd)
{
	int ret;
	do
	{
		char buff[1024];
		ret = recv(fd, buff, sizeof(buff), MSG_PEEK);
	} while (ret == -1 && errno == EINTR);

	return (ret == 0);
}

int EventLoop::createEpollFd()
{
	// 创建一个文件描述符
	int ret = ::epoll_create1(0);
	if (ret == -1)
	{
		perror("epoll_create1");
	}
	return ret;
}

void EventLoop::addEpollFdRead(int fd)
{
	// 传递一个文件描述符
	struct epoll_event evt;
	evt.data.fd = fd;
	evt.events = EPOLLIN;
	int ret = epoll_ctl(_efd, EPOLL_CTL_ADD, fd, &evt);
	if (-1 == ret)
	{
		perror("epoll_ctl");
	}
}

void EventLoop::delEpollFdRead(int fd)
{
	// 删除一个文件描述符
	struct epoll_event evt;
	evt.data.fd = fd;
	int ret = epoll_ctl(_efd, EPOLL_CTL_DEL, fd, &evt);
	if (-1 == ret)
	{
		perror("epoll_ctl");
	}
}
} //end of namespace wd



// ----- 网络编程中会涉及到3个半事件 ---- 用回调函数完成另外一半事件
// 当新连接到来时做什么事情(半个事件)
// 当信息到达时(半个事件)
// 当连接关闭时(半个事件)
// 当消息发送完成时(半个事件)

// 尾函数：挖空 定制化的操作？
// 回显操作？
// 辅助类？