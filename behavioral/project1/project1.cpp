// This project combines the Observer & Chain of responsibility patters

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

class Handler {
 public:
  virtual ~Handler() {
  }

  virtual Handler* setNext(Handler* nextValidator) = 0;
  virtual std::string handle(ChatGroup* chat, std::string data) = 0;
};

class BaseHandler : public Handler {
 protected:
  Handler* _next{nullptr};

 public:
  virtual ~BaseHandler() {
    delete _next;
  }

  Handler* setNext(Handler* nextValidator) override {
    _next = nextValidator;
    return nextValidator;
  }

  virtual std::string handle(ChatGroup* chat, std::string data) override {
    if (_next) {
      return _next->handle(chat, data);
    }
    return "Success";  // End of the chain
  }
};

// Note that the concrete implementations check if something go wrong. If not, they call BaseHandler::valite() to
// continue with the chain of reponsibility

class NotEmptyValidator : public BaseHandler {
 public:
  std::string handle(ChatGroup* chat, std::string data) override {
    puts("Checking if empty...");
    if (data.empty()) {
      return "Please enter a value";
    }
    return BaseHandler::handle(chat, data);
  }
};

class LengthValidator : public BaseHandler {
  int _minLength;

 public:
  LengthValidator(int minLength) : _minLength(minLength) {
  }
  std::string handle(ChatGroup* chat, std::string data) override {
    puts("Checking string length ...");
    if (data.size() < _minLength) {
      return "Please enter a value longer than " + std::to_string(_minLength);
    }
    return BaseHandler::handle(chat, data);
  }
};

class PostMessageHandler : public BaseHandler {
 public:
  std::string handle(ChatGroup* group, std::string message) {
    group->publish(message);
    return "Message sent!";
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

  Handler* sendMessageChain = new BaseHandler;
  sendMessageChain->setNext(new NotEmptyValidator)->setNext(new LengthValidator(2))->setNext(new PostMessageHandler);

  std::cout << "Sending empty message:\n" << sendMessageChain->handle(&group1, "") << "\n\n";
  std::cout << "Sending short message:\n" << sendMessageChain->handle(&group1, "H") << "\n\n";
  std::cout << "Sending message to group 1:\n"
            << sendMessageChain->handle(&group1, "Hello everyone in group 1!") << "\n\n";
  std::cout << "Sending message to group 2:\n"
            << sendMessageChain->handle(&group2, "Hello everyone in group 2!") << "\n\n";

  delete sendMessageChain;

  return EXIT_SUCCESS;
}
