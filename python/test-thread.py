import threading
import time

def count_down(n):
    if n < 0:
        n = -n
    while n > 0:
        n -= 1
        time.sleep(0.2)

def test_new_thread():
    t = threading.Thread(target=count_down, name='thread-countdown',
                         args=(10,))
    t.start()
    t.join()

def test_multi_thread():
    t = threading.Thread(target=count_down, name='thread-countdown',
                         args=(100,))
    t.start()

    s = 'Hello, word!'
    for c in s:
        print c,
        time.sleep(0.5)
    print ''
    if t.isAlive():
        print 'thread-countdown is still running.'

if __name__ == '__main__':
    # test_new_thread()
    test_multi_thread()
