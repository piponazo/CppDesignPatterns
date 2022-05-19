// Create an iterator interface that client code can use to iterate through any collection without knowing anything
// about its internal structure.
//
// Since iterators keep track of their current position in the collection, it's possible to have multiple iterators
// iterating through the same collection at the same time.

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class NumberIterator {
 public:
  virtual ~NumberIterator() {
  }
  virtual int next() = 0;
  virtual bool isFinished() = 0;
};

class ForwardIterator : public NumberIterator {
  int _currentPosition;
  std::vector<int>& _numbers;

 public:
  ForwardIterator(std::vector<int>& numbers) : _currentPosition(0), _numbers(numbers) {
  }

  int next() override {
    int current = _numbers.at(_currentPosition);
    _currentPosition++;
    return current;
  }

  bool isFinished() override {
    return _currentPosition >= _numbers.size();
  }
};

class BackwardsIterator : public NumberIterator {
  int _currentPosition;
  std::vector<int>& _numbers;

 public:
  BackwardsIterator(std::vector<int>& numbers) : _currentPosition(0), _numbers(numbers) {
  }

  int next() override {
    int current = _numbers.at(_numbers.size() - _currentPosition - 1);
    _currentPosition++;
    return current;
  }

  bool isFinished() override {
    return _currentPosition >= _numbers.size();
  }
};

class NumberCollection {
  std::vector<int> _numbers;

 public:
  NumberCollection(const std::vector<int>& numbers) : _numbers(numbers) {
  }
  std::unique_ptr<NumberIterator> getForwardsIterator() {
    return make_unique<ForwardIterator>(_numbers);
  }
  std::unique_ptr<NumberIterator> getBackwardsIterator() {
    return make_unique<BackwardsIterator>(_numbers);
  }
};

int main() {
  std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7};
  NumberCollection nc(numbers);

  auto fi = nc.getForwardsIterator();
  auto bi = nc.getBackwardsIterator();

  auto printWithIt = [](NumberIterator* it, std::string_view typeIt) {
    cout << "Iterating through elements " << typeIt << ": ";
    while (it->isFinished() == false) {
      cout << it->next() << ", ";
    }
    cout << endl;
  };

  printWithIt(fi.get(), "forwards");
  printWithIt(bi.get(), "backwards");

  return EXIT_SUCCESS;
}
