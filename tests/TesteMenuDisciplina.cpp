#include "doctest.h"
#include "MenuDisciplina.hpp"
#include "SemestreAtual.hpp"
#include "Disciplina.hpp"
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <string>

namespace 
{
    struct RedirecionadorIO 
    {
        std::stringstream entrada;
        std::stringstream saida;
        std::streambuf* cinOriginal;
        std::streambuf* coutOriginal;

        RedirecionadorIO(const std::string& textoEntrada = "") 
            : entrada(textoEntrada),
              cinOriginal(std::cin.rdbuf(entrada.rdbuf())),
              coutOriginal(std::cout.rdbuf(saida.rdbuf())) 
        {}

        ~RedirecionadorIO() 
        {
            std::cin.rdbuf(cinOriginal);
            std::cout.rdbuf(coutOriginal);
        }
    };
}

TEST_CASE("Exibicao do MenuDisciplina - Semestre vazio e com disciplinas") 
{
    SemestreAtual semestre("2026/02");
    MenuDisciplina menu(semestre);

    SUBCASE("Exibir com semestre vazio") 
    {
        RedirecionadorIO io;
        menu.exibir();

        std::string textoImpresso = io.saida.str();
        CHECK(textoImpresso.find("GERENCIAMENTO DE DISCIPLINAS") != std::string::npos);
        CHECK(textoImpresso.find("Nenhuma disciplina cadastrada no semestre atual.") != std::string::npos);
        CHECK(menu.substituirPilhaAoTransicionar() == false);
    }

    SUBCASE("Exibir com disciplina cadastrada") 
    {
        semestre.adicionarDisciplina("DCC204", "TZ1", "PDS II", "Prof", "ICEx 2010", 60, 100, "Obrigatoria", "Seg/Qua");
        RedirecionadorIO io;
        menu.exibir();

        std::string textoImpresso = io.saida.str();
        CHECK(textoImpresso.find("DCC204") != std::string::npos);
        CHECK(textoImpresso.find("TZ1") != std::string::npos);
        CHECK(textoImpresso.find("PDS II") != std::string::npos);
        CHECK(textoImpresso.find("60h") != std::string::npos);
        CHECK(textoImpresso.find("Obrigatoria") != std::string::npos);
    }
}