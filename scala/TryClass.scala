
/* 类定义直接就是构造函数 */
class TryClass(x: Int, y: Int) {
  var _x = x
  var _y = y
  println(_x + _y)
}


/* main必须是静态方法，但scala中没有静态方法。
 * 可以把main定义在独立对象或伴生对象中 */
object TryClass extends TryClass(10, 10) {
  def main(args: Array[String]){
    // val oo = new TryClass(10, 10)
    println(_x)
  }
}
