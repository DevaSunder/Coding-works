/*
-- Implement the following
-- reverse of a list
-- length of a list
-- null of a list
-- `elem` to check whether a given element is in the list
-- The list utilities like head, tail, last, init 
-- The tuple utilities say first, second and third
-- zipWith
*/

// Write a curried function curryF that computes
// a * (b+c)^2
// such that the following work
// curryF(2)(3)(1)
// List(1.0, 2.0, 3.0).map(curryF(2)(3))

/*
Define the infinite lists of even and odd numbers by means of filtering the list of naturals.
*/

/*
Define the function interleave that given two streams s1 and s2 returns another stream with the elements of s1 and s2 interleaved. 
E.g., if we call

interleave(Stream(1,2,3,4),Stream(10,20,30,40))

we should get the stream (1,10,2,20,3,30,4,40).
*/
// =========================================================

val from: (Int => Stream[Int]) = (n) => {n #:: from(n+1)}

val fact: (Int => Int) = (n) => {if (n==0) 1 else {n*fact(n-1)}}

val allFacts: (Stream[Int] => Stream[Int]) = (nats) => { fact(nats.head) #:: allFacts(nats.tail) }

val allFactsfrom0 = {
  lazy val allFactsrec: ((Int, Int) => Stream[Int]) = (n,factN) => { factN #:: allFactsrec(n+1, (n+1)*factN)}
  allFactsrec(0,1)
  }

val ssum: ((Stream[Int], Stream[Int]) => Stream[Int]) = (s1,s2) => { (s1,s2) match {
   case (hd1 #:: tl1, hd2 #:: tl2) => (hd1+hd2) #:: ssum(tl1,tl2)}}

val nats = from(0)

val evenStrMap = nats.zip(nats).map((a) => a._1 + a._2)
val oddStrMap = nats.zip(nats.tail).map((a) => a._1 + a._2)

val fibStr: (Stream[Int]) = {
   0 #:: 1 #:: (fibStr.zip(fibStr.tail).map((a) => a._1 + a._2)
}

// =========================================================

/*

val conditional: ((Boolean, Int, Int) => Int) = 
   (condition, thenBranch, elseBranch) => {if (condition)
   {thenBranch} else {elseBranch}
}

// Lazy evaluation => Infinite data structure

val lazyConditional: ((Boolean, => Int, => Int) => Int) = 
   (condition, thenBranch, elseBranch) => {if (condition)
   {thenBranch} else {elseBranch}
}
*/
// ========================================================

// Collections
// Immutable - List, Range, Set (mutable), maps (mutable)
// Mutable - Arrays

// ====================================================
/*
val fact: (Int => Int) = (n) => {if (n==0) 1 else {n*fact(n-1)}}

val anotherFact: (Int => Int) = (n) => {n match {
   case 0 => 1
   case m => m * fact (m-1)
}}

val length: (List[Int] => Int) = (l) => { if (l == Nil) 0 else {1+length(l.tail)}}

val anotherLength: (List[Int] => Int) = (l) => { l match {
  case Nil => 0
  case hd::tl => 1 + anotherLength(tl)
 }}

val isThere: ((Any, List[Any]) => Boolean) = (e,l) => {
  if (l == Nil) false else {
    if (e == l.head) true else 
      isThere(e,l.tail)}
 }
 
val isThereSatisfyingP: ((Int => Boolean, List[Int]) => Int) = (p,l) => {
  if (l == Nil) {-1} else {
    if (p(l.head)) {l.head} else
      isThereSatisfyingP(p,l.tail)}
 } 

*/

// =====================================================

/*
// f^-1{[f(a) + f(b)]/2} quadratic arithemetic mean

val qam: ((Double, Double, Double => Double, Double => Double) => Double) = (a, b, f, finv) => finv((f(a)+f(b))/2)

// Normal Function - Arithmetic Mean
val am: ((Double, Double) => Double) = (a,b) => (a+b)/2

// Its curried version
val curryam: (Double => (Double => Double)) = (a) => { (b) => (a+b)/2}

// Compound Interest P(1+i)^t
val CI: ((Double, Double, Double) => Double) = (i,t,p) => p * Math.pow(1+i, t)

val curryCI: (Double => (Double => (Double => Double))) = (i) => { (t) => { (p) => p * Math.pow(1+i, t)}}
*/

// ========================================================

/* Anonymous Functions
(a: Int) => 2*a
(a: Int, b: Int) => a+b
(a: Int, f: Int => Int) => f(a)
*/

/* Named Functions
val f1 = (a: Int) => 2*a
val f2 = (a: Int, b: Int) => a+b
val f3 = (a: Int, f: Int => Int) => f(a)
*/

/*
// A better way of writing functions
val f1:(Int => Int) = a => 2*a
val f2:((Int,Int) => Int) = (a,b) => a+b
val f3:((Int,Int => Int) => Int) = (a,f) => f(a)
*/












