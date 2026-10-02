/**
 * @file ControleFrequencia.hpp
 * @brief Declaração da classe ControleFrequencia.
 */
#ifndef CONTROLE_FREQUENCIA_HPP
#define CONTROLE_FREQUENCIA_HPP

/**
 * @class ControleFrequencia
 * @brief Responsável pelo acompanhamento e registro de faltas de uma disciplina.
 */
class ControleFrequencia {
private:
    /** @brief Quantidade máxima de faltas permitidas antes da reprovação por infrequência. */
    int _faltasPermitidas;

    /** @brief Quantidade de faltas acumuladas no semestre. */
    int _faltasAtuais;

public:
    /**
     * @brief Construtor da classe ControleFrequencia.
     * @param faltasPermitidas Número limite de faltas permitidas na disciplina.
     */
    ControleFrequencia(int faltasPermitidas);

    /**
     * @brief Retorna o limite de faltas permitidas.
     * @return Número de faltas permitidas.
     */
    int getFaltasPermitidas() const;

    /**
     * @brief Retorna o número atual de faltas registradas.
     * @return Quantidade de faltas atuais.
     */
    int getFaltasAtuais() const;

    /**
     * @brief Incrementa em 1 o número de faltas do estudante.
     */
    void incrementarFalta();

    /**
     * @brief Decrementa em 1 o número de faltas do estudante (mínimo 0).
     */
    void decrementarFalta();

    /**
     * @brief Calcula a taxa percentual de presença do estudante.
     * @return Percentual de frequência (0.0 a 100.0).
     */
    double calcularPercentualFrequencia() const;
};

#endif // CONTROLE_FREQUENCIA_HPP