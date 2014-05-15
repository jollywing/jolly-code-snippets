
latency_matrix = []

NODE_CNT = 100

for k in range(NODE_CNT):
    latency_matrix.append([])
    for n in range(NODE_CNT):
        latency_matrix[k].append(0)

def load_matrix():
    f = open("simplified-matrix.dat", 'r')

    while 1:
        s = f.readline()
        if s == '' :
            break
        fields = s.split()
        peer1 = int(fields[0])
        peer2 = int(fields[1])
        latency = int(fields[2]) / 2
        if peer1 >= NODE_CNT:
            break;
        if peer2 < NODE_CNT:
            latency_matrix[peer1][peer2] = latency
            latency_matrix[peer2][peer1] = latency

    f.close()

load_matrix()

print latency_matrix[1]

