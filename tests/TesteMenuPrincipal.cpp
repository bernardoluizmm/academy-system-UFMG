#include "doctest.h"
#include "MenuPrincipal.hpp"
#include <sstream>
#include <iostream>
#include <cstdio>

TEST_CASE("Teste 01: MenuPrincipal - Opcao 1 abre o MenuDisciplina") {
    Curso curso(1, "2024/01");
    HistoricoEscolar historico("2025/01");
    Estudante estudante("Gabriel", curso, historico);
    GerenciadorArquivo gerenciador("teste_menu_principal.txt");
    MenuPrincipal menu(estudante, gerenciador);

    std::istringstream entrada("1\n");
    std::cin.rdbuf(entrada.rdbuf());

    Menu* proximoMenu = menu.processarEntrada();
    CHECK(proximoMenu != nullptr);
    CHECK(proximoMenu != &menu);

    delete proximoMenu;
}

TEST_CASE("Teste 02: MenuPrincipal - Opcao 2 abre o MenuAtividadeAvaliativa") {
    Curso curso(1, "2024/01");
    HistoricoEscolar historico("2025/01");
    Estudante estudante("Gabriel", curso, historico);
    GerenciadorArquivo gerenciador("teste_menu_principal.txt");
    MenuPrincipal menu(estudante, gerenciador);

    std::istringstream entrada("2\n");
    std::cin.rdbuf(entrada.rdbuf());

    Menu* proximoMenu = menu.processarEntrada();
    CHECK(proximoMenu != nullptr);
    CHECK(proximoMenu != &menu);

    delete proximoMenu;
}

TEST_CASE("Teste 03: MenuPrincipal - Opcao 3 abre o MenuFrequencia") {
    Curso curso(1, "2024/01");
    HistoricoEscolar historico("2025/01");
    Estudante estudante("Gabriel", curso, historico);
    GerenciadorArquivo gerenciador("teste_menu_principal.txt");
    MenuPrincipal menu(estudante, gerenciador);

    std::istringstream entrada("3\n");
    std::cin.rdbuf(entrada.rdbuf());

    Menu* proximoMenu = menu.processarEntrada();
    CHECK(proximoMenu != nullptr);
    CHECK(proximoMenu != &menu);

    delete proximoMenu;
}

TEST_CASE("Teste 04: MenuPrincipal - Opcao 4 abre o MenuDetalhamentoDisciplina") {
    Curso curso(1, "2024/01");
    HistoricoEscolar historico("2025/01");
    Estudante estudante("Gabriel", curso, historico);
    GerenciadorArquivo gerenciador("teste_menu_principal.txt");
    MenuPrincipal menu(estudante, gerenciador);

    std::istringstream entrada("4\n");
    std::cin.rdbuf(entrada.rdbuf());

    Menu* proximoMenu = menu.processarEntrada();
    CHECK(proximoMenu != nullptr);
    CHECK(proximoMenu != &menu);

    delete proximoMenu;
}

TEST_CASE("Teste 05: MenuPrincipal - Opcao 5 consolida o semestre atual e avanca para o proximo") {
    Curso curso(1, "2024/01");
    HistoricoEscolar historico("2025/01");
    Estudante estudante("Gabriel", curso, historico);
    GerenciadorArquivo gerenciador("teste_menu_principal.txt");
    MenuPrincipal menu(estudante, gerenciador);

    std::istringstream entrada("5\n1\n");
    std::cin.rdbuf(entrada.rdbuf());

    Menu* proximoMenu = menu.processarEntrada();

    CHECK(proximoMenu == &menu);
    CHECK(estudante.getHistorico().getSemestreAtual()->getIdentificador() == "2025/02");
    CHECK(estudante.getHistorico().getSemestresPassados().size() == 1);
}

TEST_CASE("Teste 06: MenuPrincipal - Opcao 0 salva o arquivo e retorna nullptr para sair") {
    const std::string nomeArq = "teste_saida_principal.txt";
    std::remove(nomeArq.c_str());

    Curso curso(1, "2024/01");
    HistoricoEscolar historico("2025/01");
    Estudante estudante("Gabriel", curso, historico);
    GerenciadorArquivo gerenciador(nomeArq);
    MenuPrincipal menu(estudante, gerenciador);

    std::istringstream entrada("0\n");
    std::cin.rdbuf(entrada.rdbuf());

    Menu* proximoMenu = menu.processarEntrada();

    CHECK(proximoMenu == nullptr);
    CHECK(gerenciador.arquivoExiste() == true);

    std::remove(nomeArq.c_str());
}
