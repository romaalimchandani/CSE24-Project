#ifndef APPLICATION_H
#define APPLICATION_H

#include <bobcat_ui/all.h>
#include "Toolbar.h"
#include "Canvas.h"
#include "ColorSelector.h"

class Application : public bobcat::Application_ {
    bobcat::Window* window;
    Toolbar* toolbar;
    Canvas* canvas;
    ColorSelector* colorSelector;
    Shape* selectedShape;

    int pointerSize;
    bool dragging = false;
    float dragOffsetX = 0, dragOffsetY = 0;

    void onCanvasMouseDown(bobcat::Widget* sender, float mx, float my);
    void onCanvasDrag(bobcat::Widget* sender, float mx, float my);
    void onToolbarChange(bobcat::Widget* sender);
    void onColorSelectorChange(bobcat::Widget* sender);
    void onCanvasMouseUp(bobcat::Widget* sender, float mx, float my);

public:
    Application();

    friend struct::AppTest;
};

#endif
