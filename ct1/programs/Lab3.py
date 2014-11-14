
from ParseTree import Node

#Q4 
def makeParseTreePM (s):

    previousNode = None
 

    for i in s[1::2]:
        n = Node(i)
        
        
        r = Node (s[s.index(i)+1])
        n.setRight(r)
        
        if previousNode == None:
            l = Node (s[s.index(i)-1])
            n.setLeft (l)
        else:
            n.setLeft (previousNode)
        previousNode = n

##    print (n.getData())

    return n







#Q5 

def makeParseTreeMD (s):

    previousNode = None
 

    for i in s[1::2]:
        n = Node(i)
        
        
        r = Node (s[s.index(i)+1])
        n.setRight(r)
        
        if previousNode == None:
            l = Node (s[s.index(i)-1])
            n.setLeft (l)
        else:
            n.setLeft (previousNode)
        previousNode = n

    print (n.getData())

    return n


def infix(n):
    
    if n.getLeft():
        infix(n.getLeft()) 
    print (n.getData())
    if n.getRight():
        infix(n.getRight())


#Q 6
def prefix (n):

    print (n.getData())

    if n.getLeft():
        prefix(n.getLeft()) 
    
    if n.getRight():
        prefix(n.getRight())

##def evaluatePM (s):
##
##    st = "".join(s)
##    eval(st)
##
##def evaluateMD (s):
##
##    st = "".join(s)
##    eval(st)
##    

        
                
