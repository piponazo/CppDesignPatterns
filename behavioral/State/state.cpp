#include <iostream>
#include <string>

using namespace std;

// Class without pattern
/*
class Purchase {
  std::string productName;
  std::string currentState;

 public:
  Purchase(const std::string& productName) : productName(productName), currentState("PURCHASED") {
  }

  std::string getDescription() {
    std::string description = productName + " - " + currentState + "\n";

    if (currentState == "PURCHASED") {
      description += "Will be shipping soon\n";
    } else if (currentState == "IN_TRANSIT") {
      description += "Your item is on the way\n";
    } else if (currentState == "DELIVERED") {
      description += "Your item has arrived\n";
    }

    return description;
  }

  void goToNextState() {
    if (currentState == "PURCHASED") {
      currentState = "IN_TRANSIT";
    } else if (currentState == "IN_TRANSIT") {
      currentState = "DELIVERED";
    } else if (currentState == "DELIVERED") {
      std::cout << "No more states!";
    }
  };
};
*/

class IState {
 public:
  virtual std::string getDescription() const = 0;
  virtual IState* getNextState() = 0;
};

class PurchasedState : public IState {
  IState* _nextState;

 public:
  PurchasedState(IState* state) : _nextState(state) {
  }

  std::string getDescription() const override {
    return "Current State: PURCHARED - Will be shipping soon\n";
  }

  IState* getNextState() override {
    return _nextState;
  }
};

class InTransitState : public IState {
  IState* _nextState{nullptr};

 public:
  InTransitState(IState* state) : _nextState(state) {
  }

  std::string getDescription() const override {
    return "Current State: IN_TRANSIT - Your item is on the way\n";
  }

  IState* getNextState() override {
    return _nextState;
  }
};

class DeliveredState : public IState {
  IState* _nextState{nullptr};

 public:
  DeliveredState(IState* state) : _nextState(state) {
  }

  std::string getDescription() const override {
    return "Current State: DELIVERED - Your item has arrived\n";
  }

  IState* getNextState() override {
    return _nextState;
  }
};

class Purchase {
  std::string productName;
  IState* currentState{nullptr};

 public:
  Purchase(const std::string& productName, IState* initState) : productName(productName), currentState(initState) {
  }

  std::string getDescription() {
    return currentState->getDescription();
  }

  void goToNextState() {
    if (currentState) {
      currentState = currentState->getNextState();
    } else {
      cout << "No more states" << endl;
    }
  }
};

int main() {
  DeliveredState deliveredState(nullptr);
  InTransitState inTransitState(&deliveredState);
  PurchasedState purchasedState(&inTransitState);

  Purchase purchase("Shoes", &purchasedState);
  cout << purchase.getDescription() << endl;

  purchase.goToNextState();
  cout << purchase.getDescription() << endl;

  purchase.goToNextState();
  cout << purchase.getDescription() << endl;

  return EXIT_SUCCESS;
}
