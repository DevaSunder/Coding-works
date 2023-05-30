val fruit: List[String] = List("apples","oranges","pears")

val numbers: List[Integer]= List(1,2,3,4,5)

val twodimen: List[List[Integer]] = List(

    List(0,1,0),
    List(0,1,1),
    List(1,0,0)
)

val Empty = Nil

val consnil = 1 :: (2 :: (3 :: Nil))

println("head of list is " + consnil.head)

//List Concat

val student : List[String] = List("Deva","Sunder","Super")
val Schools : List[String] = List("Ase","Bse","Cse")


var Combined = student:::Schools

println("The combined list is as follows :" + Combined)


//val - immutable
//var - mutable

// 2 2 2 2 2 2 2 2 2 2
val num = List.fill(10)(2)

//List Tabulate

val squares = List.tabulate(6)(n => n*2)

def func1 (list : List[Integer]) : Integer = 
{
    if(list(0)==1)
    {
        println("Hi")
        return list(0)
    }
    else return (list(2))
}


def localMaxima (list: List[Integer]) : Unit = 
{   
    var count = 0
    for (elem <- list)
    {
        count=count+1
    }
    for (i<-1 until count-1)
    {
        if (list(i)>list(i-1) && list(i)>list(i+1))
        {
            println(list(i))
        }
    }
}


//reverse of a List


/*def reversefunc (list: List[Integer]) : Unit =
{
    var count=0
    var finlist : List[Integer] = List()
    for (elem <- list)
    {
        count=count+1
    }
    finlist=List.Tabulate

    for (i<-0 until count)
    {
        finlist(i)=list(count-i)
    }
    println(finlist)

}*/

val rever: (List[Int] => List[Int]) =(x) =>x match{
    case x::xs => rever(xs):::List(x)
    case Nil => Nil
}


/*val rever: (List[Int] => List[Int]) = {
  case x :: xs => rever(xs) ::: List(x)
  case Nil => Nil
}*/


//count elements in nested list


def countElements(lst: List[Any]): Int = {
  var count = 0
  for (elem <- lst) {
    elem match {
      case subList: List[_] => count += countElements(subList)
      case _ => count += 1
    }
  }
  count
}

// Example usage
val nestedList = List(1, 2, List(3, 4, 5), 6, List(7, List(8, 9)))
val count = countElements(nestedList)
println(count) // Output: 9








