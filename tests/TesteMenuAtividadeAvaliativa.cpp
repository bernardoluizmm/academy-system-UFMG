#include "doctest.h"
#include "MenuAtividadeAvaliativa.hpp"
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

    
    struct RedirecionadorDeTerminal
    {
        std::streambuf* bufferEntrada;
        std::streambuf* bufferSaida;
        std::ios::fmtflags formato;
        std::streamsize precisao;

        RedirecionadorDeTerminal(std::istringstream& entrada, std::ostringstream& saida)
            : bufferEntrada(std::cin.rdbuf(entrada.rdbuf())),
              bufferSaida(std::cout.rdbuf(saida.rdbuf())),
              formato(std::cout.flags()),
              precisao(std::cout.precision())
        {
        }

        ~RedirecionadorDeTerminal()
        {
            std::cin.rdbuf(bufferEntrada);
            std::cout.rdbuf(bufferSaida);
            std::cout.flags(formato);
            std::cout.precision(precisao);
            std::cin.clear();
        }
    };
