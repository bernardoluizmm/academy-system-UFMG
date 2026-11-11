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
         *
          * Disciplinas sem atividades concluídas são ignoradas no cálculo.
         * @return NSG entre 0 e 100 (0 se não houver disciplinas).
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
    void adicionarDisciplina(const std::string& codigo,
                             const std::string& codigoTurma,
                             const std::string& nome,
                             const std::string& professor,
                             const std::string& salaBloco,
                             int cargaHoraria,
                             int duracaoAulaMinutos,
                             const std::string& tipo,
                             const std::string& horarioDias);

    /**
     * @brief Adiciona uma disciplina já construída.
     * @param disciplina Disciplina a adicionar.
     * @throws std::invalid_argument Se já existir disciplina com o mesmo ID.
     */
    void adicionarDisciplina(const Disciplina& disciplina);

    /**
     * @brief Remove uma disciplina pelo ID.
     * @param idDisciplina ID da disciplina.
     * @throws std::invalid_argument Se não for encontrada.
     */
    void removerDisciplina(int idDisciplina);

    /**
     * @brief Busca uma disciplina pelo ID.
     * @param idDisciplina ID da disciplina.
     * @return Ponteiro para a disciplina, ou nullptr se não existir.
     */
    Disciplina* buscarDisciplina(int idDisciplina);

    /** @brief Retorna as disciplinas (somente leitura). */
    const std::vector<Disciplina>& getDisciplinas() const;

    /** @brief Retorna as disciplinas (acesso editável). */
    std::vector<Disciplina>& getDisciplinasEditavel();

    /**
     * @brief Serializa o semestre e suas disciplinas em texto.
     * @return Texto iniciado por SEMESTRE_ATUAL|id, seguido das disciplinas.
     */
    std::string serializar() const;

};

#endif
