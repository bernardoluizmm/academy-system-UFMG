#ifndef MENUCADASTROUSUARIO_HPP
#define MENUCADASTROUSUARIO_HPP

#include "Menu.hpp"

class MenuCadastroUsuario : public Menu 
{
public:
    MenuCadastroUsuario(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo);
    virtual ~MenuCadastroUsuario() override;

    virtual void exibir() override;
    virtual Menu* processarEntrada() override;
};

#endif