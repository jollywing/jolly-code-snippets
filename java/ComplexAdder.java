/**
 * 题目描述：
 * 给定两个整数A和B，其表示形式是：从个位开始，每三位数用逗号","隔开。
 * 现在请计算A+B的结果，并以正常形式输出。
 * <b>输入</b>：
 * 输入包含多组数据数据，每组数据占一行，由两个整数A和B组成（-10^9 < A,B < 10^9）。
 * 输出：
 * 请计算A+B的结果，并以正常形式输出，每组数据占一行。
 * 样例输入：
 * -234,567,890 123,456,789
 * 1,234 2,345,678
 * 样例输出：
 * -111111101
 * 2346912
 *
 * Author: jiqingwu@gmail.com
 * Create: 2015-01-07 周三
 * Compile: <code>javac -encoding UTF8 ComplexAdder.java</code>
 */

import java.util.Scanner;

public class ComplexAdder {
    private static int parseString(String a) {
        boolean positive = true;
        if (a.startsWith("-")) {
            positive = false;
            a = a.substring(1);
        }

        int sum = 0;
        String [] ss = a.split(",");
        for (String s: ss) {
            sum = sum * 1000 + Integer.parseInt(s);
        }

        if (!positive)
            sum *= -1;

        return sum;
    }

    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);
        String aStr, bStr;
        int a, b;
        while(cin.hasNext()){
            aStr = cin.next();
            bStr = cin.next();
            a = parseString(aStr);
            b = parseString(bStr);
            System.out.println(a + b);
        }
    }
}
