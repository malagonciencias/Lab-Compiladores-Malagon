#include <iostream>

// Este programa te pide el valor de tu carta y te dice cuánto vale

int main() {
    char card_name[2];
    std::cout << "La letra o número de la carta para saber su valor en Blackjack" << std::endl;
    std::cin >> card_name;

    int val = 0;
    switch(card_name[0]) {
        case 'K':
            val = 10;
            break;
        case 'Q':
            val = 10;
            break;
        case 'J':
            val = 10;
            break;
        case 'A':
            std::cout << "Esta carta puede ser 11 o 1, tu decides \n";
            break;
        default:
            val = atoi(card_name);
            if(!val || val < 2 || val > 10) {
                std::cout << "Esta carta no existe en la baraja inglesa." << std::endl;
            }
            break;
    }

    std::cout << "El valor de la carta es:" << val << std::endl;
    return 0;
}