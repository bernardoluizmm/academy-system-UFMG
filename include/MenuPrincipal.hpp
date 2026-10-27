#ifndef MENUPRINCIPAL_HPP
#define MENUPRINCIPAL_HPP

#include "Menu.hpp"

class MenuPrincipal : public Menu 
{
private:
    void exibirResumoAcademico() const;
    void exibirTabelaGeralDisciplinas() const;

public:
    MenuPrincipal(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo);
    virtual ~MenuPrincipal() override;

    virtual void exibir() override;
    virtual Menu* processarEntrada() override;
};

#endif