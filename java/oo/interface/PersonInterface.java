/**
 * AUTHOR: Jolly Wing
 * CREATE: 2013-07-04
 */

// 接口中只能定义常量和抽象方法
// 方法默认都是 public abstract，常量用 public static final 修饰
public interface PersonInterface {
    void eat(String food);
    void walk(int speed, int targetX, int targetY);
    void sleep(int beginTime, int interval);
}
