#include <windows.h>  // WinApi header
#include <iostream>

using namespace std;

#pragma region Backgrounds
class Background {
 protected:
  std::string _theme;

 public:
  virtual void getTheme() = 0;
};

class LightBkgd : public Background {
 public:
  LightBkgd(HANDLE hConsole) {
    SetConsoleTextAttribute(hConsole, 240);
    cout << "Making the background white" << endl;
    _theme = "light";
  }
  void getTheme() {
    cout << "This is a part of the light theme" << endl;
  }
};

class DarkBkgd : public Background {
 public:
  DarkBkgd(HANDLE hConsole) {
    SetConsoleTextAttribute(hConsole, 15);
    cout << "Making the background black" << endl;
    _theme = "dark";
  }
  void getTheme() {
    cout << "This is a part of the dark theme" << endl;
  }
};
#pragma endregion Background

#pragma region Text
// Base Text class
class Text {
 protected:
  std::string _theme;

 public:
  Text() {
  }
  virtual void message(HANDLE hConsole) = 0;
};

// Derived Black Text class
class BlackText : public Text {
 public:
  BlackText(HANDLE hConsole) {
    SetConsoleTextAttribute(hConsole, 240);
    _theme = "light";
    cout << "Making the text black" << endl;
  }
  void message(HANDLE hConsole) {
    SetConsoleTextAttribute(hConsole, 240);
    cout << "This is the default font from the light theme" << endl;
  }
};

// Derived White Text class
class WhiteText : public Text {
 public:
  WhiteText(HANDLE hConsole) {
    SetConsoleTextAttribute(hConsole, 15);
    _theme = "dark";
    cout << "Making the text white" << endl;
  }
  void message(HANDLE hConsole) {
    SetConsoleTextAttribute(hConsole, 15);
    cout << "This is the default font for the dark theme" << endl;
  }
};

// Derived Dark Green Text class

// Derived Light Green Text class

#pragma endregion Text

#pragma region Factories
// Base Factory
class ThemeFactory {
 public:
  virtual std::unique_ptr<Background> setBackground(HANDLE hConsole) = 0;
  virtual std::unique_ptr<Text> getDefaultText(HANDLE hConsole) = 0;
};

// Derived Light Theme Factory which pairs the white background with darker text
class LightFactory : public ThemeFactory {
 public:
  std::unique_ptr<Background> setBackground(HANDLE hConsole) override {
    return std::make_unique<LightBkgd>(hConsole);
  }
  std::unique_ptr<Text> getDefaultText(HANDLE hConsole) override {
    return std::make_unique<BlackText>(hConsole);
  }
};

// Derived Dark Theme Factory which pairs the black background with lighter text
class DarkFactory : public ThemeFactory {
 public:
  std::unique_ptr<Background> setBackground(HANDLE hConsole) override {
    return std::make_unique<DarkBkgd>(hConsole);
  }
  std::unique_ptr<Text> getDefaultText(HANDLE hConsole) override {
    return std::make_unique<WhiteText>(hConsole);
  }
};
#pragma endregion Factories

int main() {
  // Configure console variables and colours
  HANDLE hConsole;
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, 30);

  std::unique_ptr<ThemeFactory> app;
  int choice;

  cout << "Select a theme: " << endl;
  cout << "1: Light" << endl;
  cout << "2: Dark" << endl;
  cout << "Selection: ";
  cin >> choice;
  cout << endl;

  // Initiate the correct factory based on user input
  switch (choice) {
    case 1:
      app = std::make_unique<LightFactory>();
      break;
    case 2:
      app = std::make_unique<DarkFactory>();
      break;
    default:
      cout << "Invalid Selection" << endl;
      break;
  }

  // Get the correct objects based on factory selected
  if (app) {
    auto appBkgd = app->setBackground(hConsole);
    auto appDefaultText = app->getDefaultText(hConsole);

    appDefaultText->message(hConsole);
  }

  cout << endl;
  system("pause");
}
