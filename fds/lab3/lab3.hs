data Tree a = EmptyTree| Node a (Tree a) (Tree a) deriving (Show, Read, Eq)

  
depth :: (Ord a) => a -> Tree a -> Int

depth x EmptyTree =  -1  
depth x (Node a left right)   
    | x == a = 0
    | depth x left > -1 = 1 +  (depth x left)   
    | depth x right > -1  = 1 + (depth x right) 
    | otherwise = -1


height :: (Ord a) => a -> Tree a -> a

height _ EmptyTree = 0 
height x (Node a left right)
	| x == a = 1 + max ((height x left) (height x right))



tree = Node 5 (Node 3 (Node 1 EmptyTree EmptyTree) (Node 4 EmptyTree EmptyTree)) (Node 7 (Node 6 EmptyTree EmptyTree) (Node 8 EmptyTree EmptyTree))  

