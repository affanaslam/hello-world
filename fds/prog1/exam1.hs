
import Data.List 
data BinaryTree a = EmptyTree | Node a (BinaryTree a) (BinaryTree a) deriving (Show, Read, Eq)  

type Pair = (Int, [Char])
type HashTable = [(Pair)] 

{-Problem 1: -}


{-a)  a corresponds to any type-}
type Stack a = [a]

push::Stack a -> a -> Stack a 
push [] v = v:[] -- pushing to the top of the list 
push stack v = v:stack  

isEmpty::(Ord a) => Stack a -> Bool 
isEmpty [] = True 
isEmpty list
			| list /= [] = False 
			| otherwise = True 

top::Stack a ->  a 
top xs = head xs

{-top [] = Nothing-}

pop::Stack a -> Stack a 
pop [] = []
pop xs = tail xs	




{-b Queue implementation -}

type Queue a = [a]

enqueue::Queue a -> a -> Queue a  -- in queue you push from the bottom 
enqueue [] a = []++[a]
enqueue queue a = queue++[a]

isEmpty2::(Ord a) => Queue a -> Bool 
isEmpty2 [] = True 
isEmpty2 queue
			| queue /= [] = False 
			| otherwise = True   

front:: Queue a -> a 
{-could have used front [] "=" Nothing -}
front xs = head xs 

dequeue:: Queue a -> Queue a
dequeue xs = tail xs


{-loop through the elements to check whether they are greater or smaller-}
singleton' :: a -> BinaryTree a
singleton' x = Node x EmptyTree EmptyTree

value'::BinaryTree a -> a 
value' (Node v _ _) = v 

inorder':: BinaryTree a -> [a]
inorder' t@(Node v left right) = l ++ showkey ++ r 
	where 
		l = inorder' left 
		r = inorder' right 
		showkey = [value' t]    

sort':: (Ord a) =>  [a] -> [a]
sort' list = sort list 

-- here we are using the basic property of a binary tree than if it is subjected to inorder traversal it will output a sorted list. 

isBST:: (Ord a) => BinaryTree a -> [a] -> Bool 
isBST t@(Node v left right) a = if (inorder' t == sort' a) then True else (False)     

{-finding depth of the tree-}
						
depth' EmptyTree = 0
depth' (Node a left right) = 1+ (max (depth' (left) depth' (right)) ) 

{--
the way we are implementing this:

we are going to define a function called balanceFactor that will take a Binary tree. Its left child and its right child 
and will output the difference of their depths. If it is in the range [-1,1] it is ok, if not it is not balanced 
--}

balanceFactor:: (Ord a) => BinaryTree a => Bool 
balanceFactor (Node _ u v) 
				   | subtree_difference > -1 && subtree_difference < 1 = False   
				where
				subtree_difference = (depth' u) - (depth' v)  


isAVLBalanced::BinaryTree a -> Bool 
isAVLBalanced singleton' = True
isAVLBalanced t@(Node a left right) = balanceFactor t 




{-
Problem 3 

a , b done 
c
-}

{-
the hash function is weak. 
The first limitation in 
k mod m 
is that if m is a power of 2 (2^p) it will output the same values for permutations of the string. 
Furthermore if it is the power of 2, the last d bits it will take would be the same for the permutations 
Also we can prove that if m = 2p - 1 and the radix/base in which we are considering the number is 2^p 
the permutations will output the same value. The good idea, as Cormen suggests, is to take prime number
but even if we take a prime number and m = 2p - 1 and radix is suppose 128 for the characters, the permutations 
(st and ts) will have collision. To sort this out, we need to generate the integers that are not close to the power of 2 Despite all the limitations I am using this as a function.  
-}
hash::Pair -> HashTable -> Int 
hash (k,_) h = k `mod` (length h)  


--d 

{-
concatenate keys 

l = [(2,'b'),(4,'a')]
a = unzip l 

-}

find::Int-> HashTable -> [Char]
find k hash
			 | hash (_ _) (k) `elem` fst (list) = [ ((snd list) !! (hash (k)))!!0] 
			 | otherwise = [] 

		where list = (unzip h)  	   


{-
we are using zip and unzip in the hash table 

if isExist == True then delete it and if False insert 
so supposedly it will go to the subsequent condition. 

we are unzipping the lsit 

let c = zip [1,2,3,4][['a'],['b'],['c']]
hashtable = [(1,"a"),(2,"b"),(3,"c")]
unzip it ([1,2,3],["a","b","c"])


-}

insert::Pair -> HashTable -> HashTable

insert p@(k,[v]) h
				| isExist == True = delete (h !! hash ( (k,_) h))
				| isExist == False = insert p h  
				| otherwise = h  

			where 
			  isExist = hash (_ _) (k) `elem` fst (list)
		      list = (unzip h)     





























