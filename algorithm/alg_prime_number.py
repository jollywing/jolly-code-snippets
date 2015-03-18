import unittest
from math import sqrt, ceil, floor
# ceil return integer larger than x, floor return integer smaller than x
def is_prime(n):
    if n <= 0:
        return False

    m = int(ceil(sqrt(n)))
    for i in range(2, m):
        if n % i == 0:
            return False
    return True

class TestPrime(unittest.TestCase):
    def test_sqrt(self):
        self.assertEqual(sqrt(16), 4)
        # sqrt will return float number
        self.assertEqual(floor(sqrt(17)), 4)

    def test_prime_function(self):
        self.assertEqual(is_prime(2), True)
        self.assertEqual(is_prime(17), True)
        self.assertEqual(is_prime(100), False)
        self.assertEqual(is_prime(0), False)

if __name__ == '__main__':
    unittest.main()
    
