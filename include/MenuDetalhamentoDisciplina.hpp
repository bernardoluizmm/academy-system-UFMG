#ifndef MENUDETALHAMENTODISCIPLINA_HPP
#define MENUDETALHAMENTODISCIPLINA_HPP

#include "Menu.hpp"
#include "Disciplina.hpp"

class MenuDetalhamentoDisciplina : public Menu 
{
private:
    void exibirDetalhamentoDisciplina(const Disciplina& disciplina) const;
    void fluxoDetalharDisciplinaEspecifica();
    void fluxoDetalharTodasDisciplinas() const;

public:
    MenuDetalhamentoDisciplina(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo);
    virtual ~MenuDetalhamentoDisciplina() override;

    virtual void exibir() override;
    virtual Menu* processarEntrada() override;
};

#endif