#ifndef MENUFREQUENCIA_HPP
#define MENUFREQUENCIA_HPP

#include "Menu.hpp"
#include "Disciplina.hpp"

class MenuFrequencia : public Menu 
{
private:
    Disciplina* selecionarDisciplina();
    void fluxoAdicionarFalta();
    void fluxoRemoverFalta();
    void fluxoDefinirFaltas();

public:
    MenuFrequencia(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo);
    virtual ~MenuFrequencia() override;

    virtual void exibir() override;
    virtual Menu* processarEntrada() override;
};

#endif