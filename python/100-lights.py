# 有１００盏灯，编号从１－１００，
# 第一次，把所有编号是１的倍数的灯开关状态改变一次
# 第二次，把所有编号是２的倍数的灯开关状态改变一次
# 第三次，把所有编号是３的倍数的灯开关状态改变一次
# ……
# 第１００次，把所有编号是１００的倍数的灯开关状态改变一次
# 求所有亮着的灯的编号

l = [0] * 100
for i in range(100):
    for j in range(100):
        if (i + 1) % (j + 1) == 0:
            if l[i] == 0:
                l[i] = 1
            else:
                l[i] = 0

lighted = []
for i in range(100):
    if l[i] == 1:
        lighted.append(i+1)

print(lighted)
