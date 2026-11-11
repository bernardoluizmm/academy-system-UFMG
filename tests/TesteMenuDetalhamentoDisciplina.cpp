#include "doctest.h"
#include "MenuDetalhamentoDisciplina.hpp"
#include <iostream>
#include <sstream>
#include <string>

namespace
{
    struct Resultado
    {
        std::string saida;
        Menu* proximo;
    };
}