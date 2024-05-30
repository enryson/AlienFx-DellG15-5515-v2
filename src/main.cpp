#include "AlienFx_SDK.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

bool parseRGB(const std::string &str, int &r, int &g, int &b)
{
    char comma1, comma2;
    std::istringstream rgb_stream(str);
    return (rgb_stream >> r >> comma1 >> g >> comma2 >> b) && (comma1 == ',') && (comma2 == ',');
}

int main(int argc, char *argv[])
{
    if (argc >= 1) {
            std::cout << "Nome do programa: " << argv[0] << std::endl;
        AlienFx_SDK alienFX;
        if (argc < 2)
        {
            std::cerr << "Uso: " << argv[0] << " all=r,g,b | [zone=r,g,b]..." << std::endl;
            return 1;
        }

        std::map<std::string, std::vector<int>> zones;
        bool all_set = false;
        std::vector<int> all_rgb(3);

        for (int i = 1; i < argc; ++i)
        {
            std::string input = argv[i];

            size_t eq_pos = input.find('=');
            if (eq_pos == std::string::npos)
            {
                std::cerr << "Formato inválido: " << input << std::endl;
                return 1;
            }

            std::string zone = input.substr(0, eq_pos);
            std::string rgb_values_str = input.substr(eq_pos + 1);

            int r, g, b;
            if (!parseRGB(rgb_values_str, r, g, b))
            {
                std::cerr << "Formato de valores RGB inválido: " << rgb_values_str << std::endl;
                return 1;
            }

            if (zone == "all")
            {
                all_set = true;
                all_rgb = {r, g, b};
            }
            else
            {
                zones[zone] = {r, g, b};
            }
        }

        if (all_set)
        {
            std::cout << "Comando 'all' - RGB: "
                    << all_rgb[0] << ", "
                    << all_rgb[1] << ", "
                    << all_rgb[2] << std::endl;
            alienFX.SetColorAll(all_rgb[0], all_rgb[1], all_rgb[2]);
        }
        else
        {
            alienFX.SetColorZones(zones);
        }
        return 0;
    }
}