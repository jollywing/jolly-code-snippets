
class Circle {
    double _x;
    double _y;
    double _r;
public:
    Circle(double x, double y, double r):_x(x),_y(y),_r(r) {}

    double area() {
        static const double PI = 3.1415926;
        return PI * _r * _r;
    }

    double perimeter() {
        static const double PI = 3.1415926;
        return PI * _r * 2;
    }
};
