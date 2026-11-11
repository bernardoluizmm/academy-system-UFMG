/**
 * @file MenuPrincipal.hpp
 * @brief Declaracao da tela principal do sistema.
 */
#ifndef MENUPRINCIPAL_HPP
#define MENUPRINCIPAL_HPP

#include "Menu.hpp"
#include "Estudante.hpp"
#include "GerenciadorArquivo.hpp"

/**
 * @class MenuPrincipal
 * @brief Tela principal: mostra o resumo academico e empilha as telas de gerenciamento especificas.
 */
class MenuPrincipal : public Menu
{
private:
    Estudante& _estudante;                   ///< Referencia ao estudante logado (ja validado e instanciado).
    GerenciadorArquivo& _gerenciadorArquivo; ///< Gerenciador usado para salvar o perfil ao sair.

    /**
     * @brief Exibe o resumo academico do estudante.
     *
     * Mostra nome, curso, semestre de ingresso e semestre atual, os indicadores de rendimento
     * (NSG parcial, medio e global) e o progresso de integralizacao do curso (percentual e horas
     * cumpridas/exigidas em obrigatorias, optativas, formacao livre e total).
     */
    void exibirResumoAcademico() const;

    /**
     * @brief Exibe a tabela geral das disciplinas do semestre atual.
     *
     * Para cada disciplina mostra ID, nome, pontos distribuidos, nota obtida, media parcial,
     * conceito parcial, faltas e maximo de faltas. Exibe um aviso se nao houver disciplinas.
     */
    void exibirTabelaGeralDisciplinas() const;

public:
    /**
     * @brief Constroi a tela principal.
     * @param estudante Estudante cujo perfil sera exibido e editado.
     * @param gerenciadorArquivo Gerenciador usado para salvar o perfil ao sair.
     */
    MenuPrincipal(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo);

    /**
     * @brief Exibe o resumo academico, a tabela de disciplinas e as opcoes do menu principal.
     */
    virtual void exibir() override;

    /**
     * @brief Le a opcao do usuario e decide a transicao de tela.
     *
     * Opcoes: 1 a 4 abrem os menus de disciplinas, atividades, frequencia e detalhamento;
     * 5 consolida o semestre atual e inicia o proximo; 0 salva o perfil e encerra.
     *
     * @return Ponteiro para o novo menu a empilhar (opcoes 1 a 4), @c this ao consolidar o semestre
     *         (opcao 5) ou @c nullptr ao salvar e sair (opcao 0).
     */
    virtual Menu* processarEntrada() override;
};

#endif
