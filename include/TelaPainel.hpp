#ifndef TELAPAINEL_HPP
#define TELAPAINEL_HPP

#include <string>

#include "Tela.hpp"

/**
 * @file TelaPainel.hpp
 * @brief Declaração da tela de painel (dashboard) do estudante.
 */

/**
 * @class TelaPainel
 * @brief Dashboard completo com visão geral da situação acadêmica.
 *
 * Exibe dados pessoais, disciplinas do semestre atual com seus conceitos
 * parciais, progresso de integralização por categoria e o gráfico de
 * evolução do NSG em modo texto.
 */
class TelaPainel : public Tela {
public:
    /**
     * @brief Constrói a tela de painel.
     * @param estudante Referência ao estudante (a tela não é dona do objeto).
     */
    TelaPainel(Estudante& estudante);

    /**
     * @brief Exibe o dashboard: nome, curso, NSG, disciplinas com conceito,
     *        progresso por categoria e gráfico do NSG.
     * @return true para voltar ao menu principal.
     */
    bool executar() override;

    /**
     * @brief Retorna o nome identificador da tela.
     * @return "Painel".
     */
    std::string getNome() const override;

private:
    /**
     * @brief Exibe o gráfico de evolução do NSG em texto (barras horizontais).
     *
     * Usa os pontos gerados por Curso::gerarDadosGrafico().
     */
    void exibirGraficoNSG();

    /**
     * @brief Exibe barras de progresso por categoria de disciplina
     *        (Obrigatórias, Optativas e Formação Livre).
     */
    void exibirProgresso();
};

#endif  // TELAPAINEL_HPP
