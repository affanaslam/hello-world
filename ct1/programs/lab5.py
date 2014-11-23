# Lab 5: Huffman Coding
# ID 1: sa00310
# ID 2: 

from Huffman import Node
from queue import PriorityQueue
import collections

##### Base conversion

### Problem 9
def invBin(num):
    '''(str) -> int
    
    Returns a decimal number corresponding to the binary number
    represented as num.

    >>> invBin('1011')
    11
    '''
    return int(num,2)

def invHex(num):
    '''(str) -> int
    
    Returns a decimal number corresponding to the hexadecimal number
    represented as num.

    >>> invHex('5A')
    90
    '''
    return int(num,6)

def invOct(num):
    '''(str) -> int
    
    Returns a decimal number corresponding to the octal number
    represented as num.

    >>> invOct('27')
    23
    '''
    return int(num,8)


### Problem 10
def invInt(num, base):
    '''(int, int) -> str
    
    Returns a string containing the number corresponding to the
    decimal number, num, in the number system with the given
    base. base may be any of 2, 8, 10 or 16 only.

    >>> invInt(34, 10)
    '34'
    >>> invInt(17, 2)
    '10001'
    >>> invInt(25, 16)
    '19'
    >>> invInt(110, 8)
    '156'
    '''
    if base==2:
        return bin(num)[2:]
    if base==8:
        return oct(num)[2:]
    if base==10:
        return str(num)
    if base==16:
        return hex(num)[2:]

##### File I/O

### Problem 11
def copyFile(fname):
    
    with open(fname, 'r') as f:
	    data= f.read()
    with open (fname[-5::-1][::-1]+ '_copy.txt', 'w') as d:
	    d.write(data)
    print (fname[-5::-1][::-1]+ '_copy.txt')
    
    '''(str) -> str


    Returns the path to a file created such that its contents are a
    copy of the contents of the file with path, fname. The name is
    derived from fname by appending '_copy' to the name of the file in
    fname.

    >>> copyFile('foo.txt')
    'foo_copy.txt'
    '''
   

### Problem 12
def areIdentical(fname1, fname2):

    with open (fname1, 'r') as f1:
        data1 = f1.read()
    with open (fname2, 'r') as f2:
        data2 = f2.read()
    if data1 == data2:
        return True
    else:
        return False

    
    '''(str, str) -> bool

    Returns True if the contents of the files with paths fname1 and
    fname2 are identical, False otherwise.

    >>> areIdentical('foo.txt', 'foo.txt')
    True
    >>> areIdentical('Liberal_Core-Reading_1.txt', 'Think_Python-Chapter_3.txt')
    False
    '''
    pass


### Problem 13
def hexcopyFile(fname):
    '''(str) -> str

    Returns the path to a file created such that it contains two bytes
    representing the hex code of the corresponding byte in the file
    with path, fname. The name is derived from fname by appending
    '_copy' to the name of the file in fname.

    >>> hexcopyFile('foo.txt')
    'foo_hexcopy.txt'
    '''
    F1=open(fname,'rb')
    F2=open(fname[:-4]+'_hexcopy.txt','w')
    R_F1=F1.read()
    for i in R_F1:
        if len(hex(i)[2:])==1:
            F2.write('0'+hex(i)[2:])
        else:
            F2.write(hex(i)[2:])
    F2.close()
    return fname[:-4]+'_hexcopy.txt'

### Problem 14
def unhexFile(fname):
    '''(str) -> str

    Returns the path to a newly created file whose bytes are obtained
    by interpreting successive pairs of characters in the file with
    path, fname, as an ASCII hex code. The name is derived from fname
    by appending '_unhexed' to the name of the file in fname.

    >>> unhexFile('foo_hexcopy.txt')
    'foo_hexcopy_unhexed.txt'
    '''
    F1=open(fname,'r')
    F2=open(fname[:-4]+'_unhexed.txt','w')
    R_F1=F1.read()
    R_F1=R_F1.replace('0d','')
    Byte=[]
    for i in R_F1:
        if len(R_F1)==0:
            break
        Byte.append(R_F1[:2])
        R_F1=R_F1[2:]
    for i in Byte:
        Hex=Byte.pop(0)
        if Hex[0]=='0':
            Hex=Hex[-1]
        Byte.append(chr((int((Hex),16))))
    Byte=list_to_Str(Byte)
    F2.write(Byte)
    F2.close()
    return fname[:-4]+'_unhexed.txt'

