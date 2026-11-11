#include "doctest.h"
#include "MenuFrequencia.hpp"
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

TEST_CASE("Exibicao do MenuFrequencia - Semestre vazio e com disciplinas") 
{
    SemestreAtual semestre("2026/02");
    MenuFrequencia menu(semestre);

    SUBCASE("Exibir com semestre vazio") 
    {
        RedirecionadorIO io;
        menu.exibir();

        std::string textoImpresso = io.saida.str();
        CHECK(textoImpresso.find("GERENCIAMENTO DE FREQUENCIA E FALTAS") != std::string::npos);
        CHECK(textoImpresso.find("Nenhuma disciplina cadastrada no semestre atual.") != std::string::npos);
        CHECK(textoImpresso.find("1 - Adicionar 1 falta em uma disciplina") != std::string::npos);
        CHECK(menu.substituirPilhaAoTransicionar() == false);
    }

    SUBCASE("Exibir com disciplina cadastrada") 
    {
        semestre.adicionarDisciplina("MAT001", "T1", "Calculo I", "Prof", "Sala", 60, 100, "Obrigatoria", "Seg");
        RedirecionadorIO io;
        menu.exibir();

        std::string textoImpresso = io.saida.str();
        CHECK(textoImpresso.find("MAT001") != std::string::npos);
        CHECK(textoImpresso.find("Calculo I") != std::string::npos);
        CHECK(textoImpresso.find("Max Faltas") != std::string::npos);
    }
}