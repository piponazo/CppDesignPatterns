#include <iostream>
#include <string>

using namespace std;

class Person {
  string _name;
  int _age;

 public:
  Person(const string& name, int age) : _name(name), _age(age) {
  }
};

class LandMark {
  string _name;
  string _cityName;

 public:
  LandMark(const string& name, const string& cityName) : _name(name), _cityName(cityName) {
  }
};

class Car {
  string _make;
  string _model;

 public:
  Car(const string& make, const string& model) : _make(make), _model(model) {
  }
};

int main() {
  return EXIT_SUCCESS;
}
