#include <iostream>
#include <string>

// Instead of adding the same extra method to many different classes, create a separate class that can visit these
// classes and handle that logic itsel

// The main benefit is that we only need to add an "accept(Visitor)" method to our classes where we want to add extra
// functionality

using namespace std;

class IVisitor {
 public:
  virtual void handlePerson(const std::string& name, int age) = 0;
  virtual void handleLandmark(const std::string& name, const std::string cityName) = 0;
  virtual void handleCar(const std::string& make, const std::string& model) = 0;
};

class DatabaseVisitor : public IVisitor {
 public:
  void handlePerson(const string& name, int age) override {
    std::cout << "Writing person to database: " << name << ", " << age << std::endl;
  }
  void handleLandmark(const string& name, const string cityName) override {
    std::cout << "Writing landmark to database: " << name << ", " << cityName << std::endl;
  }
  void handleCar(const string& make, const string& model) override {
    std::cout << "Writing car to database: " << make << ", " << model << std::endl;
  }
};

class TextFileVisitor : public IVisitor {
 public:
  void handlePerson(const string& name, int age) override {
    std::cout << "Writing person to file: " << name << ", " << age << std::endl;
  }
  void handleLandmark(const string& name, const string cityName) override {
    std::cout << "Writing landmark to file: " << name << ", " << cityName << std::endl;
  }
  void handleCar(const string& make, const string& model) override {
    std::cout << "Writing car to file: " << make << ", " << model << std::endl;
  }
};

class Person {
  string _name;
  int _age;

 public:
  Person(const string& name, int age) : _name(name), _age(age) {
  }
  void accept(IVisitor* v) {
    v->handlePerson(_name, _age);
  }
};

class LandMark {
  string _name;
  string _cityName;

 public:
  LandMark(const string& name, const string& cityName) : _name(name), _cityName(cityName) {
  }
  void accept(IVisitor* v) {
    v->handleLandmark(_name, _cityName);
  }
};

class Car {
  string _make;
  string _model;

 public:
  Car(const string& make, const string& model) : _make(make), _model(model) {
  }
  void accept(IVisitor* v) {
    v->handleCar(_make, _model);
  }
};

int main() {
  Person person("John", 40);
  LandMark landmark("Eiffel tower", "Paris");
  Car car("Chevrolet", "Camaro");

  DatabaseVisitor dbVisitor;
  TextFileVisitor txtVisitor;

  person.accept(&dbVisitor);
  landmark.accept(&dbVisitor);
  car.accept(&dbVisitor);

  person.accept(&txtVisitor);
  landmark.accept(&txtVisitor);
  car.accept(&txtVisitor);

  return EXIT_SUCCESS;
}
