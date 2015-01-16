/**
 * PROBLEM:
 * Grading hundreds of thousands of Graduate Entrance Exams is a hard work. It is even harder to design a process to make the results as fair as possible. One way is to assign each exam problem to 3 independent experts. If they do not agree to each other, a judge is invited to make the final decision. Now you are asked to write a program to help this process.
 * For each problem, there is a full-mark P and a tolerance T(&lt;P) given. The grading rules are:
 *  ? A problem will first be assigned to 2 experts, to obtain G1 and G2. If the difference is within the tolerance, that is, if |G1 - G2| <= T, this problem's grade will be the average of G1 and G2.
 *  ? If the difference exceeds T, the 3rd expert will give G3.
 *  ? If G3 is within the tolerance with either G1 or G2, but NOT both, then this problem's grade will be the average of G3 and the closest grade.
 *  ? If G3 is within the tolerance with both G1 and G2, then this problem's grade will be the maximum of the three grades.
 *  ? If G3 is within the tolerance with neither G1 nor G2, a judge will give the final grade GJ.
 * INPUT:
    Each input file may contain more than one test case.
    Each case occupies a line containing six positive integers: P, T, G1, G2, G3, and GJ, as described in the problem. It is guaranteed that all the grades are valid, that is, in the interval [0, P].
 * OUTPUT:
    For each test case you should output the final grade of the problem in a line. The answer must be accurate to 1 decimal place.
    * SAMPLE INPUT: 20 2 15 13 10 18
    * SAMPLE OUTPUT:
    14.0
 */
import java.util.*;

public class Grading {
    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);
        int P, T, G1, G2, G3, GJ;
        while(cin.hasNext()){
            // read P, T
            P = cin.nextInt();
            T = cin.nextInt();
            // read G1, G2, G3, GJ
            G1 = cin.nextInt();
            G2 = cin.nextInt();
            G3 = cin.nextInt();
            GJ = cin.nextInt();

            int diff13, diff23;
            diff13 = Math.abs(G1 - G3);
            diff23 = Math.abs(G2 - G3);
            // if difference between G1 and G2 is less than T,
            // Output the average of G1 and G2
            if (Math.abs(G1 - G2) <= T) {
                System.out.println(String.format("%.1f", (G1 + G2) / 2f));
            }
            // If G3 is within the tolerance with both G1 and G2,
            // then this problem's grade will be the maximum
            // of the three grades.
            else if(diff13 <= T && diff23 <= T){
                int r = G1;
                if (r < G2)
                    r = G2;
                if (r < G3)
                    r = G3;
                System.out.println(String.format("%.1f", (r + 0.0f)));
            }
            // If G3 is within the tolerance with either G1 or G2,
            // but NOT both, then this problem's grade will be
            // the average of G3 and the closest grade.
            else if(diff13 <= T || diff23 <= T){
                if (diff13 < diff23)
                    System.out.println(String.format("%.1f", (G1 + G3) / 2f));
                else
                    System.out.println(String.format("%.1f", (G2 + G3) / 2f));
            }
            // If G3 is within the tolerance with neither G1 nor G2,
            // a judge will give the final grade GJ.
            else
                System.out.println(String.format("%.1f", GJ + 0.0f));
        }
    }
}
