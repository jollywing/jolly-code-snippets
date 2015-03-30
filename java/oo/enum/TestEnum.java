
// NOTICE: the type is 'enum', not 'Enum'
// enum is a special class
// it has a method 'enum.values()'
// You can even define new methods in your enum.
// each enum constant is a instance of the enum class.

// If 'public enum Day{...'
// Then you need define 'Day' in Day.java 
enum Day {
    MONDAY, TUESDAY, WEDNESDAY, THURSDAY,
        FRIDAY, SATURDAY, SUNDAY
}

enum Direction {
    EAST ("East", 0),
    SOUTH ("South", 90),
    WEST ("West", 180),
    NORTH ("North", 270);

    private final int degree;
    private final String name;

    // enum's constructor can not be decorated with 'public'
    // Of course you can not decorate it with 'protected',
    // which is meaningless.
    // you can decorate it with 'private'
    // OR you can decorate it with nothing.
    Direction(String name, int degree) {
        this.name = name;
        this.degree = degree;
    }

    public String getName() {
        return name;
    }

    public int getDegree() {
        return degree;
    }
}

// without public, a class can be accessed by other classes
// in the same directory.
// with public decorated, it can be accessed anywhere.
// A class CAN NOT be decorated with PRIVATE and PROTECTED.
public class TestEnum {
    Day day;

    // The constructor can be declared as PRIVATE,
    // in that case, we can't get the Instance with constructor.
    public TestEnum(Day _day) {
        day = _day;
    }

    public void commentDay() {
        System.out.println("" + day);
        switch(this.day) {
            // You Should not ref a enum constant like Day.MONDAY.
        case MONDAY:
            System.out.println("Moday is bad.");
            break;
        case FRIDAY:
            System.out.println("Friday is better.");
            break;
        case SATURDAY:
        case SUNDAY:
            System.out.println("Weekends is the best!");
            break;
        default:
            System.out.println("MidDays are neither good nor bad.");
        }
    }

    public static void main(String [] args) {
        for(Day d: Day.values()) {
            TestEnum test = new TestEnum(d);
            test.commentDay();
        }
        
        for(Direction dir: Direction.values()){
            System.out.println(dir.getName() + "\'s degree is " + dir.getDegree());
        }
    }
}
