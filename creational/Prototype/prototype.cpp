#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Animal {
 protected:
  std::string _hairColor;
  // Physical properties
  int _hairLength{0};
  int _tail{0};
  int _weight{0};
  int _height{0};
  int _age{0};

  // Personality properties
  int _intelligence{0};
  int _stubbornness{0};
  int _agressiveness{0};

 public:
  virtual Animal* clone() const = 0;

  void setHairLength(int v) {
    _hairLength = v;
  }
  void setHairColor(const std::string& v) {
    _hairColor = v;
  }
  void setTail(int v) {
    _tail = v;
  }
  void setWeight(int v) {
    _weight = v;
  }
  void setHeight(int v) {
    _height = v;
  }
  void setAge(int v) {
    _age = v;
  }
//  void setIntelligence(int v) {
//    _intelligence = v;
//  }
//  void setStubbornness(int v) {
//    _stubbornness = v;
//  }
//  void setAgressiveness(int v) {
//    _agressiveness = v;
//  }
};

class Sheep: public Animal{
 public:
  Sheep() {
    _hairLength = 5;
    _intelligence = 7;
    _stubbornness = 3;
    _agressiveness = 2;
  }

  Sheep* clone() const override {
    return new Sheep(*this);
  }

  void shearing() {
    _hairLength -= 2;
  }
};

class Cow: public Animal{
 public:
  Cow() {
    _intelligence = 8;
    _stubbornness = 6;
    _agressiveness = 5;
  }

  Cow* clone() const override {
    return new Cow(*this);
  }
};

int main()
{
  // Create initial instance of a Sheep
  Sheep* sheep0 = new Sheep;
  sheep0->setHairColor("white");
  sheep0->setTail(5);
  sheep0->setWeight(90);
  sheep0->setHeight(1);
  sheep0->setAge(5);

  // Create initial instance of a Cow
  Cow* cow0 = new Cow;
  cow0->setHairColor("brown");
  cow0->setTail(20);
  cow0->setWeight(790);
  cow0->setHeight(2);
  cow0->setAge(8);

  std::vector<Animal *> farm(3);

  // Use cloning to populate the farm
  farm[0] = sheep0->clone();
  farm[1] = cow0->clone();

  // Change properties
  farm[1]->setWeight(1000);

  sheep0->shearing();
  farm[2] = sheep0->clone();

  return EXIT_SUCCESS;
}
