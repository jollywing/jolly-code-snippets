import java.util.Scanner;

public class Adder
{
    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);
        int a, b;
        while(cin.hasNext()){
            a = cin.nextInt();
            b = cin.nextInt();
            System.out.println(a + b);
        }
    }
}
