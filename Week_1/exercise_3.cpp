#include <cstdlib>
#include <iostream>
#include <vector>

class Weapon{
    public:
    int id;
    Weapon(){}
    Weapon(int id):id(id){}

    bool operator==(const Weapon& other) const {
        return id == other.id;
    }
};

int main() {

    std::vector<Weapon> weapons;
    for(int i = 0; i < 10; ++i) {
        weapons.push_back(Weapon(i));
    }

    std::cout << "Before deletion:" << std::endl;
    
    for(std::vector<Weapon>::iterator it = weapons.begin(); it != weapons.end(); ++it) {
        std::cout << it->id << std::endl;
    }
    
    Weapon toDelete(5);
    auto it2 = std::find(weapons.begin(), weapons.end(), toDelete);
    if(it2 != weapons.end()) {
        weapons.erase(it2);
    }

    std::cout << "After deletion:" << std::endl;
    for(std::vector<Weapon>::iterator it = weapons.begin(); it != weapons.end(); ++it) {
        std::cout << it->id << std::endl;
    }

    return EXIT_SUCCESS;
}