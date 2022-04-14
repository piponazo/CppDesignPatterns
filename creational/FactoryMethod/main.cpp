#include <iostream>
#include <memory>
#include <string>

using namespace std;

/// Product from which the concrete products will inherit from
class Coffee {
 public:
  std::string getType() const {
    return _type;
  }

 protected:
  std::string _type;
};

class Espresso : public Coffee {
 public:
  Espresso() : Coffee() {
    _type = "Espresso";
    cout << endl << "Making a cup of espresso" << endl;
    cout << "Grind and brew one scoop of espresso beans." << endl;
  }
};

class Cappuccino : public Coffee {
 public:
  Cappuccino() : Coffee() {
    _type = "Cappuccino";
    cout << endl << "Making a cup of cappuccino" << endl;
    cout << "Grind and brew one scoop of espresso beans." << endl;
    cout << "Heat and foam milk." << endl;
  }
};

enum class CoffeType { Espresso, Cappuccino };

class CoffeMakerFactory {
 public:
  virtual std::unique_ptr<Coffee> getCoffee(CoffeType type) {
    switch (type) {
      case CoffeType::Espresso:
        return std::make_unique<Espresso>();
      case CoffeType::Cappuccino:
        return std::make_unique<Cappuccino>();
    }
    return nullptr;
  }
};

class InvertedCoffeMakerFactory : public CoffeMakerFactory {
 public:
  std::unique_ptr<Coffee> getCoffee(CoffeType type) override {
    if (type == CoffeType::Espresso) {
      type = CoffeType::Cappuccino;
    } else {
      type = CoffeType::Espresso;
    }

    return CoffeMakerFactory::getCoffee(type);
  }
};

void createOneOfEach(CoffeMakerFactory& factory) {
  cout << "asking for a espresso" << endl;
  auto espresso = factory.getCoffee(CoffeType::Espresso);
  cout << "You've got a: " << espresso->getType() << endl;

  cout << "asking for a cappuccino" << endl;
  auto cappuccino = factory.getCoffee(CoffeType::Cappuccino);
  cout << "You've got a: " << cappuccino->getType() << endl;
}

int main() {
  cout << "Using the default factory:..." << endl;
  {
    CoffeMakerFactory factory;
    createOneOfEach(factory);
  }

  cout << "\n\nNow we'll try with a inverted factory..." << endl;
  {
    InvertedCoffeMakerFactory factory;
    createOneOfEach(factory);
  }

  return EXIT_SUCCESS;
}
