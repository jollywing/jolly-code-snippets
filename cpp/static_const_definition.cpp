#include <iostream>
using namespace std;

class Game {
private:
    // 这里只是声明.
    // 比较老的编译器可能不支持类内初始化。
    static const int MAX_TURN = 100;
public:
    void max_turn() {
        cout << Game::MAX_TURN << endl;
    }
};

// const 是必须的，因为const int 和 int 是两个不同的变量。
// 因为声明时已经指定了初始值，所以这里不需要再指定。
const int Game::MAX_TURN;
// 如果再给MAX_TURN指定初始值，会报错，重复初始化。
// const int Game::MAX_TURN = 100;

int main()
{
    Game game;
    game.max_turn();
    return 0;
}
