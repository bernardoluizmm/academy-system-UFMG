#ifndef MENUINICIAL_HPP
#define MENUINICIAL_HPP

#include "Menu.hpp"

class MenuInicial : public Menu {
public:
    MenuInicial(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo);
    ~MenuInicial() override;

    virtual void exibir() override;
    virtual Menu* processarEntrada() override;
};

#endif