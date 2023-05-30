val item1 : List[String] = List("Cake","Milk","Cheese","Toilet Paper")
val item2 : List[String] = List("Bread","Water","Juice","Milk","Cheese")

for (i<-0 until item1.length)
    {
        for (j<-0 until item2.length)
        {
            if(item1(i)==item2(j))
            {
                println(item1(i))
            }

        }

    }
