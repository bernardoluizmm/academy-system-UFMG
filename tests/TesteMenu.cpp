#include "doctest.h"
#include "Menu.hpp"
#include <sstream>
#include <iostream>
#include <stdexcept>

class MenuTeste : public Menu {
public:
    void exibir() override {}
    Menu* processarEntrada() override { return nullptr; }

    int lerInt(const std::string& msg) { return entradaSanitizada<int>(msg); }
    float lerFloat(const std::string& msg) { return entradaSanitizada<float>(msg); }
    std::string lerString(const std::string& msg) { return entradaSanitizada<std::string>(msg); }
    bool confirmar() { return confirmarDadoImutavel(); }
};

TEST_CASE("Teste 01: Menu - Comportamento padrao de substituirPilhaAoTransicionar") {
    MenuTeste menu;
    CHECK(menu.substituirPilhaAoTransicionar() == false);
}

TEST_CASE("Teste 02: Menu - Leitura sanitizada de numero inteiro valido") {
    MenuTeste menu;
    std::istringstream entrada("42\n");
    std::cin.rdbuf(entrada.rdbuf());

    int valor = menu.lerInt("");
    CHECK(valor == 42);
}

TEST_CASE("Teste 03: Menu - Leitura sanitizada ignora tentativa invalida ate ler inteiro correto") {
    MenuTeste menu;
    std::istringstream entrada("abc\n10\n");
    std::cin.rdbuf(entrada.rdbuf());

    int valor = menu.lerInt("");
    CHECK(valor == 10);
}

TEST_CASE("Teste 04: Menu - Leitura sanitizada de float valido") {
    MenuTeste menu;
    std::istringstream entrada("85.5\n");
    std::cin.rdbuf(entrada.rdbuf());

    float valor = menu.lerFloat("");
    CHECK(valor == doctest::Approx(85.5f));
}

TEST_CASE("Teste 05: Menu - Leitura de string remove espacos extras nas pontas") {
    MenuTeste menu;
    std::istringstream entrada("   Ciencia da Computacao   \n");
    std::cin.rdbuf(entrada.rdbuf());

    std::string texto = menu.lerString("");
    CHECK(texto == "Ciencia da Computacao");
}

TEST_CASE("Teste 06: Menu - Leitura de string rejeita caractere proibido '|' e aceita a proxima") {
    MenuTeste menu;
    std::istringstream entrada("Texto|Invalido\nTexto Valido\n");
    std::cin.rdbuf(entrada.rdbuf());

    std::string texto = menu.lerString("");
    CHECK(texto == "Texto Valido");
}

TEST_CASE("Teste 07: Menu - Confirmar dado imutavel retorna true ao digitar 1") {
    MenuTeste menu;
    std::istringstream entrada("1\n");
    std::cin.rdbuf(entrada.rdbuf());

    bool confirmou = menu.confirmar();
    CHECK(confirmou == true);
}

TEST_CASE("Teste 08: Menu - Confirmar dado imutavel retorna false ao digitar 2") {
    MenuTeste menu;
    std::istringstream entrada("2\n");
    std::cin.rdbuf(entrada.rdbuf());

    bool confirmou = menu.confirmar();
    CHECK(confirmou == false);
}

TEST_CASE("Teste 09: Menu - Fim inesperado da entrada (EOF) lanca excecao") {
    MenuTeste menu;
    std::istringstream entrada("");
    std::cin.rdbuf(entrada.rdbuf());

    CHECK_THROWS_AS(menu.lerInt(""), std::runtime_error);
}
