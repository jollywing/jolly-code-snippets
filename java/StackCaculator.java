/**
 * ��Ŀ������
 *   ����һ��ֻ���� +, -, *, / �ķǸ�����������ʽ������ñ��ʽ��ֵ��
 * ���룺
 *   ��������������ɲ���������ÿ����������ռһ�У�ÿ�в�����200���ַ��������������֮����һ���ո�ָ���û�зǷ����ʽ����һ����ֻ��0ʱ�����������Ӧ�Ľ����Ҫ�����
 * �����
 *   ��ÿ�������������1�У����ñ��ʽ��ֵ����ȷ��С�����2λ��
 * �������룺
 * 1 + 2
 * 4 + 2 * 5 - 7 / 11
 * 0
 * ���������
 * 3.00
 * 13.36
 *
 * Create: 2015-01-07 ����
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
