import unittest

class SimpleTest(unittest.TestCase):

    def test_list(self):
        a = Simple(2)
        self.assertEqual(a.get_id(), 2)

class Simple(object):
    def __init__(self, id):
        self.id = id

    def get_id(self):
        return self.id

if __name__ == '__main__':
    unittest.main()
