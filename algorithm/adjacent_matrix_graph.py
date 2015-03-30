
class MatrixGraph(object):
    def __init__(self):
        # init self.vertexs
        self.vertexs = []
        self.vertexs.append(u'朝阳站')       # 0
        self.vertexs.append(u'东城站')       # 1
        self.vertexs.append(u'西城战')       # 2
        self.vertexs.append(u'海淀站')       # 3
        self.vertexs.append(u'丰台站')       # 4
        self.vertexs.append(u'石景山站')     # 5

        # init adjacent matrix of edges
        self.edge_matrix = []
        for i in range(len(self.vertexs)):
            self.edge_matrix.append([])
            for j in range(len(self.vertexs)):
                self.edge_matrix[i].append(0)

        self.edge_matrix[0][1] = 1
        self.edge_matrix[1][0] = 1
        self.edge_matrix[0][4] = 1
        self.edge_matrix[4][0] = 1
        self.edge_matrix[1][2] = 1
        self.edge_matrix[2][1] = 1
        self.edge_matrix[1][4] = 1
        self.edge_matrix[4][1] = 1
        self.edge_matrix[2][3] = 1
        self.edge_matrix[3][2] = 1
        self.edge_matrix[2][4] = 1
        self.edge_matrix[4][2] = 1
        self.edge_matrix[3][4] = 1
        self.edge_matrix[4][3] = 1
        self.edge_matrix[3][5] = 1
        self.edge_matrix[5][3] = 1
        self.edge_matrix[4][5] = 1
        self.edge_matrix[5][4] = 1

class TableGraph(object):
    def __init__(self):
        # init self.vertexs
        self.vertexs = []
        self.edge_table = []
        self.visited = []

    def add_vertex(self, value):
        self.vertexs.append(value)
        self.visited.append(False)
        self.edge_table.append([])

    def add_edge(self, v1, v2):
        self.edge_table[v1].append(v2)
        self.edge_table[v2].append(v1)

    def dfs(self, i):
        self.visited[i] = True
        print('DFS visit: {}'.format(self.vertexs[i]))
        for vex in self.edge_table[i]:
            if not self.visited[vex]:
                self.dfs(vex)

    # 类似于树的前序遍历
    def dfs_tranverse(self):
        for i in range(len(self.vertexs)):
            self.visited[i] = False

        for i in range(len(self.vertexs)):
            if not self.visited[i]:
                self.dfs(i)

    # 类似于树的层序遍历
    def bfs_tranverse(self):
        for i in range(len(self.vertexs)):
            self.visited[i] = False

        for i in range(len(self.vertexs)):
            if not self.visited[i]:
                tran_queue = []
                tran_queue.append(i)
                while len(tran_queue) > 0:
                    id = tran_queue[0]
                    if not self.visited[id]:
                        print('BFS visit: {}'.format(self.vertexs[id]))
                        self.visited[id] = True
                        for v in self.edge_table[id]:
                            tran_queue.append(v)
                    del tran_queue[0]

# 针对有向图的十字链表
class OrthogonalListGraph(object):
    def __init__(self):
        self.vertexs = []
        self.edges = []

    def add_vertex(self, value):
        v = OrthoListVertex(value)
        self.vertexs.append(v)

    def add_edge(self, tail, head):
        e = OrthoListEdge(tail, head)
        e.head_link = self.vertexs[e.head].first_in
        self.vertexs[e.head].first_in = e
        e.tail_link = self.vertexs[e.tail].first_out
        self.vertexs[e.tail].first_out = e
        self.edges.append(e)

    def out_degree(self, index):
        edge = self.vertexs[index].first_out
        c = 0
        while edge != None:
            c += 1
            edge = edge.tail_link
        return c

    def in_degree(self, index):
        edge = self.vertexs[index].first_in
        c = 0
        while edge != None:
            c += 1
            edge = edge.head_link
        return c

    def print_degree(self):
        for i in range(len(self.vertexs)):
            print('{}. out: {}; in: {}'.format(self.vertexs[i].data,
                                               self.out_degree(i),
                                               self.in_degree(i)))

class OrthoListEdge(object):
    def __init__(self, _tail, _head):
        self.tail = _tail
        self.head = _head
        self.head_link = None
        self.tail_link = None

class OrthoListVertex(object):
    def __init__(self, _value):
        self.data = _value
        self.first_in = None
        self.first_out = None


if __name__ == '__main__':
    g = MatrixGraph()
    print(g.vertexs)
    print(g.edge_matrix)

    g2 = TableGraph()
    g2.add_vertex(u'朝阳站')       # 0
    g2.add_vertex(u'东城站')       # 1
    g2.add_vertex(u'西城战')       # 2
    g2.add_vertex(u'海淀站')       # 3
    g2.add_vertex(u'丰台站')       # 4
    g2.add_vertex(u'石景山站')     # 5

    g2.add_edge(0, 1)
    g2.add_edge(0, 4)
    g2.add_edge(1, 2)
    g2.add_edge(1, 4)
    g2.add_edge(2, 3)
    g2.add_edge(2, 4)
    g2.add_edge(3, 4)
    g2.add_edge(3, 5)
    g2.add_edge(4, 5)

    print(g2.vertexs)
    print(g2.edge_table)

    g2.dfs_tranverse()
    g2.bfs_tranverse()

    #    +---------+
    #    |         | 
    #    v         |
    #    A--->B--->D
    #    |    |
    #    |    v
    #    +--->C
    g3 = OrthogonalListGraph()
    g3.add_vertex('A')
    g3.add_vertex('B')
    g3.add_vertex('C')
    g3.add_vertex('D')

    g3.add_edge(0, 1)
    g3.add_edge(0, 2)
    g3.add_edge(1, 2)
    g3.add_edge(1, 3)
    g3.add_edge(3, 0)
    g3.print_degree()

    #    +----E----+
    #    |         | 
    #    |         |
    #    A----B----D
    #    |    |
    #    |    |
    #    +----C
