# numpy的使用
# 从文件中读取每个数据
import numpy
world_alcohol = numpy.genfromtxt("123.txt",delimiter=",",dtype=str)
print("---------------------------")
print (type(world_alcohol))
print("---------------------------")
# 把他当成一个矩阵就可以了
print( world_alcohol)
# help（函数接口）得到使用该接口的例子
# print (help(numpy.genfromtxt))

# numpy.array() 插入数据，自动转换格式
# 插入一维数组
vec = numpy.array([1,2,3,4,])
# 插入二维数组
mat = numpy.array([[1,2,3,4],[2,3,4,5],[3,4,5,6]])
print(vec)
print(mat)

# .shape 是看结构的,几行几列
print(vec.shape)
print(mat.shape)

# numpy.array()里面的数据都必须是相同的类型
print (vec.dtype)   #int32

# 索引取数据，每一行是一个索引
# 切片--取部分数据
print(vec[0:3])
# 冒号代表是所有的
print (mat[:,1])
# 判断每个元素
mat == 1
print(mat == 1)
epual_to_one = (vec == 1)
# 使用bool类型当索引
print (epual_to_one)
print( vec[epual_to_one])
second_epl_2 = (mat[:,1] == 2)
print(second_epl_2)
print(mat[second_epl_2,:])

# 取判读的操作
# 查看一个值是否即等于1又等于2
epual_to_one_and_two = (vec == 1)&(vec == 2)
print(epual_to_one_and_two)
epual_to_one_or_two = (vec == 1)|(vec == 2)
print(epual_to_one_or_two)

# 改变数据类型
vec2 = numpy.array(["1","2","3"])
# 查看数据类型
print (vec2.dtype)
print( vec2)
# 改变数据类型
vec2 = vec2.astype(int)
# 再查看一下数据类型
print( vec2.dtype)
print( vec2)

# 对数据进行计算
# 打印最小值
print(vec2.min())
# 求和--按行或者按列来求和 最好是二维数组，一维数组里面是不行的
# axis指的是一个维度
# 求行和
print("打印VEC--------------------------")
vec3 = numpy.array([[1,1,1],[2,2,2],[3,3,3],[4,4,4]])
print(vec3)
print("行求和---------------------------")
print(vec3.sum(axis=1))
# 求列和
print("列求和---------------------------")
print(vec3.sum(axis=0))


# 矩阵变换
# 顺序生成一维向量
print("顺序生成一维向量--------------------------")
print(numpy.arange(15))
# 做成指定行列的矩阵，指定矩阵的维度
print("顺序生成一维向量，然后划分为指定行列的矩阵---------------")
a = numpy.arange(15).reshape(3,5)
print(a)
print(a.shape)
# 打印矩阵的维度
print("打印矩阵的维度---------------------")
print(a.ndim)


# 矩阵的初始化操作
# 初始化一个零矩阵
print("初始化一个3行4列的0矩阵-----------")
# 初始化1个3行4列的矩阵，传入的是元组的格式
b = numpy.zeros((3,4))
# 打印矩阵
print(b)

# 使用别名
print("生成2个3行4列的1矩阵-------------------------")
import numpy as np
# 2个3行4列的矩阵，类型是整形的
c = np.ones((2,3,4),dtype= np.int32)
print(c)

# 利用每隔几个数字相加来构造矩阵
print("每隔3个数字相加来得到矩阵--------------------")
# 10,13,16,19
d = np.arange(10,30,3)
print(d)

# 得到一个序列然后直接构造出矩阵
print("造一个序列，然后直接造出矩阵------------------")
e = np.arange(10).reshape(2,5)
print(e)

# 随机元素的生成
print("随机数字生成指定规模的矩阵--------------------")
# 先进入random模块，然后再调用random函数
# 做一些随机权重的元素的矩阵
f = np.random.random((2,3))
# 默认是从-1到1区间上的值
print(f)


#平均去取数字
# pi是一个已经有的数字3.14
from numpy import pi
print("从0到2*pi用中间，平均的取20个值----------------------")
# 从0到2*pi用中间，平均的取20个值
g = np.linspace(0,2*pi,20)
print(g)

# 数学运算
h = np.array([1,2,3,4])
i = np.arange(4)
print("打印h")
print(h)
print("打印i")
print(i)
print("矩阵的加减法,对应位置相减---------------------")
g = h - i
print(g)
g = g - 1
print(g)
print("矩阵的乘法，平方-----------------------------")
# 乘以2再乘以2，求平方的操作
print(h**2)
# 每个位置的数值跟3进行对比
print(i<3)


