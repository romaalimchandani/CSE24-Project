#include "Application.h"
#include "Enums.h"
#include "Scribble.h"
#include <bobcat_ui/bobcat_ui.h>

using namespace bobcat;
using namespace std;

void Application::onCanvasMouseDown(bobcat::Widget* sender, float mx, float my) {
    TOOL tool = toolbar->getTool();
    Color color = colorSelector->getColor();
    canvas->lastClickX = mx;
    canvas->lastClickY = my;

    if (tool == MOUSE) {
        selectedShape = canvas->getSelectedShape(mx, my);
        if (selectedShape) {
            dragging = true;
            dragOffsetX = mx;
            dragOffsetY = my;
        }
    }
    else if (tool == PENCIL) {
        selectedShape = new Scribble();
        canvas->addShape(selectedShape);
        selectedShape->setColor(color.getR(), color.getG(), color.getB());
        selectedShape->moveBy(mx, my);
        static_cast<Scribble*>(selectedShape)->addPoint(mx, my, color.getR(), color.getG(), color.getB(), pointerSize);
        dragging = true;
        canvas->redraw();
    }
    else if (tool == ERASER) {
        selectedShape = nullptr;
        canvas->addPoint(mx, my, 1.0, 1.0, 1.0, pointerSize + 7);
        canvas->redraw();
    }
    else if (tool == RECTANGLE) {
        canvas->addRectangle(mx, my, color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }
    else if (tool == CIRCLE) {
        canvas->addCircle(mx, my, color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }
    else if (tool == TRIANGLE) {
        canvas->addTriangle(mx, my, color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }
    else if (tool == POLYGON) {
        canvas->addPolygon(mx, my, color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }
}

void Application::onCanvasDrag(bobcat::Widget* sender, float mx, float my) {
    TOOL tool = toolbar->getTool();
    Color color = colorSelector->getColor();

    if (tool == PENCIL && selectedShape) {
        static_cast<Scribble*>(selectedShape)->addPoint(mx, my, color.getR(), color.getG(), color.getB(), pointerSize);
        canvas->redraw();
    }
    else if (tool == ERASER) {
        canvas->addPoint(mx, my, 1.0, 1.0, 1.0, pointerSize + 7);
        canvas->redraw();
    }
    else if (tool == MOUSE && dragging && selectedShape) {
        float dx = mx - dragOffsetX;
        float dy = my - dragOffsetY;
        selectedShape->moveBy(dx, dy);
        dragOffsetX = mx;
        dragOffsetY = my;
        canvas->redraw();
    }
}

void Application::onCanvasMouseUp(bobcat::Widget* sender, float mx, float my) {
    dragging = false;
}

void Application::onToolbarChange(bobcat::Widget* sender) {
    TOOL tool = toolbar->getTool();

    if (tool == PENCIL || tool == ERASER) {
        selectedShape = nullptr;
    }

    ACTION action = toolbar->getAction();

    if (action == CLEAR) {
        canvas->clear();
        canvas->redraw();
    }
    else if (action == BRING_TO_FRONT) {
        canvas->bringToFront();
        canvas->redraw();
    }
    else if (action == SEND_TO_BACK) {
        canvas->sendToBack();
        canvas->redraw();
    }
    else if (action == MINUS) {
        if (selectedShape) {
            selectedShape->resize(0.9);
        } else if (pointerSize > 1) {
            pointerSize--;
        }
        canvas->redraw();
    }
    else if (action == PLUS) {
        if (selectedShape) {
            selectedShape->resize(1.1);
        } else if (pointerSize < 50) {
            pointerSize++;
        }
        canvas->redraw();
    }

    toolbar->clearAction();
}

void Application::onColorSelectorChange(bobcat::Widget* sender) {
    Color color = colorSelector->getColor();

    if (selectedShape) {
        selectedShape->setColor(color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }
}

Application::Application() {
    pointerSize = 7;
    dragging = false;
    selectedShape = nullptr;

    window = new Window(25, 75, 500, 400, "Project");

    toolbar = new Toolbar(0, 0, 100, 400);
    canvas = new Canvas(100, 0, 400, 350);
    colorSelector = new ColorSelector(100, 350, 400, 50);
    colorSelector->box(FL_BORDER_BOX);

    window->add(toolbar);
    window->add(canvas);
    window->add(colorSelector);

    ON_MOUSE_DOWN(canvas, Application::onCanvasMouseDown);
    ON_DRAG(canvas, Application::onCanvasDrag);
    ON_MOUSE_UP(canvas, Application::onCanvasMouseUp);
    ON_CHANGE(toolbar, Application::onToolbarChange);
    ON_CHANGE(colorSelector, Application::onColorSelectorChange);

    window->show();
}
