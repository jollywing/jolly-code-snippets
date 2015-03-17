
enum Direction {
    EAST,
    WEST,
    SOUTH,
    NORTH;
}

public class SimpleEnum {
    public static void main(String args[]){
        Direction d = Direction.EAST;
        // switch case 的标签必须为枚举常量
        switch(d) {
        case EAST:
            System.out.println("Dragon");
            break;
        case WEST:
            System.out.println("Tiger");
            break;
        case SOUTH:
            System.out.println("Peacock");
            break;
        case NORTH:
            System.out.println("Tortoise");
        }
    }
}
