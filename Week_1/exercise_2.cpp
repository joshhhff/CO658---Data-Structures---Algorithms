#include <cstdlib>
#include <iostream>
#include <vector>

class Weapon{
    public:
    int id;
    Weapon(){}
    Weapon(int id):id(id){}
};

int main() {

    std::vector<Weapon> weapons;
    for(int i = 0; i < 10; ++i) {
        weapons.push_back(Weapon(i));
    }

    for(std::vector<Weapon>::iterator it = weapons.begin(); it != weapons.end(); ++it) {
        std::cout << it->id << std::endl;
    }

    return EXIT_SUCCESS;
}