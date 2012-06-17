import sys

def BFSolve(N):
    #Find maximum sum of adjacent products for a consecutive string of numbers,
    #1 through N

    #@param N input size
    #@returns integer solution to problem statement
    A = []
    A = BFArr(N)
    return BFSum(A)

def BFSum(A):
    #input A: list of numbers
    #return: adjacent sum of products
    
    runSum = 0
    for i in range(0,len(A)-1): #travel from first to next to last element
        runSum += A[i]*A[i+1]
    return runSum

def BFArr(N):
    #input: N: 1 to N need to be arranged
    #return: arrangement
    A = []
    A = SnakeWindArr(N)
    return A

def SnakeWindArr(N):
    #create arrangement of 1 to N based on snake wind algorithm
    A = []
    flipFlop = True;
    for i in range(N,0,-1): #from N to 1 inclusively
        if flipFlop == True:
            A.append(i)
            flipFlop = False
            continue
        if flipFlop == False:
            A.insert(0,i)
            flipFlop = True
            continue
    return A
        
    
    


##for line in iter(sys.stdin.readline,''):
##    print 'it says: ', line

T = int(sys.stdin.readline())
    
for i in range(0,T):
    N = int(sys.stdin.readline())
    print BFSolve(N)
    
