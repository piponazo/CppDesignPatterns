#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Canvas {
  std::vector<std::string> _shapes;

 public:
  void addShape(const std::string& newShape) {
    _shapes.push_back(newShape);
  }
  void clearAll() {
    _shapes.clear();
  }
  std::vector<std::string> getShapes() const {
    return _shapes;
  }
};

class Button {
 public:
  virtual ~Button() {
  }
  virtual void click() = 0;
};

class AddTriangleButton : public Button {
  Canvas* _canvas;

 public:
  AddTriangleButton(Canvas* canvas) : _canvas(canvas) {
  }
  void click() override {
    _canvas->addShape("triangle");
  }
};

// Note that each new AddXXXButton subclass has duplication of code (reference to canvas)
class AddSquareButton : public Button {
  Canvas* _canvas;

 public:
  AddSquareButton(Canvas* canvas) : _canvas(canvas) {
  }
  void click() override {
    _canvas->addShape("square");
  }
};

class AddClearButton : public Button {
  Canvas* _canvas;

 public:
  AddClearButton(Canvas* canvas) : _canvas(canvas) {
  }
  void click() override {
    _canvas->clearAll();
  }
};

int main() {
  return EXIT_SUCCESS;
}