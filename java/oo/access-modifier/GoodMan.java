
public class GoodMan {
    public static void main(String[] args) {
        Priest man = new Priest();
        man.age = 16;
        man.name = "John";
        System.out.println("Good man " + man.name + " is " + man.age + " years old.");

    }
}

class Priest {
    protected int age;          // sub-type access besides package access
    String name;                // package access
}
