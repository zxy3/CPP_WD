# 先把脚本调出来
# 包或者脚本文件
# tang.py是python的脚本文件
tang_v = 10

def tang_add(tang_list):
    tang_sum = 0
    for i in range(len(tang_list)):
        tang_sum += tang_list[i]
#         每执行一步，看一下结果
        print(tang_sum)
    return tang_sum
# list
tang_list = [1,2,3,4,5]
# 执行函数，看下结果
print (tang_add(tang_list))
