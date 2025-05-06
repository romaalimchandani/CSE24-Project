#include "Polygon.h"
#include <GL/freeglut.h>
#include <cmath>

Polygon::Polygon() {
    x = 0.0;
    y = 0.0;
    sides = 5;
    length = 0.1;
    r = 0.0;
    g = 0.0;
    b = 0.0;
}

Polygon::Polygon(float x, float y, int sides, float length, float r, float g, float b) {
    this->x = x;
    this->y = y;
    this->sides = sides;
    this->length = length;
    this->r = r;
    this->g = g;
    this->b = b;
}

void Polygon::draw() {
    glColor3f(r, g, b);
    
    glBegin(GL_POLYGON);
        float inc = 2 * M_PI / sides;

        for (float theta = 0; theta < 2 * M_PI; theta += inc) {
            glVertex2f(x + length * cos(theta), y + length * sin(theta));
        }
    glEnd();
}

bool Polygon::contains(float mx, float my) {
    int count = 0;
    float angle;
    for (int i = 0; i < sides; i++) {
        angle = atan2(my - y, mx - x);
        if (angle >= 0) {
            count++;
        }
    }
    if (count % 2 == 1) {
        return true;
    }
    return false;
}

void Polygon::setColor(float r, float g, float b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

void Polygon::moveBy(float dx, float dy) {
    x += dx;
    y += dy;
}

void Polygon::resize(float size) {
     this->length *= size;
     
     if (length < 0.05) {
         length = 0.05;
     }
 }
