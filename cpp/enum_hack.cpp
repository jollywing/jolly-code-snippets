
class Game {
private:
    // static const int GameTurn;
    enum {GameTurn = 10};
    int scores[GameTurn];

public:
    void init_scores() {
        for (int i = 0; i < GameTurn; i++) {
            scores[i] = 0;
        }
    }
};

// 不在这里定义也可以编译通过，为什么？
// const int Game::GameTurn = 10;

int main()
{
    Game game;
    game.init_scores();
    return 0;
}
