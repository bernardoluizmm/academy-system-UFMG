/**
 * @file TelaFrequencia.hpp
 * @brief Declaração da tela de controle de frequência (faltas).
 * @author Samuel
 */
 
#ifndef TELAFREQUENCIA_HPP
#define TELAFREQUENCIA_HPP
 
#include "Tela.hpp"
#include "Disciplina.hpp"
 
/**
 * @class TelaFrequencia
 * @brief Tela para acompanhar e atualizar as faltas de cada disciplina.
 *
 * O usuário escolhe uma disciplina, vê o resumo de faltas e pode
 * incrementar ou decrementar a contagem por meio de um sub-menu
 * (incrementar / decrementar / voltar).
 */
class TelaFrequencia : public Tela {
public:
    /**
     * @brief Constrói a tela de frequência.
     * @param estudante Referência ao estudante manipulado (a tela não é dona dele).
     */
    explicit TelaFrequencia(Estudante& estudante);
 
    /**
     * @brief Executa o fluxo: escolher disciplina, exibir faltas e alterá-las.
     * @return @c true quando o usuário escolhe voltar ao menu principal.
     */
    bool executar() override;
 
    /**
     * @brief Retorna o nome identificador da tela.
     * @return A string "Frequência".
     */
    std::string getNome() const override;
 
private:
    /**
     * @brief Lista as disciplinas do semestre atual e pede que o usuário escolha uma.
     * @return Índice (base 0) da disciplina escolhida, ou -1 se cancelar
     *         ou se não houver disciplinas.
     */
    int escolherDisciplina();
 
    /**
     * @brief Exibe o resumo de frequência de uma disciplina.
     *
     * Mostra as faltas atuais, as faltas permitidas e o percentual de
     * faltas já consumido. Apenas leitura: não altera a disciplina.
     *
     * @param disc Disciplina a ser resumida.
     */
    void exibirResumo(const Disciplina& disc);
};
 
#endif
 