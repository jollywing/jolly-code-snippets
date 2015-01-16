public class Test {
    public static void main(String[]args){
        char a='1';
        String b[]={"公共的","私有的","受保护的"};
        boolean c[]=new boolean[b.length];
        for(int i=0;i<5;i++){
            int e;
            do{
                e=(int)(Math.random()*b.length);
                System.out.println(e + ',' + c[e]);
            }while(c[e]);
            a=b[e];
            c[e]=true;
        }
        return;
    }
}
