/**
 * @file Semestre.hpp
 * @brief Declaração da classe base abstrata Semestre.
 */
#ifndef SEMESTRE_HPP
#define SEMESTRE_HPP

#include <string>
#include <vector>

/**
 * @class Semestre
 * @brief Classe base abstrata que representa um semestre letivo.
 *
 * Armazena o identificador (formato AAAA/01 ou AAAA/02) e o estado de
 * trancamento. As classes derivadas definem como NSG e horas são obtidos.
 */
class Semestre 
{
protected:
    std::string _identificador; ///< Identificador do semestre (AAAA/01 ou AAAA/02).
    bool _trancado;             ///< Indica se o semestre foi trancado.

    /**
     * @brief Extrai o ano de um identificador.
     * @param idStr Identificador no formato AAAA/PP.
     * @return Ano como inteiro.
     */
    static int extrairAno(const std::string& idStr);

    /**
     * @brief Extrai o período de um identificador.
     * @param idStr Identificador no formato AAAA/PP.
     * @return Período (1 ou 2).
     */
    static int extrairPeriodo(const std::string& idStr);

public:
    /**
     * @brief Calcula o identificador do semestre seguinte.
     * @param idAtual Identificador atual (ex.: "2026/02").
     * @return Identificador seguinte (ex.: "2027/01").
     */
    static std::string proximoIdentificadorSemestre(const std::string& idAtual);

    /**
     * @brief Construtor.
     * @param identificador Identificador no formato AAAA/01 ou AAAA/02.
     * @param trancado Indica se o semestre está trancado (padrão: false).
     * @throws std::invalid_argument Se o identificador for inválido.
     */
    Semestre(const std::string& identificador, bool trancado = false);

    /** @brief Destrutor virtual. */
    virtual ~Semestre() = default;

    /**
     * @brief Obtém o identificador do semestre.
     * @return Referência constante ao identificador.
     */
    const std::string& getIdentificador() const;

    /**
     * @brief Informa se o semestre está trancado.
     * @return true se trancado, false caso contrário.
     */
    bool isTrancado() const;

    /**
     * @brief Define o estado de trancamento.
     * @param estado Novo estado.
     */
    void setTrancado(bool estado);

    /**
     * @brief Calcula o NSG (Nota do Semestre Global) do semestre.
     * @return NSG entre 0 e 100.
     */

};

#endif
