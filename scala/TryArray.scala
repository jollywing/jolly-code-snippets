import scala.collection.mutable.ArrayBuffer

object TryArray {
  def main(args: Array[String]) {
    var ab = ArrayBuffer.empty[(Int,Int)]
    for(i <- 1 to 10) {
      ab += ((i, i))
    }
    val a = ab.toArray
    a.foreach{
      case t => println(t)
    }
  }
}
