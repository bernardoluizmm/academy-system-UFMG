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
     /**
     * @brief Adiciona um semestre consolidado ao histórico.
     * @param semestre Semestre a adicionar.
     */
    void adicionarSemestreConsolidado(const SemestreConsolidado& semestre);

    /** @brief Retorna os semestres consolidados. */
    const std::vector<SemestreConsolidado>& getSemestresPassados() const;

    /** @brief Remove todos os semestres consolidados. */
    void limparSemestresPassados();

    /** @brief Retorna o semestre atual (editável). */
    SemestreAtual* getSemestreAtual();

    /** @brief Retorna o semestre atual (somente leitura). */
    const SemestreAtual* getSemestreAtual() const;

    /**
     * @brief Substitui o semestre atual por um novo, vazio.
     * @param identificador Identificador do novo semestre.
     * @throws std::invalid_argument Se o identificador for inválido.
     */
    void definirSemestreAtual(const std::string& identificador);

    /**
     * @brief Consolida o semestre atual e inicia o semestre seguinte.
     * @param trancado Se true, o semestre é registrado como trancado (valores zerados).
     */
    void consolidarSemestreAtual(bool trancado = false);

    /**
     * @brief Calcula a média simples dos NSG dos semestres não trancados.
     * @return NSG médio (0 se não houver semestres válidos).
     */
    float calcularNSGMedio() const;

    /**
     * @brief Calcula o NSG global ponderado pelas horas integralizadas.
     * @return NSG global (0 se não houver horas).
     */
    float calcularNSGGlobal() const;

    /** @brief Soma as horas obrigatórias dos semestres passados. */
    int calcularTotalHorasObrigatorias() const;

    /** @brief Soma as horas optativas dos semestres passados. */
    int calcularTotalHorasOptativas() const;

    /** @brief Soma as horas de formação livre dos semestres passados. */
    int calcularTotalHorasFormacaoLivre() const;

    /** @brief Soma o total de horas integralizadas dos semestres passados. */
    int calcularTotalHorasIntegralizadas() const;

    /**
     * @brief Serializa todo o histórico em texto.
     * @return Uma linha por semestre consolidado, seguidas do semestre atual.
     */
    std::string serializar() const;
};

#endif
