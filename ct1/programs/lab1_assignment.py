#from string import maketrans #In windows it work 

import math

def isPalindrome(s):
    a = s[::-1].lower() #lowercase
    b = s[:].lower() #lowercase
    if a == b:
        return True
    else:
        return False

def isPalindrome1 (s):
    if len(s) < 2:
        return True
    return s[0] == s[-1] and isPalindrome1(s[1:-1])

def binaryString (n):

    b = ""
    p = int (math.log (n,2))
    for i in range (p,-1,-1):
        if n >= 2**i:
            b = b + "1"
            n = n - 2**i
        else:
            b = b + "0"
    return b
            
            

####def bla():
##    i=9
##    while i>=0:
##        print(i)
##        i=i-1
##        




#Q3
def binaryString1(n):
    answer = ''
    if n == 0:
        return '0'
    elif n == 1:
        return '1'
    elif n > 1:
        answer = binaryString1(n//2)
        answer = answer + str(n%2)
    return(answer)

def grid(rw,c,h,w):
    
    rw1 =  c*(w*"-"+"+")
    rw2 =  c*(w*" " +"|")
    j=0
    
    print ("+" + rw1)
    while (j<rw):
        i=0
        j+=1
        while (i<h):
            print ("|" + rw2)
            i+=1
        print ("+" + rw1)


#Q5
def transform(a,b):
    if a == b:
        return str(a)
    elif b%2 ==0 and b/2 >= a:
       b = b//2
       return '(' + transform (a,b) + ' *2)'
    else:
       b = b-1
       return '(' + transform (a,b) + ' +1)'
    transform(a,b)

#Q6
def generateRows(n,c):
    inpBin = "01"
    oupBin = "FT"
    trans = str.maketrans(inpBin,oupBin)
    a = ""
    bi = binaryString1(c)
    if n == len(bi):
        a = a + bi
    elif n != len(bi):
        a = a + "0" * (n - len(bi)) + bi
    astr = str(a)
    return (astr.translate(trans))
    
def generateTruthTable(n):
    a = 2**n
    for i in range (0,a):
        print (generateRows(n,i))
#Q7

def exponentString (n):
    bi = binaryString1(n)
    b = " "
    for c in bi:
        if c == 1:
            b = b + "SX"
        else:
            b = b + "S"
    return c
    

#Q7(b)

def computeExponent (b):
    a = 1
    for c in b:
        if c == "s":
            a = a * 2
        else:
            a = a + 1
    return a

#Q10 (a)

def encrypt (a):
    a_up = a.upper()
    inpStr = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    outStr = "KLMNOPQRSTUVWXYZABCDEFGHIJ"
    trans = str.maketrans(inpStr,outStr)
    return a_up.translate(trans)


#(b)


def decrypt (a):
    a_up = a.upper()
    inpStr = "KLMNOPQRSTUVWXYZABCDEFGHIJ"
    outStr = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    trans = str.maketrans(inpStr,outStr)
    return a_up.translate(trans)
        
        
#(c)

def takeInput (chc, strn):
    if int(chc) == 1:
        return encrypt(strn)
    elif int(chc) == 2:
        return decrypt (strn)
    else:
        return "Either enter 1 or 2"
        
    
#(d)

def encrypt1 (strn):
    a = ""
    for i in range (0,len(strn)):
        a = a + str(ord(strn[i])) + " "
    print(a)

##def decrypt1 (inr, n):
##    print (chr(int((inr[n:n+4].strip()))) + decrypt1 (inr[n+4:n+8]))
        
def decrypt1(inr):
    b = " "
    if inr < 0:
        print('Out of range')
        return
    else:
        c = chr(strn)
        b = b + str(c)
    return b







#Q9(a)

def countHanoiMoves (n):

#Tn = 2Tn-1 + 1(recursive) 2^n - 1
    return 2**n - 1
    


    
    


         
    
