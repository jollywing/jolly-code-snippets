import unittest
from print_stars import print_stars

class SimpleTest(unittest.TestCase):

    def test_print_stars(self):
        a = print_stars(1, 9)
        self.assertEqual(a, (4, 1))
        b = print_stars(5, 9)
        self.assertEqual(b, (0, 9))
        c = print_stars(9, 9)
        self.assertEqual(c, (4, 1))


if __name__ == '__main__':
    unittest.main()
