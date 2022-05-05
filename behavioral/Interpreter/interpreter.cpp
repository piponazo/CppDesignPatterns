#include <iostream>

using namespace std;

class Expression {
 public:
  virtual int evaluate() = 0;
};

// Non-terminal expression
// 5 + 10
// 5 + (10 + 1)
class OperationExpression : public Expression {
  std::string _operatorSymbol;
  Expression* _leftHandSize;
  Expression* _rightHandSize;

 public:
  OperationExpression(const std::string& operatorSymbol, Expression* left, Expression* right) :
      _operatorSymbol(operatorSymbol), _leftHandSize(left), _rightHandSize(right) {
  }

  int evaluate() override {
    if (_operatorSymbol == "+") {
      return _leftHandSize->evaluate() + _rightHandSize->evaluate();
    } else if (_operatorSymbol == "-") {
      return _leftHandSize->evaluate() - _rightHandSize->evaluate();
    } else {
      cerr << "Unrecognized operator: " << _operatorSymbol;
      return -666;
    }
  }
};

// Terminal expression
class NumberExpression : public Expression {
  std::string _numberString;

 public:
  NumberExpression(const std::string& numberString) : _numberString(numberString) {
  }

  int evaluate() override {
    return std::stoi(_numberString);
  }
};

int main() {
  NumberExpression five ("5");
  NumberExpression seven ("7");
  OperationExpression fivePlusSeven ("+", &five, &seven);

  cout << "Five + Seven is: " << fivePlusSeven.evaluate() << endl;

  NumberExpression thirteen ("13");
  OperationExpression complexOp ("-", &thirteen, &fivePlusSeven);

  cout << "Complex expression result is: " << complexOp.evaluate() << endl;

  return EXIT_SUCCESS;
}