### Problem 15
def isHexingWorking(fname):
    '''(str) -> bool

    Returns True if the functions unhexFile and hexcopyFile are
    inverses of each other for the file with path, fname, False
    otherwise.
    '''
    F1=open(unhexFile(hexcopyFile(fname)),'r')
    F2=open(fname,'r')
    Q=F1.read()
    W=F2.read()
    return (Q==W)# F(G(x))=x 


##### Letter Counting

### Problem 16
def getLetterFrequencies(text):

    return collections.Counter(text)
    '''(str) -> dict

    Returns a dictionary with (str, int) pairs representing the
    letters and their frequencies in text.

    >>> getLetterFrequencies('Hello World!')
    {'l': 3, 'W': 1, 'r': 1, 'e': 1, '!': 1, 'd': 1, 'H': 1, ' ': 1, 'o': 2}
    >>> getLetterFrequencies('print is not return.')
    {'e': 1, 't': 3, 'r': 3, ' ': 3, 'u': 1, 's': 1, 'n': 3, 'p': 1, '.': 1, 'i': 2, 'o': 1}
    '''

### Problem 17
def getFrequencies(fname):

    with open (fname, 'r') as f:
        data = f.read().replace(" ","")
    return collections.Counter(data)
    '''(str) -> dict

    Returns a dictionary with (str, int) pairs representing the
    letters and their frequencies in the file with path, fname.
    '''
    

### Problem 18
    def printFrequencyHistogram(text):
        
            freq_lst = []
            ast = "*"
            letters = collections.Counter(text)
            for key,value in letters.items():
                    freq_lst.append(value)
            freq = collections.Counter(freq_lst)
            for key2,value2 in freq.items():
                    print (key2, " ", ast*value2)


    
    

    
    '''(str) -> None

    Prints a histogram of the frequencies with which letters appear in
    text.

    >>> printFrequencyHistogram('print is not return')
    1 *****
    2 *
    3 ****
    '''
    

##### Node and PriorityQueue

### Problem 19
def makePQ(d):

    
    
    pq = PriorityQueue()

    for key,value in d.items():
        pq.put(key,value)
    return pq
   
    

    
    '''(dict) -> PriorityQueue

    Returns a priority queue containing Node objects corresponding to
    the entries in d.
    '''
    

### Problem 20
def showLetters(fname):
    '''(str) -> None

    Prints the letters contained in the file with path, fname, in
    order of increasing frequency.
    '''
    A=getFrequencies(fname)
    A=dict_to_list(A)
    A=i_to_k(A)
    A.sort()
    A=k_of_tuple(A)
    A=list_to_Str(A)
    print(A)
    #  the code can be shorted to one line, maybe 
    #print (list_to_Str(k_of_tuple(i_to_k(dict_to_list(getFrequencies(fname))).sort())))
    
    

##### Trees

### Problem 21
def makeTree():

    

    n = Node('a', 1)
    n.setLeft(Node('b',2))
    n.setRight(Node('c',5))
    L = n.getLeft()
    L.setLeft(Node('d',4))
    L.setRight(Node('e',7))
    G = n.getRight()
    G.setLeft(Node('f', 1))
    G.setRight(Node('g',4))
    return n

### Problem 22
def getCodes(node):
    '''(Node) -> dict

    Returns a dict with (str, str) pairs with each pair containing the
    data of a leaf node of the tree rooted at node and its code.
    '''
    list1=[(node,'')]
    list2=[]
    while len(list1)>0:
        T=list1.pop(-1)
        if check(T[0])==True and T[0]!=None:
            list1.append((Goright(T[0]),T[1]+'1'))
            list1.append((Goleft(T[0]),T[1]+'0'))
        if T[0]!=None and T[0].isLeaf()==True:
            list2.append((T[0].getData(),T[1]))
    return list_to_dict(list2)
    
    

### Problem 23
def writeCodes(node, fname):
    '''(Node, str) -> None

    Writes the code table corresponding to the tree rooted at node in
    ascending order of code length to the file with path, fname.
    '''
    Codes=getCodes(node)
    Codes=Sort_codes(Codes)
    CodeFile=open(fname,'w')
    for i , k in Codes:
        CodeFile.write( (i)+"\t"+(k)+"\n")
    CodeFile.close()
    return fname # for the sake  of comparision it returns the path

