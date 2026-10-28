/**
 * @file Data.hpp
 * @brief Declaração da classe Data, que representa e valida uma data no formato DD/MM.
 */
#ifndef DATA_HPP
#define DATA_HPP

#include <string>
#include <ostream>

/**
 * @class Data
 * @brief Representa uma data composta apenas por dia e mês (sem ano), validada na construção.
 *
 * A comparação entre datas considera primeiro o mês e depois o dia.
 *
 * @note Como não há ano, fevereiro aceita o dia 29 (ano bissexto) em qualquer caso.
 */
class Data 
{
private:
    std::string _data; ///< Texto da data validada, no formato DD/MM.
    int _dia;          ///< Dia da data (1 a 31, conforme o mês).
    int _mes;          ///< Mês da data (1 a 12).

    /**
     * @brief Valida se o dia e o mês formam uma data existente.
     *
     * O mês deve estar entre 1 e 12 e o dia deve estar entre 1 e a quantidade
     * máxima de dias do mês (fevereiro com 29 dias).
     *
     * @param dia Dia a ser validado.
     * @param mes Mês a ser validado.
     * @throws std::invalid_argument Se o mês ou o dia forem inválidos.
     */
    void validarData(int dia, int mes);

public:
    /**
     * @brief Constrói uma Data a partir de um texto no formato DD/MM.
     *
     * O texto deve ter exatamente 5 caracteres, com '/' na terceira posição
     * (por exemplo, "05/03").
     *
     * @param dataInput Texto contendo a data no formato DD/MM.
     * @throws std::invalid_argument Se o formato for inválido, se houver
     *         caracteres não numéricos ou se a data não existir.
     */
    Data(const std::string& dataInput);

    /**
     * @brief Construtor padrão (não inicializa dia e mês).
     */
    Data() = default; 

    /**
     * @brief Obtém o texto da data validada.
     * @return String no formato DD/MM.
     */
    std::string getDataValidada() const;

    /**
     * @brief Compara cronologicamente duas datas (mês primeiro, depois dia).
     * @param outraData Data a ser comparada com a atual.
     * @return @c true se esta data for anterior a @p outraData; @c false caso contrário.
     */
    bool operator<(const Data& outraData) const;

    /**
     * @brief Escreve a data (formato DD/MM) em um fluxo de saída.
     * @param os Fluxo de saída.
     * @param d Data a ser escrita.
     * @return Referência ao fluxo @p os, permitindo encadeamento.
     */
    friend std::ostream& operator<<(std::ostream& os, const Data& d);
};

#endif