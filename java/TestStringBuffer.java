
class TestStringBuffer
{
    public static void main(String [] args){
        // java.lang.StringBuffer
        String helloStr = "Hello, world!";
        // convert string to stringbuffer
        StringBuffer s = new StringBuffer(helloStr);
        // append string to a Stringbuffer object
        s.append(" My name is John.");
        // StringBuffer.insert(offset, String)
        s.insert(0, "Oh! ");
        // change char on a certain location
        s.setCharAt(10, 'X');
        // delete char on a certain location
        s.deleteCharAt(10);
        // delete a char sequence
        s.delete(10, 16);
        // reverse the char sequence
        s.reverse();
        // convert stringbuffer to string
        System.out.println(s.toString());
        // reverse the char sequence
        s.reverse();
        // convert stringbuffer to string
        System.out.println(s.toString());
    }
}
