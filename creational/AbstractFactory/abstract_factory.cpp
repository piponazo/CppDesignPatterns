#include <iostream>
#include <memory>

using namespace std;

class Door {
 public:
  virtual void open() = 0;
};

class GasCarDoor : public Door {
 public:
  void open() override {
    cout << "click" << endl;
  }
};

class ElectricCarDoor : public Door {
 public:
  void open() override {
    cout << "shhh" << endl;
  }
};

class Engine {
 public:
  virtual void run() = 0;
};

class GasEngine : public Engine {
 public:
  void run() override {
    cout << "Making a gas engine" << endl;
  }
};
class ElectricEngine : public Engine {
 public:
  void run() override {
    cout << "Making an electric engine" << endl;
  }
};

class CarFactory {
 public:
  virtual std::unique_ptr<Door> buildDoor() = 0;
  virtual std::unique_ptr<Engine> buildEngine() = 0;
};

class GasCarFactory : public CarFactory {
 public:
  std::unique_ptr<Door> buildDoor() override {
    return std::make_unique<GasCarDoor>();
  }
  std::unique_ptr<Engine> buildEngine() override {
    return std::make_unique<GasEngine>();
  }
};

class ElectricCarFactory : public CarFactory {
 public:
  std::unique_ptr<Door> buildDoor() override {
    return std::make_unique<ElectricCarDoor>();
  }
  std::unique_ptr<Engine> buildEngine() override {
    return std::make_unique<ElectricEngine>();
  }
};

int main() {
  std::unique_ptr<CarFactory> factory;
  int choice{0};

  cout << "Select a car type: " << endl;
  cout << "1: Gasoline" << endl;
  cout << "2: Electric" << endl;
  cout << "Selection: ";
  cin >> choice;
  cout << endl;

  switch (choice) {
    case 1: {
      factory = std::make_unique<GasCarFactory>();
      break;
    }
    case 2: {
      factory = std::make_unique<ElectricCarFactory>();
      break;
    }
  }

  if (!factory) {
    cerr << "Error in the selection of the car type" << endl;
    return EXIT_FAILURE;
  }

  auto door = factory->buildDoor();
  auto engine = factory->buildEngine();
  door->open();
  engine->run();

  return EXIT_SUCCESS;
}
