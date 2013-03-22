class Money(dollars: Int, cents: Int) {
  override def toString() =
    "$" + dollars + "." + cents
}

val m = new Money(3,40)
println("I gots some money " + m)
