
#include "tinyxml2.h"

#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <vector>
#include <iostream>
#include <fstream>

using namespace tinyxml2;
using namespace std;

class information
{
public:
    // 析构函数
    ~information()
    {
        std::cout << "~information" << std::endl;
    }

public:
    string title;
    string link;
    string description;
    // string content;
    // string lagnguage;
    // string copyright;
    // string pubdate;
    // string guid;
    // string dccreator;
};

// .dat
void traverse(vector<information> *_vecotr)
{
    std::ofstream _ostream("pagelib.dat", std::ios::app);

    vector<information>::iterator _begin = _vecotr->begin();
    vector<information>::iterator _end = _vecotr->end();

    ++_begin;
    while (_begin != _end)
    {
        _ostream << "<doc>" << endl;
        _ostream << "<title>" << _begin->title << "</title>" << endl;
        _ostream << "<link>" << _begin->link << "</link>" << endl;
        _ostream << "<description>" << _begin->description << "</description>" << endl;
        _ostream << "</doc>" << endl;
        ++_begin;
    }
}

void example1()
{
    vector<information> information_vector;

    XMLDocument doc;
    doc.LoadFile("coolshell.xml");

    cout << doc.Error() << endl;
    if (0 != doc.Error())
    {
        cout << "load file error" << endl;
        return;
    }
    //  doc.Print();

    XMLElement *root = doc.RootElement();
    XMLElement *channel = root->FirstChildElement("channel");
    if (NULL == channel)
    {
        cout << "get first child element error " << endl;
        exit(0);
    }
    XMLElement *item = channel->FirstChildElement("item");
    if (NULL == item)
    {
        cout << "get first child element error " << endl;
        exit(0);
    }
    XMLElement *title = item->FirstChildElement("title");
    cout << title->GetText() << endl;
    cout << title->Name() << endl;
    XMLElement *link = item->FirstChildElement("link");
    cout << link->GetText() << endl;
    cout << link->Name() << endl;
    XMLElement *description = item->FirstChildElement("description");
    cout << description->GetText() << endl;
    cout << description->Name() << endl;

    while (item)
    {
        title = item->FirstChildElement("title");
        cout << title->GetText() << endl;
        cout << title->Name() << endl;
        link = item->FirstChildElement("link");
        cout << link->GetText() << endl;
        cout << link->Name() << endl;
        description = item->FirstChildElement("description");
        cout << description->GetText() << endl;
        cout << description->Name() << endl;
        

        information temp;
        temp.title = title->GetText();
        temp.link = link->GetText();
        temp.description = description->GetText();
        cout << "----------" << temp.title << endl;

        information_vector.push_back(temp);

        item = item->NextSiblingElement("item");
    }
    traverse(&information_vector);
}

// 测试1
int main()
{
    example1();
    return 0;
}

// 测试2:循环获取xml页面内容
// int main(void)
// {
//     XMLDocument doc;
//     doc.LoadFile("coolshell.xml");
//     XMLElement *root = doc.RootElement();
//     XMLElement *channel = root->FirstChildElement("channel");
//     if (NULL == channel)
//     {
//         cout << "get first chile element error " << endl;
//         exit(0);
//     }
//     XMLElement *item = channel->FirstChildElement("item");
//     if (NULL == item)
//     {
//         cout << "get first chile element error " << endl;
//         exit(0);
//     }
//     XMLElement *title = item->FirstChildElement("title");
//     cout << title->GetText() << endl;
//     cout << title->Name() << endl;
//     XMLElement *link = item->FirstChildElement("link");
//     cout << link->GetText() << endl;
//     cout << link->Name() << endl;
//     XMLElement *description = item->FirstChildElement("description");
//     cout << description->GetText() << endl;
//     cout << description->Name() << endl;

//     item = item->NextSiblingElement("item");
//     while (item)
//     {
//         title = item->FirstChildElement("title");
//         cout << title->GetText() << endl;
//         cout << title->Name() << endl;
//         link = item->FirstChildElement("link");
//         cout << link->GetText() << endl;
//         cout << link->Name() << endl;
//         description = item->FirstChildElement("description");
//         cout << description->GetText() << endl;
//         cout << description->Name() << endl;

//         item = item->NextSiblingElement("item");
//     }

//     return 0;
// }
