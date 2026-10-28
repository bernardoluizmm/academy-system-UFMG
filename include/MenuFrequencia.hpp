/**
 * @file MenuFrequencia.hpp
 * @brief Declaração da classe MenuFrequencia, menu de controle de faltas.
 */
#ifndef MENUFREQUENCIA_HPP
#define MENUFREQUENCIA_HPP

#include "Menu.hpp"
#include "Disciplina.hpp"

/**
 * @class MenuFrequencia
 * @brief Menu para gerenciar as faltas das disciplinas do semestre atual do estudante.
 *
 * Exibe, para cada disciplina, as faltas atuais e o máximo permitido, e permite
 * adicionar uma falta, remover uma falta ou definir o total de faltas diretamente.
 */
class MenuFrequencia : public Menu 
{
private:
    /**
     * @brief Solicita ao usuário o ID de uma disciplina do semestre atual.
     *
     * Exibe uma mensagem de aviso ou de erro quando não há disciplinas ou quando
     * o ID não é encontrado. O usuário pode digitar 0 para cancelar.
     *
     * @return Ponteiro para a disciplina selecionada, ou @c nullptr se não houver
     *         semestre/disciplinas, se o usuário cancelar ou se o ID não existir.
     */
    Disciplina* selecionarDisciplina();

    /**
     * @brief Fluxo para registrar uma falta em uma disciplina escolhida pelo usuário.
     *
     * Exibe o novo total de faltas ou, se o limite já tiver sido atingido, a mensagem de erro.
     */
    void fluxoAdicionarFalta();

    /**
     * @brief Fluxo para remover uma falta de uma disciplina escolhida pelo usuário.
     *
     * Exibe o novo total de faltas ou, se não houver faltas, a mensagem de erro.
     */
    void fluxoRemoverFalta();

    /**
     * @brief Fluxo para definir diretamente o total de faltas de uma disciplina escolhida pelo usuário.
     *
     * Repete a solicitação até que o valor informado esteja entre 0 e o máximo de faltas.
     */
    void fluxoDefinirFaltas();

public:
    /**
     * @brief Constrói o menu de frequência.
     * @param estudante Estudante cujas disciplinas serão gerenciadas.
     * @param gerenciadorArquivo Gerenciador responsável pela persistência dos dados.
     */
    MenuFrequencia(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo);

    /**
     * @brief Destrutor.
     */
    virtual ~MenuFrequencia() override;

    /**
     * @brief Exibe o cabeçalho, a tabela de disciplinas (ID, código, nome, faltas atuais e máximo) e as opções do menu.
     *
     * Se não houver semestre atual ou disciplinas cadastradas, exibe uma mensagem informativa no lugar da tabela.
     */
    virtual void exibir() override;

    /**
     * @brief Lê a opção escolhida pelo usuário e executa a ação correspondente.
     *
     * Opções: 1 (adicionar falta), 2 (remover falta), 3 (definir faltas) e 0 (voltar).
     * Opções inválidas são rejeitadas e a leitura é repetida.
     *
     * @return Ponteiro para um novo menu alocado dinamicamente (cuja posse é do chamador):
     *         um novo MenuFrequencia após as opções 1 a 3, ou um MenuPrincipal para a opção 0.
     */
    virtual Menu* processarEntrada() override;
};

#endif