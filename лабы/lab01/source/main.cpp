#include "parent.hpp"

int main() {
    Parent(getenv("PATH_TO_CHILD"), std::cin);
    // export PATH_TO_CHILD="/Users/admin/Desktop/МАИ/второй/oc/git/Operation-systems/lab01/build/child"
    return 0;
}
