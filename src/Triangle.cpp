#include "Triangle.h"
#include <GL/freeglut.h>
#include <cmath>

Triangle::Triangle() {
    x = 0.0f;
    y = 0.0f;
    base = 0.4f;
    height = 0.4f;
    r = g = b = 0.0f;
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
        glVertex2f(x - base / 2, y - height / 2); // Bottom-left
        glVertex2f(x,            y + height / 2); // Top-center
        glVertex2f(x + base / 2, y - height / 2); // Bottom-right
    glEnd();
}

bool Triangle::contains(float mx, float my) {
    // Triangle vertices (match draw order)
    float x1 = x - base / 2, y1 = y - height / 2;
    float x2 = x,            y2 = y + height / 2;
    float x3 = x + base / 2, y3 = y - height / 2;

    auto triangleArea = [](float ax, float ay, float bx, float by, float cx, float cy) {
        return std::abs((ax * (by - cy) + bx * (cy - ay) + cx * (ay - by)) / 2.0f);
    };

    float totalArea = triangleArea(x1, y1, x2, y2, x3, y3);
    float a1 = triangleArea(mx, my, x2, y2, x3, y3);
    float a2 = triangleArea(x1, y1, mx, my, x3, y3);
    float a3 = triangleArea(x1, y1, x2, y2, mx, my);

    return std::abs((a1 + a2 + a3) - totalArea) < 0.01f;
}

void Triangle::setColor(float r, float g, float b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

void Triangle::moveBy(float dx, float dy) {
    x += dx;
    y += dy;
}

void Triangle::resize(float sizeFactor) {
    base = sizeFactor;
    height= sizeFactor;

    if (base < 0.05f) base = 0.05f;
    if (height < 0.05f) height = 0.05f;
}
