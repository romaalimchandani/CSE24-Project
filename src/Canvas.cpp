#include "Canvas.h"
#include <GL/freeglut.h>
#include <algorithm>
#include <iostream>

Canvas::Canvas(int x, int y, int w, int h) : Canvas_(x, y, w, h) {}

void Canvas::addShape(Shape* shape) {
    objects.push_back(shape);
}

void Canvas::addPoint(float x, float y, float r, float g, float b, int size) {
    // If you're still supporting point tool, you can wrap it as a Shape
    objects.push_back(new Point(x, y, r, g, b, size));
}

void Canvas::addRectangle(float x, float y, float r, float g, float b) {
    objects.push_back(new Rectangle(x, y, r, g, b));
}

void Canvas::addCircle(float x, float y, float r, float g, float b) {
    objects.push_back(new Circle(x, y, r, g, b));
}

void Canvas::addTriangle(float x, float y, float r, float g, float b) {
    objects.push_back(new Triangle(x, y, 0.4f, 0.4f, r, g, b));
}

void Canvas::addPolygon(float x, float y, float r, float g, float b) {
    objects.push_back(new Polygon(x, y, 5, 0.2f, r, g, b));
}

const std::vector<Shape*>& Canvas::getShapes() const {
    return objects;
}

void Canvas::clear() {
    for (Shape* s : objects) {
        delete s;
    }
    objects.clear();
}

void Canvas::render() {
    for (Shape* s : objects) {
        s->draw();
    }
}

void Canvas::bringToFront() {
    for (unsigned int i = 0; i < objects.size(); ++i) {
        if (objects[i]->contains(lastClickX, lastClickY)) {
            Shape* s = objects[i];
            objects.erase(objects.begin() + i);
            objects.push_back(s);
            break;
        }
    }
}

void Canvas::sendToBack() {
    for (unsigned int i = 0; i < objects.size(); ++i) {
        if (objects[i]->contains(lastClickX, lastClickY)) {
            Shape* s = objects[i];
            objects.erase(objects.begin() + i);
            objects.insert(objects.begin(), s);
            break;
        }
    }
}

Shape* Canvas::getSelectedShape(float mx, float my) {
    for (auto it = objects.rbegin(); it != objects.rend(); ++it) {
        if ((*it)->contains(mx, my)) {
            return *it;
        }
    }
    return nullptr;
}
