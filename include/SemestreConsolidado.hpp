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

    /** @brief Destrutor. */
    virtual ~SemestreConsolidado();

    /**
     * @brief Define o NSG fixo.
     * @param nsgFixo Valor entre 0 e 100.
     * @throws std::invalid_argument Se fora do intervalo.
     */

};

#endif
