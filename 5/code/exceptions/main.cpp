#include <iostream>

int div(double a, double b, double *res) {
    if (!b) {
        return -1;
    }

    *res = a / b;
    return 0;
}

struct ZeroDiv {
};

double div(double a, double b) {
    if (!b) {
        throw ZeroDiv();
    }
    return a / b;
}

int main() {
    double res = 0.0;
    double a = 1.0;
    double b = 0.0;

    if (div(a, b, &res)) {
        std::cout << "0-div" << std::endl;
    }
    std::cout << res << std::endl;

    try {
        std::cout << div(a, b) << std::endl;
    }
    catch (const ZeroDiv& e){
        std::cout << "0-div cpp style" << std::endl;
        throw;
    }
    catch (int i){
        std::cout << i << std::endl;
    }

    //std::exception
    return 0;
}