
/**
 * AUTHOR: Jolly Wing
 * CREATE: 2013-07-18
 */

// 有未实现的方法必须声明为抽象类
// public abstract class Animal
public class Animal
{
    protected String name;
    private String favoriteFood;
    private int legs;

    public static final String CLASS = "Animal";

    // abstract class has no constructor
    public Animal(String name, String food, int legs) {
        this.name = name;
        favoriteFood = food;
        this.legs = legs;
    }

    // 未实现的方法必须声明为抽象
    // public abstract void walk();

    protected void walk() {
        if(legs > 0) {
            System.out.printf("%s walks with %d legs.\n",
                              name, legs);
        }
        else
            System.out.println(name + " can not walk.");
    }

    protected void eat() {
        System.out.println(name + " like to eat " + favoriteFood + ".");
    }

    protected void sleep() {
    }
}
