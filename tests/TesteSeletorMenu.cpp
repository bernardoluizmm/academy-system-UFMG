#include "doctest.h"
#include "SeletorMenu.hpp"
#include "Menu.hpp"

class MenuSimples : public Menu {
public:
    int vezesExibido = 0;
    Menu* proximo = nullptr;
    bool substituir = false;

    void exibir() override {
        vezesExibido++;
    }

    Menu* processarEntrada() override {
        Menu* retorno = proximo;
        proximo = nullptr;
        return retorno;
    }

    bool substituirPilhaAoTransicionar() const override {
        return substituir;
    }
};

TEST_CASE("Teste 01: SeletorMenu - Inicializacao com nullptr nao causa erro") {
    SeletorMenu seletor(nullptr);
    CHECK_NOTHROW(seletor.executar());
}

TEST_CASE("Teste 02: SeletorMenu - Executa um menu simples e encerra ao receber nullptr") {
    MenuSimples* tela = new MenuSimples();
    SeletorMenu seletor(tela);

    CHECK_NOTHROW(seletor.executar());
}

TEST_CASE("Teste 03: SeletorMenu - Empilha segundo menu e volta ao primeiro depois") {
    MenuSimples* telaFilha = new MenuSimples();
    MenuSimples* telaPai = new MenuSimples();
    telaPai->proximo = telaFilha; 

    SeletorMenu seletor(telaPai);
    CHECK_NOTHROW(seletor.executar());
}

TEST_CASE("Teste 04: SeletorMenu - Substitui a pilha inteira quando substituirPilhaAoTransicionar e true") {
    MenuSimples* telaPrincipal = new MenuSimples();
    MenuSimples* telaCadastro = new MenuSimples();
    telaCadastro->proximo = telaPrincipal;
    telaCadastro->substituir = true;

    SeletorMenu seletor(telaCadastro);
    CHECK_NOTHROW(seletor.executar());
}
