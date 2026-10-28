/**
 * @file CalculadorMedia.hpp
 * @brief Declaração da classe utilitária para cálculo da média (nota mínima de aprovação).
 */
#ifndef CALCULADORMEDIA_HPP
#define CALCULADORMEDIA_HPP

/**
 * @class CalculadorMedia
 * @brief Classe utilitária (apenas métodos estáticos) para cálculo da média.
 *
 * A média corresponde a 60% do valor considerado.
 */
class CalculadorMedia 
{
public:
    /**
     * @brief Calcula a média, equivalente a 60% do valor informado.
     * @param valor Valor total (por exemplo, pontos distribuídos) sobre o qual a média é calculada.
     * @return 60% de @p valor.
     */
    static float calcular(float valor);
};

#endif