### Problem 24
def readCodes(fname):
    '''(str) -> Node

    Returns the root of the tree corresponding to the code table read
    from the file with path, fname.
    '''
    File=open(fname,'r')
    Read=File.read()
    List=Table_to_list(Read)
    Rroot=Node('','')
##    root=Node('','')
    for i,k in List:
        root=Rroot
        for q in k:
            if q=='0' and (root.getLeft()==None):
                empty=Node('','')
                root.setLeft(empty)
                root=Goleft(root)
            if q=='0' and (root.getLeft()!=None):
                root=Goleft(root)
            if q=='1' and (root.getRight()==None):
                empty=Node('','')
                root.setRight(empty)
                root=Goright(root)
            if q=='1' and (root.getRight()!=None):
                root=Goright(root)
        Variable=root.getParent()
        if k[-1]=='0':
            Variable.setLeft(Node(i,''))
        if k[-1]=='1':
            Variable.setRight(Node(i,''))
        root=Rroot
    File.close()
    return root


### Problem 25
def readCodesBinary(fname):
    '''(str) -> Node

    Returns the root of the tree corresponding to the code table read
    from the file with path, fname.
    '''
    File=open(fname,'rb')
    read=File.read()
    Read=''
    for i in read:
        Read=Read+chr(i)
    List=TableBinary_to_list(Read)
    Rroot=Node('','')
    root=Node('','')
    for i,k in List:
        root=Rroot
        for q in k:
            if q=='0' and (root.getLeft()==None):
                empty=Node('','')
                root.setLeft(empty)
                root=Goleft(root)
            if q=='0' and (root.getLeft()!=None):
                root=Goleft(root)
            if q=='1' and (root.getRight()==None):
                empty=Node('','')
                root.setRight(empty)
                root=Goright(root)
            if q=='1' and (root.getRight()!=None):
                root=Goright(root)
        Variable=root.getParent()
        if k[-1]=='0':
            Variable.setLeft(Node(i,''))
        if k[-1]=='1':
            Variable.setRight(Node(i,''))
        root=Rroot
    File.close()
    return root



#######self defined Functions#########
##CALL HELP() THEY ALL HAVE DOC STRINGS!!##


def Table_to_list(Read):
    '''Input = String with \\t and \\n in it (table of codes) \n output = List of the codes'''
    Read=Read.replace('\t','%')
    Read=Read.replace('\n','^')
    dumy=[]
    List=[]
    for i in Read:
        n=Read.find('^')
        if i=='^':
            dumy.append(Read[:n])
            Read=Read[n+1:]
    for i in dumy:
        t=i.find('%')
        if i[t]=='%':
            List.append((i[:t],i[t+1:]))
            dumy=dumy[1:]
    return List


def TableBinary_to_list(Read):
    '''Input = String with \\t and \\n in it (table of codes) \n output = List of the codes'''
    Read=Read.replace('\t','%')
    Read=Read.replace('\r\n','^')
    dumy=[]
    List=[]
    for i in Read:
        n=Read.find('^')
        if i=='^':
            dumy.append(Read[:n])
            Read=Read[n+1:]
    for i in dumy:
        t=i.find('%')
        if i[t]=='%':
            List.append((i[:t],i[t+1:]))
            dumy=dumy[1:]
    return List

def Sort_codes(n):
    '''Input = Dict of codes \n Output = Sorted order of input relative to i,k k value'''
    n=dict_to_list(n)
    Sorted=[]
    n=list_to_dict(n)
    n=key_to_item(n)
    CodeS = sorted(n.keys(),key=len)
    for i in CodeS:
        for j,k in n.items():
            if i==j:
                Sorted.append((k,i))
    return Sorted

def k_of_tuple(n):
    '''input list of tuples \n output a list of i,k K values of all tuples'''
    a=[]
    for i,k in n:
        a.append(k)
    return a
def i_to_k(n):
    '''reverses the tuples in a list'''
    a=[]
    for i,k in n:
        a.append((k,i))
    return a

def break_tuples(n):
    '''converts a list of tuples to a simpe list of str \n input=[(i,k)] \n output=[i,k]'''
    a=[]
    for i,k in n:
        a.append(i)
        a.append(k)
    return a
    
