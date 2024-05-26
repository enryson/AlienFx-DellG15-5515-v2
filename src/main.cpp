#include "AlienFx_SDK.h"
#include <iostream>
#include <string>
#include <sstream>

int main(int argc, char* argv[]) {
    // Verifica se o número de argumentos é suficiente
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " all=r,g,b" << std::endl;
        return 1;
    }

    // Converte o argumento para uma string
    std::string input = argv[1];

    // Verifica se o argumento começa com "all="
    std::string prefix = "all=";
    if (input.find(prefix) != 0) {
        std::cerr << "Comando inválido. Deve começar com 'all='" << std::endl;
        return 1;
    }

    // Extrai a parte dos valores RGB
    std::string rgb_values_str = input.substr(prefix.length());

    // Parseia os valores RGB
    int r, g, b;
    char comma1, comma2;
    std::istringstream rgb_stream(rgb_values_str);
    if ((rgb_stream >> r >> comma1 >> g >> comma2 >> b) && (comma1 == ',') && (comma2 == ',')) {
        std::cout << "Valores RGB: " << r << ", " << g << ", " << b << std::endl;

        AlienFx_SDK alienFX;
        alienFX.SetColorAll(r,g,b);
    } else {
        std::cerr << "Formato de valores RGB inválido." << std::endl;
        return 1;
    }

    return 0;
}
