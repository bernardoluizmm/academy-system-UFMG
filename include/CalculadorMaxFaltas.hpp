/**
 * @file CalculadorMaxFaltas.hpp
 * @brief Declaração da classe utilitária para cálculo do máximo de faltas.
 */
#ifndef CALCULADORMAXFALTAS_HPP
#define CALCULADORMAXFALTAS_HPP

/**
 * @class CalculadorMaxFaltas
 * @brief Classe utilitária (apenas métodos estáticos) para calcular o limite de faltas de uma disciplina.
 */
class CalculadorMaxFaltas 
{
public:
    /**
     * @brief Calcula o número máximo de encontros (dias) em que o estudante pode faltar.
     *
     * O limite corresponde a 25% da carga horária (em horas-aula de 50 minutos),
     * dividido pela quantidade de horas-aula de cada encontro:
     * - limite de horas-aula = @p cargaHorariaHoras / 4;
     * - horas-aula por encontro = @p duracaoAulaMinutos / 50 (divisão inteira);
     * - resultado = limite de horas-aula / horas-aula por encontro (divisão inteira).
     *
     * @param cargaHorariaHoras Carga horária total da disciplina. Deve ser maior que zero e divisível por 15.
     * @param duracaoAulaMinutos Duração de cada encontro, em minutos. Deve ser de, no mínimo, 50.
     * @return Quantidade máxima de faltas (encontros) permitida.
     * @throws std::invalid_argument Se a carga horária for inválida (<= 0 ou não divisível por 15)
     *         ou se a duração da aula for menor que 50 minutos.
     */
    static int calcularDiasMaximosFalta(int cargaHorariaHoras, int duracaoAulaMinutos);
};

#endif