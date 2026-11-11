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

TEST_CASE("Processar Entrada - Navegacao basica, opcoes invalidas e EOF") 
{
    SemestreAtual semestre("2026/02");
    MenuFrequencia menu(semestre);

    SUBCASE("Opcao 0 - Voltar ao Menu Principal retorna nullptr") 
    {
        RedirecionadorIO io("0\n");
        Menu* proximoMenu = menu.processarEntrada();
        CHECK(proximoMenu == nullptr);
    }

    SUBCASE("Opcoes invalidas e entradas nao numericas repetem o laco ate ler 0") 
    {
        RedirecionadorIO io("-1\n9\nabc\n0\n");
        Menu* proximoMenu = menu.processarEntrada();

        CHECK(proximoMenu == nullptr);
        std::string textoImpresso = io.saida.str();
        CHECK(textoImpresso.find("[ERRO] Opcao invalida. Escolha entre 0 e 3.") != std::string::npos);
        CHECK(textoImpresso.find("Erro: Tipo de entrada incorreto. Tente novamente.") != std::string::npos);
    }

    SUBCASE("Excecao de Fim de Fluxo (EOF)") 
    {
        RedirecionadorIO io("");
        CHECK_THROWS_AS(menu.processarEntrada(), std::runtime_error);
    }
}