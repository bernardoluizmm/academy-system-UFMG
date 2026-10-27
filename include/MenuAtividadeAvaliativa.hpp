#ifndef MENUATIVIDADEAVALIATIVA_HPP
#define MENUATIVIDADEAVALIATIVA_HPP

#include "Menu.hpp"
#include "Disciplina.hpp"

/**
 * @file MenuAtividadeAvaliativa.hpp
 * @brief Declaração do menu de gerenciamento de atividades avaliativas.
 */

/**
 * @class MenuAtividadeAvaliativa
 * @brief Menu responsável pelo gerenciamento das atividades avaliativas das disciplinas.
 *
 * Permite ao estudante selecionar uma disciplina e, a partir dela, criar, editar,
 * apagar atividades avaliativas e lançar notas.
 *
 * @see Menu
 * @see Disciplina
 */
class MenuAtividadeAvaliativa : public Menu 
{
private:
    /**
     * @brief Solicita ao usuário que escolha uma das disciplinas do estudante.
     * @return Ponteiro para a disciplina selecionada, ou @c nullptr caso nenhuma
     *         disciplina seja selecionada.
     */
    Disciplina* selecionarDisciplina();

    /**
     * @brief Exibe na tela as atividades avaliativas de uma disciplina.
     * @param disciplina Disciplina cujas atividades serão listadas.
     */
    void exibirAtividadesDaDisciplina(const Disciplina& disciplina) const;

    /**
     * @brief Conduz o fluxo de criação de uma nova atividade avaliativa.
     *
     * Seleciona a disciplina, coleta os dados da atividade e a registra no diário
     * de atividades da disciplina.
     */
    void fluxoCriarAtividade();

    /**
     * @brief Conduz o fluxo de lançamento de nota em uma atividade avaliativa.
     */
    void fluxoLancarNota();

    /**
     * @brief Conduz o fluxo de edição de uma atividade avaliativa existente.
     */
    void fluxoEditarAtividade();

    /**
     * @brief Conduz o fluxo de remoção de uma atividade avaliativa existente.
     */
    void fluxoApagarAtividade();

public:
    /**
     * @brief Constrói o menu de atividades avaliativas.
     * @param estudante Estudante cujas disciplinas e atividades serão manipuladas.
     * @param gerenciadorArquivo Gerenciador usado para persistir as alterações em arquivo.
     */
    MenuAtividadeAvaliativa(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo);

    /**
     * @brief Destrutor virtual.
     */
    virtual ~MenuAtividadeAvaliativa() override;

    /**
     * @brief Exibe as opções do menu de atividades avaliativas.
     */
    virtual void exibir() override;

    /**
     * @brief Lê a opção escolhida pelo usuário e executa o fluxo correspondente.
     * @return Ponteiro para o próximo menu a ser exibido.
     */
    virtual Menu* processarEntrada() override;
};

#endif