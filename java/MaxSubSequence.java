/**
 * @题目描述： 
 *  给定K个整数的序列{ N1, N2, ..., NK }，其任意连续子序列可表示为{ Ni, Ni+1, ..., Nj }，其中 1 <= i <= j <= K。最大连续子序列是所有连续子序列中元素和最大的一个，例如给定序列{ -2, 11, -4, 13, -5, -2 }，其最大连续子序列为{ 11, -4, 13 }，最大和为20。现在增加一个要求，即还需要输出该子序列的第一个和最后一个元素。
 * @输入： 
 * 测试输入包含若干测试用例，每个测试用例占2行，第1行给出正整数K( K< 10000 )，第2行给出K个整数，中间用空格分隔。当K为0时，输入结束，该用例不被处理。
 * @输出： 
 * 对每个测试用例，在1行里输出最大和、最大连续子序列的第一个和最后一个元素，中间用空格分隔。如果最大连续子序列不唯一，则输出序号i和j最小的那个（如输入样例的第2、3组）。若所有K个元素都是负数，则定义其最大和为0，输出整个序列的首尾元素。
 * @样例输入： 
 * 6
 * -2 11 -4 13 -5 -2
 * 10
 * -10 1 2 3 4 -5 -23 3 7 -21
 * 6
 * 5 -8 3 2 5 0
 * 1
 * 10
 * 3
 * -1 -5 -2
 * 3
 * -1 0 -2
 * 0
 * @样例输出： 
 * 20 11 13
 * 10 1 4
 * 10 3 5
 * 10 10 10
 * 0 -1 -2
 * 0 0 0
 *
 * @Compile:
 * javac -encoding UTF8 MaxSubSequence.java
 * @Create: 2015-01-11 Sun
 **/

import java.util.*;

class Main {
    public static boolean isAllNegative(int [] numArray)
    {
        for(int i = 0; i < numArray.length; i++) {
            if (numArray[i] >= 0) {
                return false;
            }
        }
        return true;
    }

    public static void maxSS_O1(int [] numArray) {
        if (isAllNegative(numArray)) {
            System.out.println("0 " + numArray[0] + " " + numArray[numArray.length - 1]);
            return;
        }
        int maxSum = numArray[0];
        int sum = 0, tempStart = 0;
        int startIndex = 0, endIndex = 0;
        for(int i = 0; i < numArray.length; i++) {
            sum += numArray[i];
            if (sum > maxSum) {
                maxSum = sum;
                startIndex = tempStart;
                endIndex = i;
            }
            if (sum < 0) {
                sum = 0;
                tempStart = i + 1;
            }
        }
        System.out.println(maxSum + " " + numArray[startIndex] +
                ' ' + numArray[endIndex]);
    }

    public static void maxSS_O2(int [] numArray) {
        if (isAllNegative(numArray)) {
            System.out.println("0 " + numArray[0] + " " + numArray[numArray.length - 1]);
            return;
        }
        int maxSum = numArray[0];
        int startIndex = 0;
        int endIndex = 0;
        int i, j, sum;
        for (i = 0; i < numArray.length; i++) {
            sum = 0;
            for (j = i; j < numArray.length; j++) {
                sum += numArray[j];
                if (sum > maxSum) {
                    maxSum = sum;
                    startIndex = i;
                    endIndex = j;
                }
            }
        }
        System.out.println(maxSum + " " + numArray[startIndex] +
                ' ' + numArray[endIndex]);
        
    }

    public static void maxSubSequence_O3(int [] numArray) {
        if (isAllNegative(numArray)) {
            System.out.println("0 " + numArray[0] + " " + numArray[numArray.length - 1]);
            return;
        }

        int step;
        int maxSum = Integer.MIN_VALUE;
        int startIndex = 0;
        int endIndex = numArray.length - 1;
        for(int start = 0; start < numArray.length; start++) {
            for(step = 1; step <= numArray.length - start; step++){
                int sum = 0;
                for (int off = 0; off < step; off++) {
                    sum += numArray[start + off];
                }
                if (sum > maxSum) {
                    maxSum = sum;
                    startIndex = start;
                    endIndex = start + step - 1;
                }
            }
        }
        System.out.println(maxSum + " " + numArray[startIndex] +
                ' ' + numArray[endIndex]);
    }

    public static void main(String [] args) {
        int numCount;
        int [] numArray;
        Scanner cin = new Scanner(System.in);
        while(cin.hasNext()) {
            numCount = cin.nextInt();
            if (numCount == 0) break;
            numArray = new int[numCount];
            for (int i = 0; i < numCount; i++) {
                numArray[i] = cin.nextInt();
            }
            maxSS_O1(numArray);
        }
    }
}
