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
 * Compile: javac -encoding GBK SimpleCaculator.java
 * Wrong Answer, Why?
 */

import java.util.*;

class Main {

    private static int charCountInString(String s, char c){
        int count = 0;
        int index = -1;
        while((index = s.indexOf(c, index + 1)) != -1){
            count ++;
        }
        return count;
    }

    /**
     * calc the simple expression such as '5 + 6'
     */
    private static double calcSimpleExp(String exp){
        String [] ss = exp.split(" ");
        if (ss.length != 3) {
            System.out.println("Invalid Simple Expression: " + exp);
            System.exit(2);
        }
        double left, right;
        left = Double.parseDouble(ss[0]);
        right = Double.parseDouble(ss[2]);
        if (ss[1].equals("+"))
            return left + right;
        else if (ss[1].equals("-"))
            return left - right;
        else if (ss[1].equals("*"))
            return left * right;
        else
            return left / right;
    }

    private static double calcExp(String exp){
        int spaceCount = charCountInString(exp, ' ');
        if(spaceCount < 2){
            System.out.println("invalid Expression: " + exp);
            System.exit(1);
        }
        // if it contains only 2 space, it is a simple exp, calc
        if(spaceCount == 2){
            return calcSimpleExp(exp);
        }
        else {
            char lastOp, secondToLastOp;
            int t = exp.lastIndexOf(' ');
            lastOp = exp.charAt(t - 1);
            // the second to last space
            int t2 = exp.lastIndexOf(' ', t - 1);
            // the third to last space
            int t3 = exp.lastIndexOf(' ', t2 - 1);
            secondToLastOp = exp.charAt(t3 - 1);
            // if its last operator is * or /, calculate the simple exp,
            // then generate new exp, call calcExp(newExp)
            if (lastOp == '*' || lastOp == '/') {
                String se = exp.substring(t3 + 1);
                double r = calcSimpleExp(se);
                String newExp = exp.substring(0, t3 + 1) + r;
                return calcExp(newExp);
            }
            else {
                    String headExp = exp.substring(0, t2);
                    String remainExp = exp.substring(t2);
                    return calcExp(calcExp(headExp) + remainExp);
            }
        }
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
