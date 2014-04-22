#include <iostream>
using std::cout;
using std::endl;

class Cup {
    int height;
    float radius;

    class Cover {
        float radius;
        Cup * cup;
    public:
        inline void set_cup(Cup *c){cup = c;};
        inline float get_radius(){return cup->get_radius() + 0.5;};
    };

    Cover c;

public:
    Cup(int h, float r) {
        height = h;
        radius = r;
        c.set_cup(this);
    }

    int get_height() {
        return height;
    }

    float get_radius(){
        return radius;
    }
};

int main(int argc, char *argv[])
{
    Cup cup(10, 5.5);
    cout << "Height: " << cup.get_height() <<
            "; Radius: " << cup.get_radius() << endl;
    return 0;
}
