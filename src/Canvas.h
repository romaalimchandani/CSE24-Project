#ifndef CANVAS_H
#define CANVAS_H

#include <bobcat_ui/all.h>
#include <vector>
#include "Shape.h"
#include "Scribble.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"
#include "Polygon.h"

class Canvas : public bobcat::Canvas_ {
private:
    std::vector<Shape*> objects;

public:
    float lastClickX;
    float lastClickY;

    Canvas(int x, int y, int w, int h);

    void addShape(Shape* shape); // For scribbles and other tools
    void addPoint(float x, float y, float r, float g, float b, int size);
    void addRectangle(float x, float y, float r, float g, float b);
    void addCircle(float x, float y, float r, float g, float b);
    void addTriangle(float x, float y, float r, float g, float b);
    void addPolygon(float x, float y, float r, float g, float b);

    void clear();
    void render();
    void bringToFront();
    void sendToBack();

    Shape* getSelectedShape(float mx, float my);
    const std::vector<Shape*>& getShapes() const;
};

#endif
