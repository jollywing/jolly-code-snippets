#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TextTestRunner.h>
#include "circle.h"

// make: c++ `pkg-config --cflags --libs` test_demo.cpp

// 1. Fix: import cppunit support
// 2. Test: new a Circle object
// 3. Fix: define a Circle class and its constructor
// 4. display test results with testsuite, 
// 5. fix: import testsuite.h, import testcaller.h
// 6. fix: make circleAreaTest public
// 7. fix: #include <cppunit/TextTestRunner.h>

class CppUnitTestDemo : public CppUnit::TestCase
{
public:
    void runTest(){
        circleAreaTest();
        circlePerimeterTest();
    }

    void circlePerimeterTest()
    {
        const double PI = 3.1415926;
        Circle circle(1.0, 1.0, 133.0);
        double perimeter = PI * 133.0 * 2;
        CPPUNIT_ASSERT(perimeter == circle.perimeter());
    }

    void circleAreaTest()
    {
        const double PI = 3.1415926;
        Circle circle(1.0, 1.0, 2.0);
        double area = PI * 2.0 * 2.0;
        CPPUNIT_ASSERT(area == circle.area());
    }
};

int main()
{
    // Simple TestCase, without output
    // CppUnitTestDemo demo;
    // demo.runTest();

    // TestCase -> TestCaller -> TestSuite -> TestRunner
    CppUnit::TestSuite *suite = new CppUnit::TestSuite("Test Demo");
    suite->addTest(new CppUnit::TestCaller<CppUnitTestDemo>(
                "circleAreaTest", &CppUnitTestDemo::circleAreaTest));
    suite->addTest(new CppUnit::TestCaller<CppUnitTestDemo>(
                "circlePerimeterTest", &CppUnitTestDemo::circlePerimeterTest));
    CppUnit::TextTestRunner runner;
    runner.addTest(suite);
    runner.run();
    return 0;
}
