/**
 * 题目描述：
 *   读入一个只包含 +, -, *, / 的非负整数计算表达式，计算该表达式的值。
 * 输入：
 *   测试输入包含若干测试用例，每个测试用例占一行，每行不超过200个字符，整数和运算符之间用一个空格分隔。没有非法表达式。当一行中只有0时输入结束，相应的结果不要输出。
 * 输出：
 *   对每个测试用例输出1行，即该表达式的值，精确到小数点后2位。
 * 样例输入：
 * 1 + 2
 * 4 + 2 * 5 - 7 / 11
 * 0
 * 样例输出：
 * 3.00
 * 13.36
 *
 * Create: 2015-01-07 周三
 * Compile: javac -encoding GBK StackCaculator.java
 */

import java.util.*;

class Main {

    private static double calcExp(String exp){
        String [] ss = exp.split(" ");
        ArrayList<Double> stack = new ArrayList<Double>();
        int top = -1;

        int i = 0;
        double d;
        while (i < ss.length) {
            if (ss[i].equals("+")) {
                d = Double.parseDouble(ss[++i]);
                stack.add(d);
                top ++;
            }
            else if(ss[i].equals("-")) {
                d = Double.parseDouble(ss[++i]);
                stack.add(d * -1);
                top ++;
            }
            else if(ss[i].equals("*")) {
                d = Double.parseDouble(ss[++i]);
                stack.set(top, (double)stack.get(top) * d);
            }
            else if(ss[i].equals("/")) {
                d = Double.parseDouble(ss[++i]);
                stack.set(top, (double)stack.get(top) / d);
            }
            else {
                stack.add(Double.parseDouble(ss[i]));
                top ++;
            }
            i ++;
        }

        d = 0;
        for (i = 0; i < stack.size(); i++) {
            d += (double)stack.get(i);
        }
        return d;
    }

    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);
        while(cin.hasNext()){
            String exp = cin.nextLine();
            if(exp.equals("0"))
                break;
            double r = calcExp(exp);
            System.out.println(String.format("%.2f", r));
        }
    }
}
