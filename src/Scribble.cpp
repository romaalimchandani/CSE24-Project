#include "Scribble.h"

void Scribble::addPoint(float x, float y, float r, float g, float b, int size) {
    points.push_back(new Point(x, y, r, g, b, size));
}

void Scribble::draw() {
    for (Point* p : points) {
        p->draw();
    }
}

Scribble::~Scribble() {
    for (Point* p : points) {
        delete p;
    }
    points.clear();
}

bool Scribble::contains(float mx, float my) {
    const float threshold = 5.0f; // pixel distance threshold for click
    for (Point* p : points) {
        float dx = p->getX() - mx;
        float dy = p->getY() - my;
        if (dx * dx + dy * dy <= threshold * threshold) {
            return true;
        }
    }
    return false;
}

void Scribble::setColor(float r, float g, float b) {
    for (Point* p : points) {
        p->setColor(r, g, b);
    }
}

void Scribble::moveBy(float dx, float dy) {
    for (Point* p : points) {
        p->moveBy(dx, dy);
    }
}
