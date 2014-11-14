import turtle



#Question 1 part 1 


def F(k,l):
    
    turtle.fd(l)
    turtle.left(60)
    turtle.fd(l)
    turtle.right(120)
    turtle.fd(l)
    turtle.left(60)
    turtle.fd(l)
    


def kochCurve (i):

   
    l = 200/(3**i-1)
    kochCurve1 (i,l)
    
##    if i == 0:
##        turtle.fd(l)
##    elif i == 1: #base case
##        F(i)
##    else:
##        kochCurve(i-1)
##        turtle.left(60)
##        kochCurve(i-1)
##        turtle.right(120)
##        kochCurve(i-1)
##        turtle.left(60)
##        kochCurve(i-1)

def kochCurve1 (i,l):

    if i == 0:
        turtle.fd(l)
    elif i == 1: #base case
        F(i,l)
    else:
        kochCurve1(i-1,l)
        turtle.left(60)
        kochCurve1(i-1,l)
        turtle.right(120)
        kochCurve1(i-1,l)
        turtle.left(60)
        kochCurve1(i-1,l)

