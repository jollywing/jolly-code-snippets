import unittest

names = ['BaoZheng', 'BaiYuTang', 'BaoBuTong',
         'CaoJiJun', 'CaoCong',
         'DengXing', 'DingNing',
         'FengWanEr', 'FangZuMing',
         'HanLiLi', 'HeXianGu', 'HeZuDao']

def binarySearch(strList, s):
    low = 0
    high = len(strList) - 1
    # low == high的情况发生在寻找第一个元素和最后一个元素时
    while low <= high:
        mid = (low + high) // 2
        print(low, high, mid)
        if strList[mid] == s:
            return mid
        if strList[mid] < s:
            low = mid + 1
        if strList[mid] > s:
            high = mid - 1
    return -1

class TestStringSearch(unittest.TestCase):
    def setUp(self):
        names.sort()
        print(names)

    def testA(self):
        self.assertEqual(2, binarySearch(names, 'BaoZheng'))
        self.assertEqual(-1, binarySearch(names, 'GaoQiu'))
        self.assertEqual(10, binarySearch(names, 'HeXianGu'))
        self.assertEqual(11, binarySearch(names, 'HeZuDao'))

if __name__ == '__main__':
    unittest.main()
