#include "doctest.h"
#include "MenuCarregarUsuario.hpp"
#include "MenuPrincipal.hpp"
#include <cstdio>

TEST_CASE("Teste 01: MenuCarregarUsuario - Deve substituir a pilha ao transicionar") {
    std::unique_ptr<Estudante> estudante(nullptr);
    GerenciadorArquivo gerenciador("arquivo_teste.txt");
    MenuCarregarUsuario menu(estudante, gerenciador);

    CHECK(menu.substituirPilhaAoTransicionar() == true);
}

TEST_CASE("Teste 02: MenuCarregarUsuario - Carrega perfil existente e avanca para MenuPrincipal") {
    const std::string nomeArq = "teste_menu_carregar.txt";
    std::remove(nomeArq.c_str());

    GerenciadorArquivo gerenciador(nomeArq);
    Curso curso(2, "2024/01");
    HistoricoEscolar historico("2024/01");
    Estudante estudanteSalvo("Carlos Eduardo", curso, historico);
    gerenciador.salvar(estudanteSalvo);

    std::unique_ptr<Estudante> estudanteCarregado(nullptr);
    MenuCarregarUsuario menu(estudanteCarregado, gerenciador);
    Menu* proximoMenu = menu.processarEntrada();

    CHECK(proximoMenu != nullptr);
    CHECK(estudanteCarregado != nullptr);
    CHECK(estudanteCarregado->getNome() == "Carlos Eduardo");
    CHECK(estudanteCarregado->getCurso().getNome() == "Sistemas de Informacao");

    delete proximoMenu;
    std::remove(nomeArq.c_str());
}

TEST_CASE("Teste 03: MenuCarregarUsuario - Retorna nullptr quando o arquivo nao existe") {
    std::remove("arquivo_inexistente.txt");
    GerenciadorArquivo gerenciador("arquivo_inexistente.txt");
    std::unique_ptr<Estudante> estudante(nullptr);

    MenuCarregarUsuario menu(estudante, gerenciador);
    Menu* proximoMenu = menu.processarEntrada();

    CHECK(proximoMenu == nullptr);
    CHECK(estudante == nullptr);
}
