#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class IMediator {
 public:
  virtual void mediate(const std::string& event) = 0;
};

// ------------------------------------------------------

class InterfaceElement {
 protected:
  IMediator* _mediator;
  std::string name;
  bool isVisible = true;

 public:
  InterfaceElement(const std::string& name, bool isVisible, IMediator* mediator) :
      name(name), isVisible(isVisible), _mediator(mediator) {
  }
  void setVisibility(bool isVisible) {
    this->isVisible = isVisible;
  };
  std::string getDescription() {
    return isVisible ? name + " is visible" : name + " is NOT visible";
  }
};

class ButtonElement : public InterfaceElement {
 public:
  ButtonElement(const std::string& name, bool isVisible, IMediator* mediator) :
      InterfaceElement(name, isVisible, mediator) {
  }
  virtual ~ButtonElement(){};
  virtual void click() {
    _mediator->mediate(name + "clicked");
  }
};

class TextBox : public InterfaceElement {
  std::string textValue = "";

 public:
  TextBox(const std::string& name, bool isVisible, IMediator* mediator) : InterfaceElement(name, isVisible, mediator) {
  }
  virtual ~TextBox(){};
  virtual void changeText(const std::string& newValue) {
    textValue = newValue;
    if (newValue.empty()) {
      _mediator->mediate(name + " empty");
    } else {
      _mediator->mediate(name + " not empty");
    }
  };
};

class CheckBox : public InterfaceElement {
  bool isChecked = false;

 public:
  CheckBox(const std::string& name, bool isVisible, IMediator* mediator) : InterfaceElement(name, isVisible, mediator) {
  }
  virtual ~CheckBox(){};
  virtual void setIsChecked(bool isChecked) {
    this->isChecked = isChecked;
    if (isChecked) {
      _mediator->mediate(name + " is checked");
    } else {
      _mediator->mediate(name + " is unchecked");
    }
  };
};

// ------------------------------------------------------
// Manager class

class UserInterface : public IMediator {
  std::unique_ptr<TextBox> _nameTextBox;
  std::unique_ptr<TextBox> _spousesNameTextBox;
  std::unique_ptr<CheckBox> _isMarriedCheckBox;
  std::unique_ptr<ButtonElement> _submitButton;

 public:
  UserInterface() {
    _nameTextBox = std::make_unique<TextBox>("Name textbox", true, this);
    _spousesNameTextBox = std::make_unique<TextBox>("Spouse's name textbox", false, this);
    _isMarriedCheckBox = std::make_unique<CheckBox>("Is married checkbox", true, this);
    _submitButton = std::make_unique<ButtonElement>("Submit button", false, this);
  }

  void mediate(const std::string& event) override {
    std::cout << "Mediating event: " << event << "...\n";

    if (event == "Name textbox is empty") {
      _submitButton->setVisibility(false);
    } else if (event == "Name textbox is not empty") {
      _submitButton->setVisibility(true);
    } else if (event == "Is married checkbox is checked") {
      _spousesNameTextBox->setVisibility(true);
    } else if (event == "Is married checkbox is unchecked") {
      _spousesNameTextBox->setVisibility(false);
    } else if (event == "Submit button clicked") {
      std::cout << "Submitted!\n";
    } else {
      std::cout << "Unrecognized event!";
    }
  }

  TextBox* getNameTextBox() {
    return _nameTextBox.get();
  }
  TextBox* getSpousesNameTextBox() {
    return _spousesNameTextBox.get();
  }
  CheckBox* getIsMarriedCheckBox() {
    return _isMarriedCheckBox.get();
  }
  ButtonElement* getSubmitButton() {
    return _submitButton.get();
  }
};

int main(int argc, const char* argv[]) {
  UserInterface ui;
  std::vector<InterfaceElement *> elements {
    ui.getNameTextBox(),
    ui.getIsMarriedCheckBox(),
    ui.getSpousesNameTextBox(),
    ui.getSubmitButton(),
  };

  for (auto element: elements) {
    cout << element->getDescription() << endl;
  }

  cout << endl;
  ui.getIsMarriedCheckBox()->setIsChecked(true);

  for (auto element: elements) {
    cout << element->getDescription() << endl;
  }

  return EXIT_SUCCESS;
}
