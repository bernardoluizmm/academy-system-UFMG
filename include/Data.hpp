/**
 * @file Data.hpp
 * @brief Declaracao da classe Data, que representa e valida uma data no formato DD/MM.
 */
#ifndef DATA_HPP
#define DATA_HPP

#include <string>
#include <ostream>

/**
 * @class Data
 * @brief Representa uma data composta apenas por dia e mes (sem ano), validada na construcao.
 *
 * A comparacao entre datas considera primeiro o mes e depois o dia.
 *
 * @note Como nao ha ano, fevereiro aceita o dia 29 (ano bissexto) em qualquer caso.
 */
class Data 
{
private:
    std::string _data; ///< Texto da data validada, no formato DD/MM.
    int _dia;          ///< Dia da data (1 a 31, conforme o mes).
    int _mes;          ///< Mes da data (1 a 12).

    /**
     * @brief Valida se o dia e o mes formam uma data existente.
     *
     * O mes deve estar entre 1 e 12 e o dia deve estar entre 1 e a quantidade
     * maxima de dias do mes (fevereiro com 29 dias).
     *
     * @param dia Dia a ser validado.
     * @param mes Mes a ser validado.
     * @throws std::invalid_argument Se o mes ou o dia forem invalidos.
     */
    void validarData(int dia, int mes);

public:
    /**
     * @brief Constroi uma Data a partir de um texto no formato DD/MM.
     *
     * O texto deve ter exatamente 5 caracteres, com '/' na terceira posicao
     * (por exemplo, "05/03").
     *
     * @param dataInput Texto contendo a data no formato DD/MM.
     * @throws std::invalid_argument Se o formato for invalido, se houver
     *         caracteres nao numericos ou se a data nao existir.
     */
    Data(const std::string& dataInput);

    /**
     * @brief Obtem o texto da data validada.
     * @return String no formato DD/MM.
     */
    std::string getDataValidada() const;

    /**
     * @brief Compara cronologicamente duas datas (mes primeiro, depois dia).
     * @param outraData Data a ser comparada com a atual.
     * @return @c true se esta data for anterior a @p outraData; @c false caso contrario.
     */
    bool operator<(const Data& outraData) const;

    /**
     * @brief Escreve a data (formato DD/MM) em um fluxo de saida.
     * @param os Fluxo de saida.
     * @param d Data a ser escrita.
     * @return Referencia ao fluxo @p os, permitindo encadeamento.
     */
    friend std::ostream& operator<<(std::ostream& os, const Data& d);
};

#endif