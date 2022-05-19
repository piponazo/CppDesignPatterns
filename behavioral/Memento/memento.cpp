/* Allow certain objects to save themselves in such a way that they can't be modified - at least until they say so
 *
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Canvas;  // Forward declaration

class CanvasMemento {
  friend class Canvas;  // No other class/function rather than Canvas can modify me
  const std::vector<std::string> _shapes;

 public:
  CanvasMemento(const std::vector<std::string>& shapes) : _shapes(shapes) {
  }
};

class Canvas {
  std::vector<std::string> _shapes;
  std::vector<CanvasMemento*> _oldStates;

 public:
  ~Canvas() {
    for (auto p : _oldStates) {
      delete p;
    }
    _oldStates.clear();
  }

  void addShape(const std::string& newShape) {
    _oldStates.push_back(new CanvasMemento(_shapes));
    _shapes.push_back(newShape);
  }

  void undo() {
    CanvasMemento* previousState = _oldStates.back();
    _oldStates.pop_back();
    _shapes = previousState->_shapes;
    delete previousState;
  }

  void clearAll() {
    _shapes.clear();
  }

  std::vector<std::string> getShapes() {
    return _shapes;
  }
};

int main() {
  Canvas canvas;

  canvas.addShape("rhombus");
  canvas.addShape("triangle");
  canvas.addShape("square");
  canvas.addShape("circle");

  for(auto shape : canvas.getShapes()) {
    cout << shape << ", ";
  }
  cout << endl;

  canvas.undo();
  for(auto shape : canvas.getShapes()) {
    cout << shape << ", ";
  }
  cout << endl;

  canvas.addShape("rhombus");
  canvas.addShape("triangle");
  canvas.addShape("square");
  canvas.addShape("circle");
  canvas.undo();

  for(auto shape : canvas.getShapes()) {
    cout << shape << ", ";
  }
  cout << endl;


  return EXIT_SUCCESS;
}
