#include "doctest.h"
#include "MenuCadastroUsuario.hpp"
#include "MenuPrincipal.hpp"
#include <sstream>
#include <iostream>

TEST_CASE("Teste 01: MenuCadastroUsuario - Deve substituir a pilha ao transicionar") {
    std::unique_ptr<Estudante> estudante(nullptr);
    GerenciadorArquivo gerenciador("teste_cadastro.txt");
    MenuCadastroUsuario menu(estudante, gerenciador);

    CHECK(menu.substituirPilhaAoTransicionar() == true);
}

TEST_CASE("Teste 02: MenuCadastroUsuario - Cadastro de estudante calouro sem semestres anteriores") {
    std::unique_ptr<Estudante> estudante(nullptr);
    GerenciadorArquivo gerenciador("teste_cadastro.txt");
    MenuCadastroUsuario menu(estudante, gerenciador);

    std::istringstream entrada("Pedro\n1\n2025/01\n2025/01\n1\n");
    std::cin.rdbuf(entrada.rdbuf());

    Menu* proximoMenu = menu.processarEntrada();

    CHECK(proximoMenu != nullptr);
    CHECK(estudante != nullptr);
    CHECK(estudante->getNome() == "Pedro");
    CHECK(estudante->getCurso().getNome() == "Ciencia da Computacao");
    CHECK(estudante->getCurso().getSemestreIngresso() == "2025/01");
    CHECK(estudante->getHistorico().getSemestresPassados().size() == 0);

    delete proximoMenu;
}

TEST_CASE("Teste 03: MenuCadastroUsuario - Cadastro com semestre anterior consolidado normal") {
    std::unique_ptr<Estudante> estudante(nullptr);
    GerenciadorArquivo gerenciador("teste_cadastro.txt");
    MenuCadastroUsuario menu(estudante, gerenciador);

    std::istringstream entrada("Pedro\n2\n2024/01\n2024/02\n1\n2\n80\n60\n15\n0\n1\n");
    std::cin.rdbuf(entrada.rdbuf());

    Menu* proximoMenu = menu.processarEntrada();

    CHECK(proximoMenu != nullptr);
    CHECK(estudante != nullptr);
    CHECK(estudante->getNome() == "Pedro");
    CHECK(estudante->getHistorico().getSemestresPassados().size() == 1);
    CHECK(estudante->getHistorico().getSemestresPassados()[0].calcularNSG() == doctest::Approx(80.0f));
    CHECK(estudante->getHistorico().getSemestresPassados()[0].getHorasObrigatorias() == 60);

    delete proximoMenu;
}

TEST_CASE("Teste 04: MenuCadastroUsuario - Cadastro com semestre anterior trancado") {
    std::unique_ptr<Estudante> estudante(nullptr);
    GerenciadorArquivo gerenciador("teste_cadastro.txt");
    MenuCadastroUsuario menu(estudante, gerenciador);

    std::istringstream entrada("Lucas\n1\n2024/01\n2024/02\n1\n1\n1\n");
    std::cin.rdbuf(entrada.rdbuf());

    Menu* proximoMenu = menu.processarEntrada();

    CHECK(proximoMenu != nullptr);
    CHECK(estudante != nullptr);
    CHECK(estudante->getHistorico().getSemestresPassados().size() == 1);
    CHECK(estudante->getHistorico().getSemestresPassados()[0].isTrancado() == true);
    CHECK(estudante->getHistorico().getSemestresPassados()[0].calcularNSG() == doctest::Approx(0.0f));

    delete proximoMenu;
}
