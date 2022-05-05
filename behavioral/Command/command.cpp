// Command pattern turns a request into a standalone object that contains all information about the request.

#include <iostream>
#include <memory>
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
  const std::vector<std::string>& getShapes() const {
    return _shapes;
  }
};

class Command {
 public:
  virtual ~Command() {
  }
  virtual void execute() = 0;
};

class Button {
  std::unique_ptr<Command> _command;

 public:
  Button(std::unique_ptr<Command> command) : _command(std::move(command)) {
  }
  void click() {
    _command->execute();
  }
};

class AddShapeCommand : public Command {
  std::string _shapeName;
  Canvas* _canvas;

 public:
  AddShapeCommand(const std::string& shapeName, Canvas* canvas) : _shapeName(shapeName), _canvas(canvas) {
  }
  void execute() override {
    _canvas->addShape(_shapeName);
  }
};

class ClearCommand : public Command {
  Canvas* _canvas;

 public:
  ClearCommand(Canvas* canvas) : _canvas(canvas) {
  }
  void execute() override {
    _canvas->clearAll();
  }
};

int main() {
  auto canvas = std::make_unique<Canvas>();

  auto addTriangleButton = std::make_unique<Button>(std::make_unique<AddShapeCommand>("triangle", canvas.get()));
  auto addSquareButton = std::make_unique<Button>(std::make_unique<AddShapeCommand>("square", canvas.get()));
  auto clearButton = std::make_unique<Button>(std::make_unique<ClearCommand>(canvas.get()));

  auto printShapes = [](const std::vector<std::string>& shapes) {
    cout << "Current canvas state:\n";
    for (auto& shape : shapes) {
      cout << "\tShape: " << shape << endl;
    }
  };

  addTriangleButton->click();
  printShapes(canvas->getShapes());

  addSquareButton->click();
  addSquareButton->click();
  addTriangleButton->click();
  printShapes(canvas->getShapes());

  clearButton->click();
  printShapes(canvas->getShapes());

  return EXIT_SUCCESS;
}
