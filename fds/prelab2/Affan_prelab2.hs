doubleMe x = x + x

fib 0 = 1 
fib 1 = 1
fib n = fib (n-1) + fib (n-2) 


speed dist time = dist / time 

salePrice sellingPrice discountRate = sellingPrice - (sellingPrice * (discountRate/100))

largestNumber x y z = max (max x y) z

average lst = (sum lst) / (fromIntegral  (length lst))

uptoThatNumber num = [1,2 .. num]

sumUpto num = sum [1,2 .. num]

divisible num = [x | x <- [1 .. ] , x `mod` num == 0]

divisibleByNum num = product [x | x <- [1..num], even x]

getFromTuple tuple = snd (fst tuple) 