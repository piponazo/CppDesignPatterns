#include <iostream>

using namespace std;

/*
class Person {
 public:
  virtual void greet(const std::string& name) = 0;
};

class BussinessPerson : public Person {
 public:
  void greet(const string& name) override {
    cout << "Good morning " << name << ", how do you do?\n";
  }
};

class NormalPerson : public Person {
 public:
  void greet(const string& name) override {
    cout << "Hi " << name << ", how are you?\n";
  }
};

class CoolPerson : public Person {
 public:
  void greet(const string& name) override {
    cout << "Hey " << name << ", what's up?\n";
  }
};

// Uh oh - code duplication!
class PoliticianPerson : public Person {
 public:
  void greet(const string& name) override {
    cout << "Good morning " << name << ", how do you do?\n";
  }
};
*/

class GreetingStrategy {
 public:
  virtual ~GreetingStrategy() {
  }
  virtual void greet(const std::string& name) = 0;
};

class FormalGreetingStrategy : public GreetingStrategy {
 public:
  void greet(const string& name) override {
    cout << "Good morning " << name << ", how do you do?\n";
  }
};

class NormalGreetingStrategy : public GreetingStrategy {
 public:
  void greet(const string& name) override {
    cout << "Hi " << name << ", how are you?\n";
  }
};

class InformalGreetingStrategy : public GreetingStrategy {
 public:
  void greet(const string& name) override {
    cout << "Hey " << name << ", what's up?\n";
  }
};

class Person {
  GreetingStrategy* _greetingStrategy;

 public:
  Person(GreetingStrategy* greetingStrategy) : _greetingStrategy(greetingStrategy) {
  }
  ~Person() {
    delete _greetingStrategy;
  }

  void greet(const std::string& name) {
    _greetingStrategy->greet(name);
  }
};

int main() {
  Person bussinessPerson(new FormalGreetingStrategy);
  Person normalPerson(new NormalGreetingStrategy);
  Person coolPerson(new InformalGreetingStrategy);
  Person politician(new FormalGreetingStrategy);

  cout << "The business person says: ";
  bussinessPerson.greet("Shaun");

  cout << "The normal person says: ";
  normalPerson.greet("Shaun");

  cout << "The cool person says: ";
  coolPerson.greet("Shaun");

  cout << "The politician says: ";
  politician.greet("Shaun");

  return EXIT_SUCCESS;
}
