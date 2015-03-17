
public class SplitString {
    public static void main(String args[]) {
        String test = "100  1000 89  45";
        // split test str with 1+ spaces
        String [] results = test.split("\\s+");
        for(String str : results){
            System.out.println(str + "$");
        }
    }
}
