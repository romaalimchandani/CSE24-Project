#include "Triangle.h"
#include <GL/freeglut.h>

Triangle::Triangle() {
    x = 0.0;
    y = 0.0;
    base = 0.4;
    height = 0.4;
    r = 0.0;
    g = 0.0;
    b = 0.0;
}

Triangle::Triangle(float x, float y, float base, float height, float r, float g, float b) {
    this->x = x;
    this->y = y;
    this->base = base;
    this->height = height;
    this->r = r;
    this->g = g;
    this->b = b;
}

void Triangle::draw() {
    glColor3f(r, g, b);
    
    glBegin(GL_POLYGON);
        glVertex2f(x - base/2, y - height/2);
        glVertex2f(x, y + height/2);
        glVertex2f(x + base/2, y - height/2);
    glEnd();
}

bool Triangle::contains(float mx, float my) {
    float area = base * height / 2.0;
    float area1 = std::abs((x * ( y + height / 2) + mx * (y - height / 2) + (x + base / 2) * (y + height / 2)) / 2.0);
    float area2 = std::abs((x * ( y - height / 2) + mx * (y - height / 2) + (x + base / 2) * (y - height / 2)) / 2.0);
    float area3 = std::abs((x * ( y + height / 2) + mx * (y + height / 2) + (x + base / 2) * (y - height / 2)) / 2.0);

    if (area1 + area2 + area3 <= area) {
        return true;
    }
    return false;
}

void Triangle::setColor(float r, float g, float b) {
    this->r = r;
    this->g = g;
    this->b = b;
}