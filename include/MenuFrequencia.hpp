/**
 * @file MenuFrequencia.hpp
 * @brief Declaracao da classe MenuFrequencia, menu de controle de faltas.
 */
#ifndef MENUFREQUENCIA_HPP
#define MENUFREQUENCIA_HPP

#include "Menu.hpp"
#include "SemestreAtual.hpp"
#include "Disciplina.hpp"

/**
 * @class MenuFrequencia
 * @brief Menu para gerenciar as faltas das disciplinas do semestre atual.
 */
class MenuFrequencia : public Menu
{
private:
    SemestreAtual& _semestreAtual; ///< Semestre em andamento cujas faltas sao gerenciadas.

    /**
     * @brief Pede ao usuario o ID de uma disciplina do semestre.
     * @return Ponteiro para a disciplina escolhida, ou @c nullptr nos casos:
     *         - nao ha disciplinas no semestre (um aviso e exibido);
     *         - o usuario cancelou digitando 0 (nenhuma mensagem e exibida);
     *         - o ID informado nao existe (uma mensagem de erro e exibida).
     */
    Disciplina* selecionarDisciplina();

    /**
     * @brief Registra uma falta na disciplina escolhida.
     *
     * Exibe o total de faltas atualizado ou, se o limite ja tiver sido atingido, a mensagem de erro.
     */
    void fluxoAdicionarFalta();

    /**
     * @brief Remove uma falta da disciplina escolhida.
     *
     * Exibe o total de faltas atualizado ou, se nao houver faltas, a mensagem de erro.
     */
    void fluxoRemoverFalta();

    /**
     * @brief Define diretamente o total de faltas da disciplina escolhida.
     *
     * A leitura se repete ate o usuario informar um valor entre 0 e o maximo de faltas permitido.
     */
    void fluxoDefinirFaltas();

public:
    /**
     * @brief Constroi o menu de frequencia recebendo apenas o SemestreAtual.
     * @param semestreAtual Semestre cujas disciplinas terao a frequencia gerenciada.
     */
    explicit MenuFrequencia(SemestreAtual& semestreAtual);

    /**
     * @copydoc Menu::exibir
     */
    virtual void exibir() override;

    /**
     * @brief Le a opcao do usuario e executa o fluxo correspondente.
     * @return @c this apos adicionar, remover ou definir faltas (permanece na tela);
     *         @c nullptr ao escolher "0 - Voltar" (retorna ao menu anterior).
     */
    virtual Menu* processarEntrada() override;
};

#endif