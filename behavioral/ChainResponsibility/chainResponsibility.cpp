#include <iostream>
#include <memory>
#include <regex>
#include <string>

using namespace std;

// Note: The returning of a pointer in setNext() allows us to chain the calls to such method.

class StringValidator {
 public:
  virtual ~StringValidator() {
  }

  virtual StringValidator* setNext(StringValidator* nextValidator) = 0;
  virtual std::string validate(std::string data) = 0;
};

class BaseValidator : public StringValidator {
 protected:
  StringValidator* _next{nullptr};

 public:
  virtual ~BaseValidator() {
    delete _next;
  }

  StringValidator* setNext(StringValidator* nextValidator) override {
    _next = nextValidator;
    return nextValidator;
  }

  virtual std::string validate(std::string data) override {
    if (this->_next) {
      return this->_next->validate(data);
    }
    return "Success";  // End of the chain
  }
};

// Note that the concrete implementations check if something go wrong. If not, they call BaseValidator::valite() to
// continue with the chain of reponsibility

class NotEmptyValidator : public BaseValidator {
 public:
  std::string validate(std::string data) override {
    puts("Checking if empty...");
    if (data.empty()) {
      return "Please enter a value";
    }
    return BaseValidator::validate(data);
  }
};

class LengthValidator : public BaseValidator {
  int _minLength;

 public:
  LengthValidator(int minLength) : _minLength(minLength) {
  }
  std::string validate(std::string data) override {
    puts("Checking string length ...");
    if (data.size() < _minLength) {
      return "Please enter a value longer than " + std::to_string(_minLength);
    }
    return BaseValidator::validate(data);
  }
};

class RegexValidator : public BaseValidator {
  std::string _patternName;
  std::string _regexString;

 public:
  RegexValidator(std::string patternName, std::string regexString) :
      _patternName(patternName), _regexString(regexString) {
  }

  std::string validate(std::string data) override {
    puts("Checking regex match ...");
    if (!std::regex_match(data, std::regex(_regexString))) {
      return "The value entered does not match the proper format for a " + _patternName;
    }
    return BaseValidator::validate(data);
  }
};

bool in_array(const std::string& value, const std::vector<std::string>& array) {
  return std::find(array.begin(), array.end(), value) != array.end();
}

class HistoryValidator : public BaseValidator {
  std::vector<std::string> _historyItems;

 public:
  HistoryValidator(std::vector<std::string> historyItems) : _historyItems(historyItems) {
  }

  std::string validate(std::string data) override {
    puts("Checking if string has been used before ...");
    if (in_array(data, _historyItems)) {
      return "Please enter a value here that you haven't entered before";
    }
    return BaseValidator::validate(data);
  }
};

int main() {
  vector<string> oldPasswords = {"abc123", "123456", "hello"};

  auto emailValidator = std::make_unique<BaseValidator>();

  emailValidator->setNext(new NotEmptyValidator)
      ->setNext(new RegexValidator("email address", "^\\w+([-+.']\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*$"));

  cout << "Checking Emails ---------------\n";
  cout << "Input: \n" << emailValidator->validate("") << "\n\n";
  cout << "Input: shaun\n" << emailValidator->validate("shaun") << "\n\n";
  cout << "Input: shaun@test.com\n" << emailValidator->validate("shaun@test.com") << "\n\n";

  return EXIT_SUCCESS;
}