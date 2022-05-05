#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Subscriber {
 public:
  virtual void notify(const std::string& publisherName, const std::string& message) = 0;
  virtual std::string getName() = 0;
};

class Publisher {
 public:
  virtual void subscribe(Subscriber* subscriber) = 0;
  virtual void unsubscribe(Subscriber* subscriber) = 0;
  virtual void publish(const std::string& message) = 0;
};

class ChatGroup : public Publisher {
  std::string _groupName;
  std::vector<Subscriber*> _subscribers;

 public:
  ChatGroup(const std::string name) : _groupName(name) {
  }

  // Publisher interface
  void subscribe(Subscriber* subscriber) override {
    _subscribers.push_back(subscriber);
  }
  void unsubscribe(Subscriber* subscriber) override {
    _subscribers.erase(std::remove_if(_subscribers.begin(), _subscribers.end(),
                                      [subscriber](Subscriber* s) { return s->getName() == subscriber->getName(); }));
  }
  void publish(const std::string& message) override {
    for (auto subscriber : _subscribers) {
      subscriber->notify(_groupName, message);
    }
  }
};

class ChatUser : public Subscriber {
  std::string _userName;

 public:
  ChatUser(const std::string& name) : _userName(name) {
  }

  // Subscriber interface
  void notify(const std::string& publisherName, const std::string& message) override {
    std::cout << _userName << " received a new message from " << publisherName << ": " << message << std::endl;
  }
  std::string getName() override {
    return _userName;
  }
};

int main() {
  ChatUser user1("Jim");
  ChatUser user2("Luis");
  ChatUser user3("Celia");

  ChatGroup group1("gatitos");
  ChatGroup group2("all");

  group1.subscribe(&user2);
  group1.subscribe(&user3);

  group2.subscribe(&user1);
  group2.subscribe(&user2);
  group2.subscribe(&user3);

  group1.publish("Bobo ate all the food");
  group2.publish("Russia is attacking Ukraine");

  return EXIT_SUCCESS;
}
