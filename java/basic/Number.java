
/**
 * Author: Jolly Wing
 * Create: 2013-06-27
 * Update: 2013-06-27
 **/

/**
 * @compile: javac -encoding UTF-8 Number.java
 * 系统有 java.lang.Number 类，我们的 Number 类不属于什么包，
 * 所以不会和 java.lang.Number 冲突。
 **/

public class Number {
    public static void main (String [] args) {

        // Integer.parseInt(str): str 中不能含小数点，否则会报异常。
        String intStr = "999";
        try {
            int i = Integer.parseInt(intStr);
            System.out.println("The value of i is " + i);
        } catch (NumberFormatException e) {
            System.out.println(intStr + " is not a valid integer string.");
        }

        // 100 会被认为是4字节的 整型常量 (int)，
        // 100L 或 100l 表示 8字节 的长整型常量 (long)。
        // 如果试图把 长整型常量 赋值给 整型变量，会报错。
        long j = 100l;
        System.out.println("The value of j is " + j);

        // float 表示单精度浮点数，4字节，可以精确到小数点后7位。
        // 123.456 会被认为是 double 常量，将它赋值给 float 变量会报错。
        // 123.456f 或 123.456F 表示float常量。
        float f = 123.456F;
        System.out.println("The value of f is " + f);

        // double 表示双精度浮点数，8字节，可以精确到小数点后15位。
        // 23.5 或 23.5d 或 23.5D 都表示 double 常量。
        double d = 23.5D;
        System.out.println("The value of d is " + d);
    }
}
