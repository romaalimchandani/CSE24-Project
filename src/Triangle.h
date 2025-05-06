#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"

class Triangle : public Shape {
private:
    float x = 0.0f;
    float y = 0.0f;
    float base = 0.4f;
    float height = 0.4f;
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;

public:
    Triangle();
    Triangle(float x, float y, float base, float height, float r, float g, float b);

    void draw() override;
    bool contains(float mx, float my) override;
    void setColor(float r, float g, float b) override;
    void moveBy(float dx, float dy) override;
    void resize(float sizeFactor) override;

    friend struct AppTest;
};

#endif