# 矩阵的乘法运算
A = np.array([[1,2],[2,3]])
B = np.array([[3,4],[4,5]])
print("A--------------------------------")
print(A)
print("B--------------------------------")
print(B)
print("A*B--矩阵的乘法-----------------")
# 计算内积
print(A*B)
print("A.dot(B)--矩阵的乘法-------------------")
#矩阵的乘法 2种表达方法
print(A.dot(B))
# print(help(np.dot))

# 幂和根号的表达
C = np.arange(3)
print("B---------------------------------")
print(B)
print("幂运算----------------------------")
print(np.exp(B))
print("开根号运算------------------------")
print(np.sqrt(B))


# 矩阵的运算
# floor是向下取正的操作
a = np.floor(10*np.random.random((3,4)))
print("先打印A矩阵-----------------------")
# 会向下取整
print(a)
print("把矩阵拉成一个向量-----------------")
# 把一个矩阵拉成一个向量
print(a.ravel())
print("把拉直的向量，再弄成6行2列的矩阵-------")
a.shape = (6,2)
print(a)
print("把A矩阵转置一下，打印出来------------")
print(a.T)

# 矩阵的拼接
print("矩阵的拼接。横向的拼接。")
a1 = np.floor(10*np.random.random((2,2)))
b1 = np.floor(10*np.random.random((2,2)))
print("打印a1----------------------------")
print(a1)
print("打印b1----------------------------")
print(b1)
print("拼接矩阵(横向拼接)--------------------------")
# 横向拼接
print(np.hstack((a1,b1)))

# 切分矩阵
print("矩阵的切分----------------------")
a2 = np.floor(10 * np.random.random((2,12)))
print("打印一下a2----------------------")
print(a2)
print("按列进行拆分--------------------")
# 把a2切分成3*4的矩阵
print(np.hsplit(a2,3))
# 在a2的2位置和4位置各切一刀
# print(np.hsplit(a2,(2,4,6,8)))

a2 = np.floor(10 * np.random.random((12,2)))
print("打印一下新构造的的a2----------------------")
print(a2)
print("打印一下切分后的数组 ------------")
print(np.vsplit(a,3))

#矩阵的复制
# 方法1
print("矩阵的复制--------------------")
a3 = np.arange(12)
b3 = a3
print(b3 is a3)
# 把b改成3行4列的矩阵
b3.shape =(3,4)
# a会同步更改
print(a3.shape)
# 打印两个矩阵的内存值
print(id(a3))
print(id(b3))

# 方法2
print("方法2------------------------")
c3 = a3.view()
print(c3 is a3)
c3.shape = 2,6
print(a3.shape)
c3[0,4] = 1234
print(a3)
# 指向的是不同的区域，但是使用的值是一样的
print("--------------")
print(c3)
# 打印id
print(id(a3))
print(id(c3))


# 方法3
print("方法3----------------")
# 各自不同的内存空间
d3 = a3.copy()
print(d3 is a3)
d3[0,0] = 9999
print(a3)
print("---------------------")
print(d3)

# 排序和索引
print("排序和索引--------------------")
data = np.sin(np.arange(20)).reshape(5,4)
print(data)
# 找到每一列最大的值，然后拿到索引号
ind = data.argmax(axis = 0)
print(ind)

# 通过index然后每一列拿到最大的那个数值，放到data_max里面
data_max = data[ind,range(data.shape[1])]
print(data_max)


# 矩阵的扩展
print("矩阵的扩展-------------------")
# 从0到40,每10个数字取一个
a4 = np.arange(0,40,10)
print(a4)
# a4的行是原来的3倍，列是原来的5倍
b4 = np.tile(a4,(3,5))
print("-------------------------")
print(b4)

# 排序

print("排序")
a5 = np.array([[1,5,3],[9,3,4]])
print(a5)
print("-----------")
# 拿到a5,然后每一行进行排序，然后重新组成一个新的矩阵
b5 = np.sort(a5,axis=1)
print(b5)

a5.sort(axis=1)
print("---------------")
print(a5)
print("第二种排序-------")
a5 = np.array([4,3,2,1])
# 取最小值的索引，然后再取第二小的索引，再取第三小的索引
j = np.argsort(a5)
print(a5)
print("------------")
print(j)
print("------------")
print(a5[j])

# numpy的基础操作到此结束
print("\n "
      "numpy的基础操作到此结束")

