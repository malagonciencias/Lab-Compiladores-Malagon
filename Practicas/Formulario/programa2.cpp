#include <iostream>

int main() {

    int arr[] = {6, 42, 919};
    int *ptr;
    ptr = arr;
    std::cout << *ptr << std::endl;
    ptr += 1;
    std::cout << *ptr << std::endl;
    std::cout << *++ptr << std::endl;
    std::cout << *ptr-- << std::endl;
    ptr += 1;
    std::cout << *ptr << std::endl;
}