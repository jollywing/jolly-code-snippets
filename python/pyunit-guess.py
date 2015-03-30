import unittest
import random

class GuessGame:
    def __init__(self, minNum, maxNum):
        self.answer = random.randint(minNum, maxNum)
        self.lowBound = minNum
        self.upBound = maxNum
        self.guessTime = 0

    def check(self, n):
        if self.answer > n:
            return 'too little.'
        elif self.answer < n:
            return 'too large.'
        else:
            return 'bingo!'

    def run(self):
        print 'I have decided a number[%d, %d], you guess!'%(self.lowBound, self.upBound)
        while True:
            try:
                self.guessTime += 1
                inputAnswer = int(raw_input('(%d)Give your answer: ' % self.guessTime))
                result = self.check(inputAnswer)
                print result
                if result == 'bingo!':
                    break
            except ValueError:
                print 'Please input valid number, fool!'

class TestGuessGame(unittest.TestCase):
    def setUp(self):
        self.game = GuessGame(10, 100)

    def testA(self):
        result = self.game.check(9)
        self.failUnless(result == 'too little.')

    def testB(self):
        result = self.game.check(101)
        self.failIf(result == 'bingo!')

# unittest.main()
game = GuessGame(0, 100)
game.run()
