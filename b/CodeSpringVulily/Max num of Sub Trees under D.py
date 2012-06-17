def Solution(dictm):
    #iterate through all subtrees summing the distance of all pairs
    return None

def createBlankDict(N):
    #N is number of nodes
    #N - 1 number of edges
    dictm = {}
    for i in range(N): #0-indexed
        dictm[i] = set()
    return dictm

def addtoDict(a,b,dictm):
    #adds both a->b and b->a
    #a and b are ints
    dictm[a].add(b)
    dictm[b].add(a)
    return dictm

def convLineReadtoInts(strng):
    [first,second] = strng.split()
    return [first,second]


T = int(sys.stdin.readline())

for i in range(0,T):
    N = sys.stdin.readline()
    dictm = {} #reset for new input
    for j in range(N-1):
        #grab values
        #put into data structure
    print Solution()
sys.stdin.readline() #skip a line

