/**
 * AUTHOR: Jolly Wing
 * CREATE: 2013-07-04
 */

// If 'Person' is not a Abstract class,
// it must implement all methods declared in PersonInterface.
// all methods of interface must be daclared as PUBLIC.
// 这是因为如果不加 public 修饰符，默认的访问权限是包级访问权限，
// 即同一目录下其他类可以访问。
public class Person implements PersonInterface {
    private String name;
    private int age;
    private char sex;

    public Person() {
        name = "NONAME";
        age = 18;
        sex = 'F';
    }

    public Person(String _name, int _age, char _sex) {
        name = _name;
        age = _age;
        sex = _sex;
    }

    public void eat(String food) {
        System.out.println(name + " eat " + food + ".");
    }

    public void walk(int speed, int targetX, int targetY) {
        System.out.println(name + " walk towards (" + targetX
                           + ", " + targetY + ") at speed of " + speed);
    }
    
    public void sleep(int beginTime, int interval) {
        System.out.println(name + " go to bed at " + beginTime +
                           ", get up at " + (beginTime + interval));
    }

    public static void main (String [] args) {
        Person p = new Person("Ming", 18, 'M');
        p.eat("ice cream");
        p.sleep(6, 12);
    }
}
