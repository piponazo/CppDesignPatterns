#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Entree {
 protected:
  string _entree;

 public:
  string getEntree() const {
    return _entree;
  }
};

class Burger : public Entree {
 public:
  Burger() {
    cout << "\n Grill burger patty, add tomatoes and place them in a bun\n";
    _entree = "hamburguer";
  }
};

class Hotdog : public Entree {
 public:
  Hotdog() {
    cout << "\n Cook sausage and place it in a bun\n";
    _entree = "hotdog";
  }
};

// -------------------------------

class Side {
 protected:
  string _side;

 public:
  string getSide() const {
    return _side;
  }
};

class Fries : public Side {
 public:
  Fries() {
    cout << "\n Fry and season potatoes\n";
    _side = "fries";
  }
};

class Salad : public Side {
 public:
  Salad() {
    cout << "\n Toss greens and dressing together\n";
    _side = "salad";
  }
};

// -------------------------------

class Drink {
 protected:
  string _drink{"soda"};

 public:
  string getDrink() const {
    return _drink;
  }
};

// -------------------------------

class MealCombo {
 private:
  std::unique_ptr<Entree> _entree;
  std::unique_ptr<Side> _side;
  std::unique_ptr<Drink> _drink;
  std::string _type;

 public:
  MealCombo(std::string_view type) : _type(type) {
  }
  void setEntree(std::unique_ptr<Entree> v) {
    _entree = std::move(v);
  }
  void setSide(std::unique_ptr<Side> v) {
    _side = std::move(v);
  }
  void setDrink(std::unique_ptr<Drink> v) {
    _drink = std::move(v);
  }
  std::string openMealBag() {
    return _type + " meal combo: " + _entree->getEntree() + " " + _side->getSide() + " " + _drink->getDrink() + "\n";
  }
};

// ------------------------

class MealBuilder {
 protected:
  std::unique_ptr<MealCombo> _meal;

 public:
  virtual void cookEntree() = 0;
  virtual void cookSide() = 0;
  virtual void fillDrink() = 0;
  MealCombo* getMeal() {
    return _meal.get();
  }
};

class BurgerMeal : public MealBuilder {
 public:
  BurgerMeal() {
    _meal = std::make_unique<MealCombo>("Burguer");
  }

  void cookEntree() override {
    _meal->setEntree(std::make_unique<Burger>());
  }

  void cookSide() override {
    _meal->setSide(std::make_unique<Fries>());
  }

  void fillDrink() override {
    _meal->setDrink(std::make_unique<Drink>());
  }
};

class HotdogMeal : public MealBuilder {
 public:
  HotdogMeal() {
    _meal = std::make_unique<MealCombo>("Hotdog");
  }

  void cookEntree() override {
    _meal->setEntree(std::make_unique<Hotdog>());
  }

  void cookSide() override {
    _meal->setSide(std::make_unique<Salad>());
  }

  void fillDrink() override {
    _meal->setDrink(std::make_unique<Drink>());
  }
};

int main() {
  std::unique_ptr<MealBuilder> builder;

  int choice;
  cout << "Select a meal: " << endl;
  cout << "1: Hamburguer Meal " << endl;
  cout << "2: Hotdog Meal " << endl;
  cout << "Selection: " << endl;
  cin >> choice;
  cout << endl;

  switch(choice) {
    case 1: {
      builder = std::make_unique<BurgerMeal>();
      break;
    }
    case 2: {
      builder = std::make_unique<HotdogMeal>();
      break;
    }
  }

  if (!builder) {
    cerr << "Error in the selection" << endl;
    return EXIT_FAILURE;
  }

  cout << "Making selected meal" << endl;

  builder->cookEntree();
  builder->cookSide();
  builder->fillDrink();
  auto meal = builder->getMeal();

  cout << "OpenMealBag: " << meal->openMealBag() << endl;

  return EXIT_SUCCESS;
}
