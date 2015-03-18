
MAX_SIZE = 10

class SortList:
    def __init__(self):
        self.elems = []

    def add_elems(self, new_el_list):
        self.elems += new_el_list

    def print_elems(self):
        print(self.elems)

    def swap_elem(self, i, j):
        if i < 0 or i >= len(self.elems): return
        if j < 0 or j >= len(self.elems): return
        if i == j: return

        t = self.elems[i]
        self.elems[i] = self.elems[j]
        self.elems[j] = t

    def bubble_sort_1(self):
        l = len(self.elems)
        for i in range(0, l - 1):
            for j in range(i + 1, l):
                if self.elems[i] > self.elems[j]:
                    self.swap_elem(i, j)

    def bubble_sort_2(self):
        l = len(self.elems)
        for i in range(0, l):
            flag = False
            for j in range(l - 1, i, -1):
                if self.elems[j - 1] > self.elems[j]:
                    self.swap_elem(j - 1, j)
                    flag = True

            if not flag: break


    def selection_sort(self):
        l = len(self.elems)
        for i in range(0, l - 1):
            min = i
            for j in range(i + 1, l):
                if self.elems[j] < self.elems[min]:
                    min = j
            if i != min:
                self.swap_elem(i, min)

    def insertion_sort(self):
        l = len(self.elems)
        for i in range(1, l):
            if self.elems[i] < self.elems[i - 1]:
                t = self.elems[i]
                for j in range(i - 1, -1, -1):
                    if self.elems[j] > t:
                        self.elems[j + 1] = self.elems[j]
                    else:
                        break
                if j == 0:
                    if self.elems[0] > t:
                        self.elems[0] = t
                else:
                    self.elems[j + 1] = t

    # shell sorting
    def shell_sort(self):
        l = len(self.elems)
        increment = l
        while increment > 1:
            increment = increment // 3 + 1
            for i in range(increment, l):
                if self.elems[i] < self.elems[i - increment]:
                    t = self.elems[i]
                    for j in range(i - increment, -1, -increment):
                        if t > self.elems[j]:
                            j += increment
                            break
                        self.elems[j + increment] = self.elems[j]
                    self.elems[j] = t

sl = SortList();
sl.add_elems([1, 1000, 200, 255, 122]);
sl.bubble_sort_1()
sl.print_elems()

sl.add_elems([55])
sl.bubble_sort_2()
sl.print_elems()

sl.add_elems([99])
sl.selection_sort()
sl.print_elems()

sl.add_elems([-100])
sl.insertion_sort()
sl.print_elems()

sl.add_elems([445, 23])
sl.shell_sort()
sl.print_elems()
