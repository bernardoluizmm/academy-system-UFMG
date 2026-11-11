/**
 * @file MenuAtividadeAvaliativa.hpp
 * @brief Declaracao do menu de gerenciamento de atividades avaliativas.
 */
#ifndef MENUATIVIDADEAVALIATIVA_HPP
#define MENUATIVIDADEAVALIATIVA_HPP

#include "Menu.hpp"
#include "SemestreAtual.hpp"
#include "Disciplina.hpp"

/**
 * @class MenuAtividadeAvaliativa
 * @brief Menu responsavel pelo gerenciamento das atividades avaliativas das disciplinas do semestre atual.
 *
 * Recebe por injecao de dependencia apenas a referencia ao SemestreAtual,
 * mantendo baixo acoplamento em relacao ao restante do perfil do estudante.
 */
class MenuAtividadeAvaliativa : public Menu
{
private:
    SemestreAtual& _semestreAtual; ///< Referencia ao semestre em andamento.

    /**
     * @brief Lista as disciplinas do semestre e pede ao usuario que escolha uma pelo ID.
     * @return Ponteiro para a disciplina escolhida, ou @c nullptr nos casos:
     *         - nao ha disciplinas no semestre (um aviso e exibido);
     *         - o usuario cancelou digitando 0 (nenhuma mensagem e exibida);
     *         - o ID informado nao existe (uma mensagem de erro e exibida).
     */
    Disciplina* selecionarDisciplina();

    /**
     * @brief Exibe a tabela de atividades de uma disciplina.
     *
     * Para cada atividade mostra ID, nome, data, valor, nota obtida (ou "Pendente"),
     * conceito e media. Se nao houver atividades, exibe um aviso.
     *
     * @param disciplina Disciplina cujas atividades serao exibidas.
     */
    void exibirAtividadesDaDisciplina(const Disciplina& disciplina) const;

    /**
     * @brief Fluxo de criacao de atividade: escolhe a disciplina e pede nome, data e valor.
     *
     * Cada dado e lido e validado em lacos de repeticao ate ser aceito.
     */
    void fluxoCriarAtividade();

    /**
     * @brief Fluxo de lancamento de nota: escolhe a disciplina e a atividade e pede a nota obtida.
     *
     * A leitura se repete ate que a nota seja valida (entre 0 e o valor maximo da atividade).
     */
    void fluxoLancarNota();

    /**
     * @brief Fluxo de edicao de atividade: escolhe a disciplina e a atividade e abre um submenu.
     *
     * O submenu permite alterar nome, data, valor e nota, ou remover o lancamento da nota.
     * Apos alterar a data, as atividades sao reordenadas.
     */
    void fluxoEditarAtividade();

    /**
     * @brief Fluxo de exclusao de atividade: escolhe a disciplina e a atividade e pede confirmacao.
     */
    void fluxoApagarAtividade();

public:
    /**
     * @brief Constroi o menu de atividades avaliativas recebendo apenas o semestre atual.
     * @param semestreAtual Semestre cujas disciplinas e atividades serao manipuladas.
     */
    explicit MenuAtividadeAvaliativa(SemestreAtual& semestreAtual);

    /**
     * @brief Le a opcao do usuario e executa o fluxo correspondente.
     * @return @c this apos criar, lancar nota, editar ou apagar atividade (permanece na tela);
     *         @c nullptr ao escolher "0 - Voltar" (retorna ao menu anterior).
     */
    virtual Menu* processarEntrada() override;
    virtual void exibir() override;
};

#endif