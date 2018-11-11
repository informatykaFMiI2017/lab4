#include "triangle.h"
#include "sl.h"
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

void Triangle::draw() {
    slLine(p1.getX(), p1.getY(), p2.getX(), p2.getY());
    slLine(p2.getX(), p2.getY(), p3.getX(), p3.getY());
    slLine(p3.getX(), p3.getY(), p1.getX(), p1.getY());
};

void Rectangle::draw() {
    slLine(p4.getX(), p4.getY(), p5.getX(), p5.getY());
    slLine(p5.getX(), p5.getY(), p6.getX(), p6.getY());
    slLine(p6.getX(), p6.getY(), p7.getX(), p7.getY());
    slLine(p7.getX(), p7.getY(), p4.getX(), p4.getY());
};

void Circle::draw() { slCircleOutline(p.getX(), p.getY(), radius, numVertex); };

double Rectangle::area() { return (fabs(p5.getX() - p4.getX())) * (fabs((p7.getY() - p4.getY()))); };

double Triangle::area() {
    return (fabs(p1.getX() * p2.getY() + p2.getX() * p3.getY() - p1.getX() * p3.getY() - p3.getX() * p2.getY() -
                 p2.getX() * p1.getY())) /
           2;
};

double Circle::area() { return 3.14 * pow(getRadius(), 2); };

bool Rectangle::hasGreaterArea(Polygon* e) { return this->area() > e->area(); };

bool Circle::hasGreaterArea(Polygon* e) { return this->area() > e->area(); };

bool Triangle::hasGreaterArea(Polygon* e) { return this->area() > e->area(); };

void Square::draw() { Rectangle::draw(); };

double Square::area() { Rectangle::area(); };

bool Square::hasGreaterArea(Polygon* a) { Rectangle::hasGreaterArea(a); };

Factory::~Factory() {
    for (int i = 0; i < arr.size(); ++i) {
        delete arr[i];
    }
};

void Factory::createFigure(int type) {
    Polygon* figure;
    switch (type) {
    case 0:
        figure = createSquare();
        break;

    case 1:
        figure = createCircle();
        break;

    default:
        break;
    }
    sum += figure->area();
    arr.push_back(figure);
};

Polygon* Factory::createSquare() {
    int x = slGetMouseX(), y = slGetMouseY();

    if (x < 50 || x > 450 || y < 50 || y > 450)
        throw WrongInputException("Wrong input data.");

    Point p1(x - 50, y - 50);
    Point p2(x + 50, y - 50);
    Point p3(x + 50, y + 50);
    Point p4(x - 50, y + 50);

    return new Square(p1, p2, p3, p4);
};

Polygon* Factory::createSquare(int x, int y) {
    if (x < 50 || x > 450 || y < 50 || y > 450)
        throw WrongInputException("Wrong input data.");

    Point p1(x - 50, y - 50);
    Point p2(x + 50, y - 50);
    Point p3(x + 50, y + 50);
    Point p4(x - 50, y + 50);

    return new Square(p1, p2, p3, p4);
};

Polygon* Factory::createCircle() {
    int x = slGetMouseX(), y = slGetMouseY();

    if (x < 50 || x > 450 || y < 50 || y > 450)
        throw WrongInputException("Wrong input data.");

    Point p(x, y);

    return new Circle(p, 50, 50);
};

void Factory::draw() {
    for (int i = 0; i < arr.size(); ++i) {
        arr[i]->draw();
    }
};

double Factory::getSum() { return sum; };

const char* WrongInputException::what() const throw() { return message.c_str(); };

CFile::CFile(const char* name) {
    if ((file = fopen(name, "rw")) == NULL)
        throw std::runtime_error("Cannot open file");
        //std::cout << "Cannot open a file." << std::endl;
};

CFile::~CFile() {
    std::cout << "Destructor CFile" << std::endl;
    fclose(file);
};

void CFile::write(const std::string& text) { fwrite(text.c_str(), sizeof(char), text.size(), file); };