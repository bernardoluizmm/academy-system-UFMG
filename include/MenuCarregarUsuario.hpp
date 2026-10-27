#ifndef MENUCARREGARUSUARIO_HPP
#define MENUCARREGARUSUARIO_HPP

#include "Menu.hpp"

class MenuCarregarUsuario : public Menu 
{
public:
    MenuCarregarUsuario(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo);
    virtual ~MenuCarregarUsuario() override;

    virtual void exibir() override;
    virtual Menu* processarEntrada() override;
};

#endif