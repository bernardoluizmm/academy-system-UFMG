/**
 * @file CalculadorConceito.hpp
 * @brief Declaração da classe utilitária para cálculo de conceito.
 */
#ifndef CALCULADORCONCEITO_HPP
#define CALCULADORCONCEITO_HPP

/**
 * @class CalculadorConceito
 * @brief Classe utilitária (apenas métodos estáticos) que converte um percentual de nota em conceito.
 */
class CalculadorConceito 
{
public:
    /**
     * @brief Determina o conceito correspondente a um percentual de aproveitamento.
     *
     * Faixas utilizadas:
     * | Percentual | Conceito |
     * |------------|----------|
     * | >= 90      | A        |
     * | >= 80      | B        |
     * | >= 70      | C        |
     * | >= 60      | D        |
     * | >= 40      | E        |
     * | < 40       | F        |
     *
     * @param notaPercentual Percentual de aproveitamento (0 a 100).
     * @return Caractere do conceito: 'A', 'B', 'C', 'D', 'E' ou 'F'.
     */
    static char calcular(float notaPercentual);
};

#endif