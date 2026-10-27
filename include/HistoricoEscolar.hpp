/**
 * @file HistoricoEscolar.hpp
 * @brief Declaração da classe HistoricoEscolar.
 */
#ifndef HISTORICOESCOLAR_HPP
#define HISTORICOESCOLAR_HPP

#include <vector>
#include <string>
#include "SemestreConsolidado.hpp"
#include "SemestreAtual.hpp"

/**
 * @class HistoricoEscolar
 * @brief Reúne os semestres consolidados e o semestre atual do aluno.
 *
 * Possui o semestre atual por ponteiro, por isso implementa a regra dos três
 * (construtor de cópia, operador de atribuição e destrutor).
 */
class HistoricoEscolar 
{
private:
    std::vector<SemestreConsolidado> _semestresPassados; ///< Semestres já encerrados.
    SemestreAtual* _semestreAtual;                       ///< Semestre em andamento (possuído).

public:
    /** @brief Construtor padrão. Cria o semestre atual "2026/01". */
    HistoricoEscolar();

    /**
     * @brief Construtor de cópia (cópia profunda).
     * @param outro Histórico a copiar.
     */
    HistoricoEscolar(const HistoricoEscolar& outro);

    /**
     * @brief Operador de atribuição (cópia profunda).
     * @param outro Histórico a copiar.
     * @return Referência a este objeto.
     */
    HistoricoEscolar& operator=(const HistoricoEscolar& outro);

    /** @brief Destrutor. Libera o semestre atual. */
    ~HistoricoEscolar();
    };

#endif
