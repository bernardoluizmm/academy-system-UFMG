#ifndef MENUDISCIPLINA_HPP
#define MENUDISCIPLINA_HPP

#include "Menu.hpp"

class MenuDisciplina : public Menu 
{
private:
    void fluxoCriarDisciplina();
    void fluxoEditarDisciplina();
    void fluxoApagarDisciplina();
    std::string escolherTipoDisciplina();

public:
    MenuDisciplina(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo);
    virtual ~MenuDisciplina() override;

    virtual void exibir() override;
    virtual Menu* processarEntrada() override;
};

#endif