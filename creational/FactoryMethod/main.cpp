#include <iostream>
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

int main() {
  cout << "Hello world!" << endl;
  return EXIT_SUCCESS;
}
