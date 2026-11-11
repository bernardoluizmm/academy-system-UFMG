/**
 * @file SemestreConsolidado.hpp
 * @brief Declaração da classe SemestreConsolidado.
 */
#ifndef SEMESTRECONSOLIDADO_HPP
#define SEMESTRECONSOLIDADO_HPP

#include "Semestre.hpp"
#include <string>

/**
 * @class SemestreConsolidado
 * @brief Semestre já encerrado, com NSG e horas fixos.
 *
 * Se o semestre for trancado, NSG e horas são sempre retornados como zero.
 */
class SemestreConsolidado : public Semestre 
{
private:
    float _nsgFixo;           ///< NSG final do semestre.
    int _horasObrigatorias;   ///< Horas obrigatórias integralizadas.
    int _horasOptativas;      ///< Horas optativas integralizadas.
    int _horasFormacaoLivre;  ///< Horas de formação livre integralizadas.

public:
    /**
     * @brief Construtor.
     * @param identificador Identificador do semestre (AAAA/01 ou AAAA/02).
     * @param nsgFixo NSG final (0 a 100).
     * @param horasObrigatorias Horas obrigatórias (múltiplo de 15).
     * @param horasOptativas Horas optativas (múltiplo de 15).
     * @param horasFormacaoLivre Horas de formação livre (múltiplo de 15).
     * @param trancado Se true, os valores numéricos são ignorados.
     * @throws std::invalid_argument Se algum valor for inválido.
     */
    SemestreConsolidado(const std::string& identificador,
                        float nsgFixo,
                        int horasObrigatorias,
                        int horasOptativas,
                        int horasFormacaoLivre,
                        bool trancado = false);

  /**
     * @brief Obtem o NSG fixo do semestre.
     * @return NSG final, ou 0 se o semestre foi trancado.
     */
    virtual float calcularNSG() const override;

    /** @brief Retorna o total de horas integralizadas (0 se trancado). */
    virtual int getHorasIntegralizadas() const override;

    /** @brief Retorna as horas obrigatórias (0 se trancado). */
    virtual int getHorasObrigatorias() const override;

    /** @brief Retorna as horas optativas (0 se trancado). */
    virtual int getHorasOptativas() const override;

    /** @brief Retorna as horas de formação livre (0 se trancado). */
    virtual int getHorasFormacaoLivre() const override;

    /**
     * @brief Serializa o semestre em texto.
     * @return Linha no formato
     *         SEMESTRE_CONSOLIDADO|id|nsg|obrig|optat|livre|trancado.
     */
    std::string serializar() const;

};

#endif
