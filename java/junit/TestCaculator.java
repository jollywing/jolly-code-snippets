
import junit.framework.TestCase;

public class TestCaculator extends TestCase {
    public void testAdd(){
        Caculator calc = new Caculator();
        assertEquals(25, calc.add(12, 13));
    }
}
