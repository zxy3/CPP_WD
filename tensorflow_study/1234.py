# -*- coding: UTF-8 -*-

"""
用梯度下降的优化方法来快速解决线性回归问题
"""

import numpy as np
import matplotlib.pyplot as plt
import tensorflow as tf

try:
    xrange = xrange  # Python 2
except:
    xrange = range   # Python 3

# 构建数据
points_num = 100
vectors = []
# 用 Numpy 的正态随机分布函数生成 100 个点
# 这些点的（x, y）坐标值对应线性方程 y = 0.1 * x + 0.2
# 权重（Weight）为 0.1，偏差（Bias）为 0.2
for i in xrange(points_num):
    x1 = np.random.normal(0.0, 0.66)
    y1 = 0.1 * x1 + 0.2 + np.random.normal(0.0, 0.04)
    vectors.append([x1, y1])

x_data = [v[0] for v in vectors]  # 真实的点的 x 坐标
y_data = [v[1] for v in vectors]  # 真实的点的 y 坐标

# 图像 1 ：展示 100 个随机数据点
plt.plot(x_data, y_data, 'r*', label="Original data")  # 红色星形的点 label是数据解释
plt.title("Linear Regression using Gradient Descent")  # 是表头
plt.legend()
# 展示图像
plt.show()