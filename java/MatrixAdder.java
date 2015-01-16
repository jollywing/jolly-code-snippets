import java.util.Scanner;

public class MatrixAdder
{
    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);
        int M, N;
        int [][] matrix1;
        int [][] matrix2;
        int [][] matrix3;
        while(cin.hasNext()){
            M = cin.nextInt();
            // if M is 0, exit loop
            if(M == 0){
                break;
            }
            N = cin.nextInt();
            if (M > 0 && N > 0) {
                matrix1 = new int[M][N];
                matrix2 = new int[M][N];
                matrix3 = new int[M][N];

                int i, j;
                // if M > 0 and N > 0, read matrix1
                for (i = 0; i < M; i++) {
                    for (j = 0; j < N; j++) {
                        matrix1[i][j] = cin.nextInt();
                    }
                }
                // read matrix2
                for (i = 0; i < M; i++) {
                    for (j = 0; j < N; j++) {
                        matrix2[i][j] = cin.nextInt();
                    }
                }
                // add two matrix, stored in matrix3
                for (i = 0; i < M; i++) {
                    for (j = 0; j < N; j++) {
                        matrix3[i][j] = matrix1[i][j] + matrix2[i][j];
                    }
                }

                int [] rowSums = new int[M];
                for (i = 0; i < M; i++) {
                    rowSums[i] = 0;
                }

                int [] colSums = new int[N];
                for (i = 0; i < N; i++) {
                    colSums[i] = 0;
                }

                for (i = 0; i < M; i++) {
                    for (j = 0; j < N; j++) {
                        rowSums[i] += matrix3[i][j];
                        colSums[j] += matrix3[i][j];
                    }
                }

                int zeroLines = 0, zeroCols = 0;
                for (i = 0; i < M; i++) {
                    if (rowSums[i] == 0) {
                        zeroLines ++;
                    }
                }

                for (i = 0; i < N; i++) {
                    if (colSums[i] == 0) {
                        zeroCols ++;
                    }
                }

                System.out.println(zeroLines + zeroCols);
            }
        }
    }
}