def key_to_item(n):
    
    ''' input = dict{ i : k } \n
    output = dict { k : i }'''

    new={}
    for i,k in n.items():
        new[k]=i
    return new

def dict_to_list(n):
    
    '''Input= dict{ i : k ....} \n
    Output = List --> [(i,k)....]'''

    l=[]
    for i,k in n.items():
        l.append((i,k))
    return l

def list_to_dict(n):
    
    '''Input = List-->[(i,k),...]\n
    Output = dict{ i,k ,...}'''

    d={}
    for i,k in n:
        d[i]=k
    return d
def check(n):
    ''' Checks if Argument has a Child\n input=Node \n output = Bool'''
    if (n!=None )and (n.isLeaf()==False):
        return True
    else:
        return False

def Goleft(n):
    '''Input = parent Node \n Output = Left Child Node'''
    n=n.getLeft()
    return n

def Goright(n):
    '''Input = parent Node \n Output = Right Child Node'''
    n=n.getRight()
    return n

def list_to_Str(n):
    ''' input = list \n output = str '''
    string=''
    for i in n:
        string=string+str(i)
    return string



def buildBranch(l,r):
    node = Node("","")
    node.setRight(l)
    node.setLeft(r)
    return node
    

##freq = [
##    (8, 'a'), (1, 'b'), (2, 'c'), (4, 'd') ]

freq = [
    ('a',8), ('b',1), ('c',2), ('d',4) ]


def leafNodes(freq):
    stack = []
    for key,value in freq:
        stack.append((Node(key,""),value))
    return stack


### Problem 26
def buildHuffmanTree(frequencies):
    '''(PriorityQueue) -> Node

    Return the root of the Huffman tree constructed using the
    frequencies stored in pq.
    '''
    
    p = PriorityQueue()
    for key,value in leafNodes(frequencies):
        p.put((key,value))            
    while p.qsize() > 1:         
        l, r = p.get(), p.get()
       
        node = buildBranch(l[0], r[0])
        
        p.put((node, l[1]+r[1]))       
    return p.get()[0] 


### Problem 27
def writeHuffman(root,fname):

    '''(Node, str) -> None

    Writes the header corresponding to the Huffman tree rooted at node
    to the file with path, fname.
    '''

    with open(fname,'w') as f:
        f.write ('HUFF \n')
        f.write (str(len(leafNodes(freq))) + '\n')
        for key,value in getCodes(root).items():
            f.write(key + "\t" +  value + '\n')   


### Problem 28
def writeHuffmanBinary(root,fname):

    '''(Node, str) -> None

    Writes the header corresponding to the Huffman tree rooted at node
    to the file with path, fname.
    '''

    with open(fname,'wb') as f:
        f.write ('HUFF\r\n'.encode())
        f.write (str(len(leafNodes(freq))).encode() + '\r\n'.encode()) 
        for key,value in getCodes(root).items():
            f.write(key.encode() + '\t'.encode() +  value.encode() + '\r\n'.encode()) 



### Problem 29
def encode(fname):
    '''(str) -> str

    Returns the path to a newly created file containing the Huffman
    header and a body consisting of bits corresponding to Huffman
    coding of the contents of the file with path, fname. The name is
    derived from fname by appending '_coded' to the name of the file
    in fname.

    >>> encode('foo.txt.)
    'foo_coded.txt'
    '''
    pass

##### Compression and Decompression

### Problem 30
def compress(fname):
    '''(str) -> str

    Returns the path to the compressed file obtained by applying
    Huffman coding to the file with path, fname. The name is derived
    from fname by appending '_cmp' to the name of the file in fname.

    >>> encode('foo.txt.)
    'foo_cmp.txt'
    '''
    pass

### Problem 31
def decompress(fname):
    '''(str) -> str

    Returns the path to the file obtained by decompressing the file
    with path, fname, which is assumed to be compressed using Huffman
    coding. The name is derived from fname by appending '_dcmp' to the
    name of the file in fname.

    >>> encode('foo_cmp.txt.)
    'foo_cmp_dcmp.txt'
    '''
    pass

### Problem 32
def isHuffmanWorking(fname):
    '''(str) -> bool

    Returns True if Huffman compression and decompression above are
    inverses of each other on the file with path, fname, False
    otherwise.
    '''
    pass

