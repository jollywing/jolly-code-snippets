
import unittest
from stock import *

class StockTest(unittest.TestCase):
    def test_sqlite_open(self):
        r = sqlite_open('stock.db')
        self.assertEqual(r, True)

if __name__ == '__main__':
    unittest.main()
