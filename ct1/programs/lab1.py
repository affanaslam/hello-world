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

        
        
        
            
        
            

    

