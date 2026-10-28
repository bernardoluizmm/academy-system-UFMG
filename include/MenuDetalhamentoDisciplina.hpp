#ifndef MENUDETALHAMENTODISCIPLINA_HPP
#define MENUDETALHAMENTODISCIPLINA_HPP

#include "Menu.hpp"
#include "Disciplina.hpp"

/**
 * @file MenuDetalhamentoDisciplina.hpp
 * @brief Declaração do menu de detalhamento de disciplinas.
 */

/**
 * @class MenuDetalhamentoDisciplina
 * @brief Menu responsável por exibir informações detalhadas das disciplinas do estudante.
 *
 * Permite detalhar uma disciplina específica ou todas as disciplinas de uma só vez.
 *
 * @see Menu
 * @see Disciplina
 */
class MenuDetalhamentoDisciplina : public Menu 
{
private:
    /**
     * @brief Exibe na tela os dados detalhados de uma disciplina.
     * @param disciplina Disciplina a ser detalhada.
     */
    void exibirDetalhamentoDisciplina(const Disciplina& disciplina) const;

    /**
     * @brief Conduz o fluxo de detalhamento de uma disciplina específica.
     *
     * Solicita ao usuário a escolha de uma disciplina e exibe seus detalhes.
     */
    void fluxoDetalharDisciplinaEspecifica();

    /**
     * @brief Conduz o fluxo de detalhamento de todas as disciplinas do estudante.
     */
    void fluxoDetalharTodasDisciplinas() const;

public:
    /**
     * @brief Constrói o menu de detalhamento de disciplinas.
     * @param estudante Estudante cujas disciplinas serão detalhadas.
     * @param gerenciadorArquivo Gerenciador de arquivos utilizado pelo menu.
     */
    MenuDetalhamentoDisciplina(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo);

    /**
     * @brief Destrutor virtual.
     */
    virtual ~MenuDetalhamentoDisciplina() override;

    /**
     * @brief Exibe as opções do menu de detalhamento.
     */
    virtual void exibir() override;

    /**
     * @brief Lê a opção escolhida pelo usuário e executa o fluxo correspondente.
     * @return Ponteiro para o próximo menu a ser exibido.
     */
    virtual Menu* processarEntrada() override;
};

#endif