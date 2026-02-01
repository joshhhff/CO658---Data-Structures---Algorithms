#include <iostream>

class IOObject {
public:

    void DisplayIntLessThan(int n) {
        --n;
        if (n > 0) {
            DisplayIntLessThan(n);
        }
        std::cout << n << std::endl;
    }

    int factorialI(int n) {
        int t, result;
        result = 1;
        for (t = 1; t <= n; t++) result *= t;
        return result;
    }
};

int main() {
    IOObject obj;
    obj.DisplayIntLessThan(20);

    int fact = obj.factorialI(4);
    std::cout << "Factorial of 4 is: " << fact << std::endl;
    return EXIT_SUCCESS;
}