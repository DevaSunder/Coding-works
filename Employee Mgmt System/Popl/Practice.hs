-- comments
{-
Hello
-}

import Data.List
import System.IO

--Int
maxInt = maxBound :: Int
minInt = minBound :: Int

--Double
bigFloat = 3.999999 + 0.0000005

--Permanent value over variable
always5 :: Int
always5 = 5

--Functions

sumOfNums=[1..100]
summy=sum(sumOfNums)
addEx=5+4
 
modEx = mod 5 4 --Prefix operator
modEx2 = 5 `mod` 4

num9 = 9 :: Int
sqrtof9 = sqrt(fromIntegral num9)

trueAndFalse = True && False
trueOrFalse = True || False

-- use :t in ghci to know about the function.


--Lists

primenumbers=[3,5,7,11]

morePrime = primenumbers ++ [13,17,19,23,29]

--cons operator to construct the list
favNums = 2:7:21:66:[]

multList=[[3,5,7],[11,13,17]]

morePrime2 = 2 : morePrime --add 2

lenPrime = length morePrime2
revPrime = reverse morePrime2
isListEmpty = null morePrime2

firstPrime = head morePrime2
lastPrime = last morePrime2
primeInit = init morePrime2 --except last value
first3Prime = take 3 morePrime2

is7InList = 7 `elem` morePrime2

newList = [2,3,5]
prodPrimes = product newList

evenList = [2,4..20]

letterList=['A','C'..'Z']

--InfiniteList
infinPow10 = [10,20..]

many2s = take 10(repeat 2)

many3s = replicate 10 3 -- 3 3 3 3 3 3 3 3 3 3

cycleList = take 10 (cycle[1,2,3,4,5]) 

listTimes2 = [x*2 | x <-[1..10]]

listTimes3 = [x*3 | x <-[1..10],x*3<=50]

divisBy9N19 = [x | x <- [1..500],x `mod` 13 ==0,x `mod` 9 ==0]

sortedList = sort [9,0,2,3,5,4]

sumOfLists = zipWith (+) [1,2,3,4,5][6,7,8,9,10] -- output 7,9,11,13,15

listBiggerThan5 = filter (>5) morePrime2

evensUpTo20 = takeWhile (<=20) [2,4..]

mulOfList = foldr (+) 2[2,3,4,5] -- foldl and foldr

--List Comprehension

pow3List = [3^n | n <- [1..10]]

multTable = [[x*y | y <-[1..10],x<-[1..10]]]
--Tuple

randTuple = ("a","Random Tuple")

bobSmith = ("bon Smith",52)

bobsName = fst bobSmith
bobsAge  = snd bobSmith

names = ["Bob","Mary","Tom"]
addresses=["123 Main","234 North","567 South"]

namesAddress = zip names addresses


--Functions

main = do
    putStrLn "Wat your name"
    name <- getLine
    putStrLn("Hello" ++ name)

--func1

addMe :: Int -> Int -> Int -- inputs an int,another int and return an int
--funcname param1 param2 = operations(returned value)
addMe x y = x + y
 
addTuples :: (Int,Int) -> (Int,Int) -> (Int,Int)
addTuples (x,y) (x2,y2) = (x+x2,y+y2)

whatAge :: Int -> String

whatAge 16 = "You can drive"
whatAge 18 = "You can vote"
whatAge 21 = "You're an adult"
whatAge _ = "Nothing Important"


factorial :: Int -> Int

factorial 0 =1
factorial n =n*factorial (n-1)


prodFact n = product [1..n]


--Guards Conditional Exec


isOdd :: Int -> Bool

isOdd n
    |   n `mod` 2 == 0 = False
    |   otherwise = True

isEven n = n `mod` 2 == 0

whatGrade :: Int -> String

whatGrade age
    | (age>=5)&&(age<=6) = "KG"
    | (age>6)&&(age<=10) = "Elementary School"
    | otherwise = "Go to College"


--Where clause to prevent repeated calc


--batAvgRating1 :: double -> double -> String

batAvgRating hits atBats
    | avg <=0.200 = "Teriible Bating"
    | avg <= 0.250 = "Abgagd"
    |otherwise = "SUoooep"
    where avg = hits / atBats
{-
getListItems :: [Int] -> String

getListItems [] = "Your List isempty"
getListItems (x:[])="Your List starts with " ++ show x
getListItems (x:y:[])="Your List contains" ++ show x " and " ++ show y
getListItems (x:xs)="The 1st item is " ++ show x " and the rest is " 

getFirstItem :: String -> String

getFirstItem [] = "Empty String"
getFirstItem all@(x:xs) = "The first letter in " ++ all ++ " is " show x
-}
--Accesign list items


sumofmulti :: Int -> Int
sumofmulti n
    | (n==0) = 0 
    |((n `mod` 3)==0)||((n `mod` 5)==0)  = n+sumofmulti (n-1)
    | otherwise = sumofmulti (n-1)

















