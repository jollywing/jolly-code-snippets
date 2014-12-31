
public class StringCompareTest {
    public static void main(String[] args){
        String s1 = "Hello";
        String s2 = "Hello";
        // assert pass, because both s1 and s2 point to the same const object.
        assert s1 == s2;

        String s3 = new String("World!");
        String s4 = new String("World!");
        // AssertionError, because s3 and s4 are different object
        // assert s3 == s4;
        assert s3 != s4;
        // assert pass, equals are used to compare the contents of two strings.
        assert s3.equals(s4);

        String s5 = new String("");
        // AssertionError, don't examine an empty string with '=='
        // assert s5 == "";
        
    }
}
