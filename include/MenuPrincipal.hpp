#ifndef MENUPRINCIPAL_HPP
#define MENUPRINCIPAL_HPP

#include "Menu.hpp"

/**
 * @file MenuPrincipal.hpp
 * @brief Declaração da tela principal do sistema.
 */

/**
 * @class MenuPrincipal
 * @brief Tela principal: mostra o resumo acadêmico e leva às demais telas.
 *
 * Exibe os dados do estudante, os indicadores de NSG, o progresso de
 * integralização do curso e a tabela das disciplinas do semestre atual.
 * Em seguida oferece as opções para gerenciar disciplinas, atividades e
 * frequência, ver o detalhamento, consolidar o semestre atual ou salvar e sair.
 */
class MenuPrincipal : public Menu 
{
private:
    /**
     * @brief Exibe o cabeçalho com nome, curso, ingresso e semestre atual,
     *        os indicadores de NSG e o progresso de integralização do curso.
     *
     * O progresso é mostrado em percentual e em horas, para o curso completo
     * e para cada categoria (obrigatórias, formação livre e optativas). As
     * horas adicionais exigidas só aparecem se forem maiores que zero.
     * Se não houver semestre atual, o identificador aparece como "-".
     */
    void exibirResumoAcademico() const;

    /**
     * @brief Exibe a tabela geral das disciplinas do semestre atual.
     *
     * Para cada disciplina mostra ID, nome, nota distribuída, nota obtida,
     * média parcial, conceito, faltas e máximo de faltas. Se não houver
     * disciplinas, exibe uma mensagem informando isso.
     */
    void exibirTabelaGeralDisciplinas() const;

public:
    /**
     * @brief Constrói a tela principal.
     * @param estudante          Estudante exibido e manipulado (deve viver mais que o Menu).
     * @param gerenciadorArquivo Gerenciador usado para salvar o perfil (deve viver mais que o Menu).
     */
    MenuPrincipal(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo);

    /**
     * @brief Destrutor.
     */
    virtual ~MenuPrincipal() override;

    /**
     * @brief Exibe o resumo acadêmico, a tabela de disciplinas e as opções do menu.
     */
    virtual void exibir() override;

    /**
     * @brief Lê a opção do usuário e decide a próxima tela.
     *
     * Repete a leitura até receber uma opção entre 0 e 5:
     * - 1: MenuDisciplina;
     * - 2: MenuAtividadeAvaliativa;
     * - 3: MenuFrequencia;
     * - 4: MenuDetalhamentoDisciplina;
     * - 5: pergunta se o semestre atual deve ser consolidado (normalmente ou como
     *   trancado) ou se a operação deve ser cancelada, e depois volta ao MenuPrincipal;
     * - 0: salva o perfil e encerra o programa. Se o salvamento falhar, o erro
     *   é exibido e o programa encerra mesmo assim.
     *
     * @return Ponteiro para a próxima tela, alocada com new (quem recebe passa a ser
     *         responsável por liberá-lo), ou nullptr para encerrar o programa.
     * @throws std::runtime_error Se o fluxo de entrada terminar (EOF) durante a leitura.
     */
    virtual Menu* processarEntrada() override;
};

#endif