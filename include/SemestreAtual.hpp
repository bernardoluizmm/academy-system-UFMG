/**
 * @file SemestreAtual.hpp
 * @brief Declaração da classe SemestreAtual.
 */
#ifndef SEMESTREATUAL_HPP
#define SEMESTREATUAL_HPP

#include "Semestre.hpp"
#include "Disciplina.hpp"
#include <vector>
#include <string>

/**
 * @class SemestreAtual
 * @brief Semestre em andamento, que gerencia as disciplinas cursadas.
 *
 * O NSG e as horas são calculados dinamicamente a partir das disciplinas.
 * Só contam como integralizadas as disciplinas com nota parcial >= 60.
 */
class SemestreAtual : public Semestre 
{
private:
    std::vector<Disciplina> _disciplinas; ///< Disciplinas do semestre.
    int _contadorId;                      ///< Próximo ID automático de disciplina.

public:
    /** @brief Construtor padrão (semestre "2026/01"). */
    SemestreAtual();

    /**
     * @brief Construtor com identificador.
     * @param identificador Identificador do semestre (AAAA/01 ou AAAA/02).
     * @throws std::invalid_argument Se o identificador for inválido.
     */
    SemestreAtual(const std::string& identificador);

    /** @brief Destrutor. */
    virtual ~SemestreAtual();

    /**
     * @brief Calcula o NSG ponderado pela carga horária.
     * @return NSG entre 0 e 100 (0 se não houver disciplinas).
     */
    virtual float calcularNSG() const override;

    /** @brief Retorna o total de horas integralizadas no semestre. */
    virtual int getHorasIntegralizadas() const override;

    /** @brief Retorna as horas de disciplinas obrigatórias aprovadas. */
    virtual int getHorasObrigatorias() const override;

    /** @brief Retorna as horas de disciplinas optativas aprovadas. */
    virtual int getHorasOptativas() const override;

    /** @brief Retorna as horas de formação livre aprovadas. */
    virtual int getHorasFormacaoLivre() const override;

    /**
     * @brief Cria e adiciona uma disciplina com ID automático.
     * @param codigo Código da disciplina.
     * @param codigoTurma Código da turma.
     * @param nome Nome da disciplina.
     * @param professor Nome do professor.
     * @param salaBloco Sala e bloco.
     * @param cargaHoraria Carga horária total.
     * @param duracaoAulaMinutos Duração de cada aula, em minutos.
     * @param tipo Tipo ("Obrigatoria", "Optativa" ou "Formacao Livre").
     * @param horarioDias Horários e dias das aulas.
     */

};

#endif
