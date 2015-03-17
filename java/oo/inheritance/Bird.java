
/**
 * AUTHOR: Jolly Wing
 * CREATE: 2013-07-18
 */

// Every class you use or write inherits the instance methods of Object.
public class Bird extends Animal
{
    // 子类如果定义和父类相同的静态变量，则会隐藏父类的变量
    public static final String CLASS = "Bird";

    // 只要field的名字与父类field的名字相同，即使类型不同，也会隐藏父类的field.
    // 对于被隐藏的父类field, 如果想在子类中访问，需要用super, 如：super.varName
    // 隐藏父类的field不提倡，这除了让代码难读，没什么好处。
    private boolean canFly;
    private boolean sleepAtNight;
    
    // 如果一个构造函数没有显式地调用父类的构造函数，
    // Java编译器会自动插入父类不带参数的构造函数，即super().
    // 如果父类没有不带参数的构造函数，编译时会报错。
    public Bird(String name, String food, int legs, boolean fly) {
        // Invocation of a superclass constructor must be the
        // first line in the subclass constructor.
        super(name, food, legs);
        canFly = fly;
    }

    private void setSleepTime(boolean night) {
        sleepAtNight = night;
    }

    // 方法成员可以和数据成员重名
    public void fly() {
        if(canFly)
            System.out.println(name + " can fly.");
        else
            System.out.println(name + " can not fly.");
    }

    // 如果 sleep 是 Animal 的私有方法，则不能在Bird中 override.
    // Override时，可以放宽方法的访问权限，
    // 如父类中的protected方法可以Override为public
    // 但不能Override为private

    // @Override 告诉编译器这是一个覆盖父类的方法，如果父类中没有此方法或不能覆盖，
    // 则编译器会报错
    @Override
    public void sleep() {
        if (sleepAtNight)
            System.out.println(name + " sleeps at night.");
        else
            System.out.println(name + " sleeps at day.");
    }

    public static void main(String [] args) {
        // 隐式转换
        // animal既是一个Animal对象，也是一个Bird对象
        Animal animal = new Bird("Pidgeon", "worms", 2, true);
        // 虽然子类不能访问父类的私有成员，但可以通过父类的非私有方法访问它们
        animal.walk();
        animal.eat();
        // 当实例的类型为Animal时，会引用 Animal.CLASS
        // 而当实例的类型为Bird时，则会引用 Bird.CLASS
        // 这就是 hide 的特性
        // 被隐藏的类方法也一样
        System.out.println(animal.CLASS);
        // 被覆盖的方法则不同，如果一个Animal变量指向Bird的实例
        // 调用被覆盖的方法时，会调用 Bird 中的方法
        animal.sleep();

        // toString() 是 Object class 的方法，
        // 我们写的任何类都继承了Object的方法。
        // 如果我们要调用这些方法，最好重写这些方法。
        System.out.println(animal.toString());
        // 虽然 animal 实际上是一个Bird对象，但它不能直接调用Bird的方法
        // animal.fly();
        // 从父类向子类转换，需要显式转换，
        // 如果运行时检测到父类对象并非子类对象，会抛出异常
        if (animal instanceof Bird) { 
            Bird bird = (Bird)animal;
            System.out.println(bird.CLASS);
            bird.fly();
            // 因为main是Bird的成员函数，所以它能访问Bird的私有函数
            bird.setSleepTime(true);
            bird.sleep();
        }
    }
}
