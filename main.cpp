#include "sl.h"
#include "triangle.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

int main() {
    slWindow(500, 500, "Simple SIGIL Example", false);
    slSetFont(slLoadFont("arial.ttf"), 20);
    slSetTextAlign(SL_ALIGN_LEFT);

    /*
    Point p1(100, 100);
    Point p2(200, 200);
    Point p3(300, 100);

    //Create a Triangle object
    Triangle t1(p1, p2, p3);

    Point p4(50, 50);
    Point p5(450, 50);
    Point p6(450, 350);
    Point p7(50, 350);

    //Create a Rectangle object
    Rectangle r1(p4, p5, p6, p7);

    Point p8(280, 280);

    //Create a Circle object
    Circle c1(p8, 50, 75);

    Point p9(150, 150);
    Point p10(300, 150);
    Point p11(300, 300);
    Point p12(150, 300);

    //Create a Square object
    Square s1(p9, p10, p11, p12);

    Polygon *e1 = &t1; //Polygon e1 = Triangle
    Polygon *e2 = &r1; //Polygon e2 = Rectangle
    Polygon *e3 = &c1; //Polygon e3 = Circle
    Polygon *e4 = &s1; //Polygon e4 = Square

    std::cout << "Area Triangle: " << e1->area() << std::endl;
    std::cout << "Area Rectangle: " << e2->area() << std::endl;
    std::cout << "Area Circle: " << e3->area() << std::endl;
    std::cout << "Area Square: " << e4->area() << std::endl;

    //Check the area of ​​the triangle and rectangle
    if (e2->hasGreaterArea(e1))
        std::cout << "Rectangle has greater area than Triangle" << std::endl;
    else
        std::cout << "Triangle has greater area than Rectangle " << std::endl;

    //Check the area of ​​the triangle and circle
    if (e3->hasGreaterArea(e1))
        std::cout << "Circle has greater area than Triangle" << std::endl;
    else
        std::cout << "Triangle has greater area than Circle" << std::endl;
    */

    std::cout << "Size of the class Triangle: " << sizeof(Triangle) << std::endl;
    std::cout << "Size of the class Rectangle: " << sizeof(Rectangle) << std::endl;
    std::cout << "Size of the class Rhombus: " << sizeof(Rhombus) << std::endl;
    std::cout << "Size of the class Circle: " << sizeof(Circle) << std::endl;
    std::cout << "Size of the class Square: " << sizeof(Square) << std::endl;

    // arr.push_back(e1);
    // arr.push_back(e2);
    // arr.push_back(e3);
    // arr.push_back(e4);

    Factory factory = Factory();

    try {
        {
            CFile file("test.txt");
            factory.createSquare(0, 0);
            file.write("12345");
        }
    } catch (WrongInputException& ex) {
        std::cout << ex.what() << std::endl;
    }

    {
        //CFile stackFile("test2.txt");
        //stackFile.write("test2");
        //std::cout << "Destroy file on stack:" << std::endl;
    }

    CFile* heapFile = new CFile("test3.txt");
    heapFile->write("test3");
    std::cout << "Destroy file on heap:" << std::endl;
    delete heapFile;

    int isClicked = 0;
    while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE)) {
        slSetForeColor(1.0, 0.3, 0.5, 1.0);

        double sum = 0;
        if (slGetMouseButton(SL_MOUSE_BUTTON_1) && isClicked == 0) {
            try {
                factory.createFigure(0);
                factory.createFigure(1);
            } catch (WrongInputException& ex) {
                std::cout << ex.what() << std::endl;
            }
        }

        // e1->draw(); //t1.draw() Triangle
        // e2->draw(); //r1.draw() Rectangle
        // e3->draw(); //t1.draw() Circle

        factory.draw();

        // We can call a square drawRectangle method
        // on the object that draws a triangle because
        // the Square class inherits from the Rectangle class
        // e4->draw(); //s1.draw() Square

        slSetForeColor(0.7, 0.7, 0.7, 1.0);

        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << factory.getSum();
        std::string text = stream.str();
        slText(0, 0, text.c_str());

        isClicked = slGetMouseButton(SL_MOUSE_BUTTON_1);
        slRender(); // draw everything
    }
    slClose(); // close the window and shut down SIGIL
    return 0;
}