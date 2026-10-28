/**
 * @file ControleFrequencia.hpp
 * @brief Declaração da classe ControleFrequencia, responsável pelo controle de faltas.
 */
#ifndef CONTROLEFREQUENCIA_HPP
#define CONTROLEFREQUENCIA_HPP

/**
 * @class ControleFrequencia
 * @brief Controla as faltas de uma disciplina em relação ao limite máximo permitido.
 *
 * Garante que o número de faltas atuais permaneça entre 0 e o máximo permitido.
 */
class ControleFrequencia 
{
private:
    int _maxFaltas;     ///< Número máximo de faltas permitido.
    int _faltasAtuais;  ///< Número de faltas acumuladas até o momento.

public:
    /**
     * @brief Constrói o controle de frequência, iniciando com zero faltas.
     * @param maxFaltas Número máximo de faltas permitido.
     */
    ControleFrequencia(int maxFaltas);

    /**
     * @brief Obtém o número máximo de faltas permitido.
     * @return Limite de faltas.
     */
    int getMaxFaltas() const;

    /**
     * @brief Obtém o número de faltas acumuladas.
     * @return Quantidade atual de faltas.
     */
    int getFaltasAtuais() const;

    /**
     * @brief Define o número máximo de faltas permitido.
     *
     * Se as faltas atuais excederem o novo limite, elas são reduzidas
     * para que fiquem iguais ao novo máximo.
     *
     * @param novoMaxFaltas Novo limite de faltas.
     */
    void setMaxFaltas(int novoMaxFaltas);

    /**
     * @brief Define diretamente o número de faltas acumuladas.
     * @param novasFaltas Nova quantidade de faltas (de 0 até o máximo permitido).
     * @throws std::invalid_argument Se @p novasFaltas for negativo ou maior que o máximo de faltas.
     */
    void setFaltasAtuais(int novasFaltas);

    /**
     * @brief Registra uma falta (incrementa o contador de faltas atuais).
     * @throws std::invalid_argument Se o máximo de faltas já tiver sido atingido.
     */
    void adicionarFalta();

    /**
     * @brief Remove uma falta registrada (decrementa o contador de faltas atuais).
     * @throws std::invalid_argument Se não houver faltas para remover.
     */
    void removerFalta();
};

#endif