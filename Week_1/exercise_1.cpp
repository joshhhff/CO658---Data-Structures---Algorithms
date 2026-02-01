#include <cstdlib>
#include <iostream>

class Entity {
    public:
    int size;
    Entity(int s):size(s){}
};

// overload the ++ operator here
Entity& operator++(Entity& e) {
    e.size++;
    return e;
}
Entity& operator--(Entity& e) {
    e.size--;
    return e;
}


int main() {

    Entity e1(5);
    Entity e2(3);

    ++e1;
    --e2;

    std::cout << "e1 size: " << e1.size << std::endl;
    std::cout << "e2 size: " << e2.size << std::endl;

    return EXIT_SUCCESS;
}