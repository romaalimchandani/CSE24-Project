#ifndef SCRIBBLE_H
#define SCRIBBLE_H

#include "Shape.h"
#include "Point.h"
#include <vector>

class Scribble : public Shape {
private:
    std::vector<Point*> points;

public:
    Scribble() = default;
    ~Scribble();

    void addPoint(float x, float y, float r, float g, float b, int size);

    void draw() override;
    bool contains(float mx, float my) override;
    void setColor(float r, float g, float b) override;
    void moveBy(float dx, float dy) override;
    void resize(float size) override {} // Not applicable for scribble
};

#endif
