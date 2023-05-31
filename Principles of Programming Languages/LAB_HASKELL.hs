--reverse
--length of a list
--null of a list
--flip
--'elem' to check whether a given element is in the list
--The list utilities like head,tail,last,init
--The tuple utilities say first,second and third
--zipWith
--flip
--map
--filter

--element
a = [1,2,3,4,5]
elemfunc x
    | x `elem` a = "an element of the list"
    | otherwise = "Not an element"

--zipWith
a1=[1,2,3,4,5]
b1=[10,11,12,13,14]
zippy = zipWith (+) a1 b1

--reverse
rev1 = reverse [1,2,3,4,5]

--length
len1 = length [1,1,1,2,2,2,3,3,3]

--flip 
--flip1 = flip (+) [1,2,3,4,5]

--sum of elements of list
listaddn :: [Int] -> Int
listaddn [] = 0
listaddn [x] = x
listaddn (x:xs) = x+listaddn(xs)



--ZipWith HigherOrderFuncitons


zipWith' _ [] _ = []
zipWith' _ _ [] = []
zipWith' f (x:xs) (y:ys) = f x y : zipWith' f xs ys



--Currying and higher order fucntion

--Let and where

letty a b = x+y
    where 
    x=a*a
    y=b*b






