
class MultiDimArray {

    static class GreenTree {
        int height;
        int age;
        public GreenTree(int h, int a){
            height = h;
            age = a;
        }

        public int height(){
            return height;
        }

        public int age() {
            return age;
        }
    }

    public static void printArray(byte [][] a) {
        // the dimension of array: a.length
        if(a == null || a.length == 0)
            return;

        int d1 = a.length;
        int d2 = a[0].length;

        for(int i = 0; i < d1; i ++) {
            for(int j = 0; j < d2; j ++) {
                System.out.print("" + a[i][j]);
                if (j < d2 - 1)
                    System.out.print("\t");
                else
                    System.out.print("\n");
            }
        }

        System.out.println("");
    }

    public static void main(String args[]) {
        byte [][] a;
        int d1 = 5;
        int d2 = 10;

        // all elements will be 0
        a = new byte[d1][d2];

        // dump
        printArray(a);

        for(int i = 0; i < d1; i ++) {
            for(int j = 0; j < d2; j ++) {
                a[i][j] = (byte)(i * j);
            }
        }

        printArray(a);

        System.out.println("------------------------------");

        GreenTree [][] trees;
        trees = new GreenTree[d1][d2];
        for(int i = 0; i < d1; i ++) {
            for(int j = 0; j < d2; j ++) {
                trees[i][j] = new GreenTree(i, j);
                System.out.print("(" + trees[i][j].height()
                                 + ", " + trees[i][j].age() +")");
                if (j < d2 - 1)
                    System.out.print("\t");
                else
                    System.out.print("\n");
            }
        }

    }
}
