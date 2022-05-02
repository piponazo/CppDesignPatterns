#include <iostream>

using namespace std;

class Leader {
 private:
  Leader() {
    cout << "New leader elected" << endl;
  }

 public:
  static Leader* instance() {
    static Leader instance;
    return &instance;
  }

  void giveSpeech() const {
    cout << "Address the public" << endl;
  }
};

int main() {
  auto leader = Leader::instance();
  leader->giveSpeech();

  auto leader2 = Leader::instance();
  leader2->giveSpeech();

  if (leader2 == leader) {
    cout << "Same leader" << endl;
  }
  return EXIT_SUCCESS;
}
