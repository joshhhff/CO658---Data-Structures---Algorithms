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

    int factorialR(int number) {
        if (number == 1) {
            return 1;
        }
        return factorialR(number - 1) * number;
    }
};

int main() {
    IOObject obj;
    obj.DisplayIntLessThan(20);

    int fact = obj.factorialI(4);
    std::cout << "FactorialI of 4 is: " << fact << std::endl;

    fact = obj.factorialR(4);
    std::cout << "FactorialR of 4 is: " << fact << std::endl;
    return EXIT_SUCCESS;
}