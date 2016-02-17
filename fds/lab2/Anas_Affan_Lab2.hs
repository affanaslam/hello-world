-- **** 	lst!!i returns the ith element of list.
firstKnumbers lst k = [lst!!i | i <- [0..k-1]] 

-- **** 	We get the numbers lst[length-1] (last element) to k.
lastKnumbers lst k = reverse [lst!!i | i <- [(length lst)-1, (length lst) -2 .. (length lst)-k]] 

-- ****	We concatenate the first k-1 numbers, and the last length - k numbers with the kth number.
kthElementMoved lst k = (firstKnumbers lst (k-1)) ++ (lastKnumbers lst ((length lst) - (k))) ++ [lst !!k-1]

-- ****	Assuming list is homogenous, the function compares the first and second element of ith tuple of the list.
checkList lst = [fst(lst!!i) == snd(lst!!i) | i<-[0..(length  lst) -1] ]

-- ****	i is the element of the list and i%2 will be 0 if even, and 1 if odd.
parityList lst = [ ["even","odd"]!!(i `mod` 2) | i<-lst ]

-- ******************			REFRESHER EXERCISES IN HASKELL

-- **** Last Element
myLast lst = last lst

-- ****

secondLast lst = last (init lst)

kthElemet lst k = lst !! k


-- ****	reverses a list
myReverse [x] = [x]
myReverse lst = [last lst] ++ (myReverse (init lst))

-- **** returns the only the unique elements of the list, in a list.
unique [] = []
unique [x] = [x]
unique lst = if (head lst) `elem` (tail lst) 
then (unique (tail lst)) 
else ([head lst] ++ (unique (tail lst)))

-- **** 

max' [x] = x
max' (x:xs) = if (x > max' xs) then x else max' xs

min' [x] = x
min' (x:xs) = if (x < min' xs) then x else min' xs




countFrequency lst k = (if not (k `elem` lst) then 0 else (if ((head lst) == k) then (1+countFrequency (tail lst) k)
					   else (0 + countFrequency (tail lst) k)))

uniqueList lst = [ ( (unique lst)!!i , (countFrequency lst (unique lst!!i)) ) | i<-[0..(length (unique lst))-1]]

