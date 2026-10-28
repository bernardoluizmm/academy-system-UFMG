#ifndef DISCIPLINA_HPP
#define DISCIPLINA_HPP

#include "ControleFrequencia.hpp"
#include "DiarioAtividades.hpp"
#include <string>

/**
 * @file Disciplina.hpp
 * @brief Declaração da classe que representa uma disciplina cursada pelo estudante.
 */

/**
 * @class Disciplina
 * @brief Representa uma disciplina, com seus dados cadastrais, controle de frequência
 *        e diário de atividades avaliativas.
 *
 * @see ControleFrequencia
 * @see DiarioAtividades
 */
class Disciplina 
{
private:
    int _id;                    ///< Identificador único da disciplina.
    std::string _codigo;        ///< Código da disciplina.
    std::string _codigoTurma;   ///< Código da turma.
    std::string _nome;          ///< Nome da disciplina.
    std::string _professor;     ///< Nome do professor responsável.
    std::string _salaBloco;     ///< Sala e bloco onde ocorrem as aulas.
    int _cargaHoraria;          ///< Carga horária total da disciplina.
    int _duracaoAulaMinutos;    ///< Duração de cada aula, em minutos.
    std::string _tipo;          ///< Tipo da disciplina.
    std::string _horarioDias;   ///< Dias e horários das aulas.

    ControleFrequencia _frequencia; ///< Controle de frequência (faltas) da disciplina.
    DiarioAtividades _avaliacoes;   ///< Diário com as atividades avaliativas da disciplina.

    /**
     * @brief Atualiza o limite de faltas do controle de frequência.
     *
     * Deve ser chamado quando os dados que influenciam esse limite
     * (como carga horária e duração da aula) são alterados.
     */
    void atualizarLimiteFaltas(); 

public:
    /**
     * @brief Constrói uma disciplina com todos os seus dados cadastrais.
     * @param id Identificador único da disciplina.
     * @param codigo Código da disciplina.
     * @param codigoTurma Código da turma.
     * @param nome Nome da disciplina.
     * @param professor Nome do professor.
     * @param salaBloco Sala e bloco das aulas.
     * @param cargaHoraria Carga horária total.
     * @param duracaoAulaMinutos Duração de cada aula, em minutos.
     * @param tipo Tipo da disciplina.
     * @param horarioDias Dias e horários das aulas.
     */
    Disciplina(int id,
               const std::string& codigo,
               const std::string& codigoTurma,
               const std::string& nome,
               const std::string& professor,
               const std::string& salaBloco,
               int cargaHoraria,
               int duracaoAulaMinutos,
               const std::string& tipo,
               const std::string& horarioDias);

    /** @name Getters
     *  Métodos de acesso aos dados da disciplina.
     *  @{ */

    /** @brief Retorna o identificador único da disciplina. */
    int getId() const;
    /** @brief Retorna o código da disciplina. */
    std::string getCodigo() const;
    /** @brief Retorna o código da turma. */
    std::string getCodigoTurma() const;
    /** @brief Retorna o nome da disciplina. */
    std::string getNome() const;
    /** @brief Retorna o nome do professor. */
    std::string getProfessor() const;
    /** @brief Retorna a sala e o bloco das aulas. */
    std::string getSalaBloco() const;
    /** @brief Retorna a carga horária total. */
    int getCargaHoraria() const;
    /** @brief Retorna a duração de cada aula, em minutos. */
    int getDuracaoAulaMinutos() const;
    /** @brief Retorna o tipo da disciplina. */
    std::string getTipo() const;
    /** @brief Retorna os dias e horários das aulas. */
    std::string getHorarioDias() const;
    /** @} */

    /**
     * @brief Acessa o controle de frequência da disciplina (leitura e escrita).
     * @return Referência ao ControleFrequencia.
     */
    ControleFrequencia& frequencia();

    /**
     * @brief Acessa o controle de frequência da disciplina (somente leitura).
     * @return Referência constante ao ControleFrequencia.
     */
    const ControleFrequencia& frequencia() const;

    /**
     * @brief Acessa o diário de atividades avaliativas (leitura e escrita).
     * @return Referência ao DiarioAtividades.
     */
    DiarioAtividades& avaliacoes();

    /**
     * @brief Acessa o diário de atividades avaliativas (somente leitura).
     * @return Referência constante ao DiarioAtividades.
     */
    const DiarioAtividades& avaliacoes() const;

    /** @name Setters
     *  Métodos de alteração dos dados da disciplina.
     *  @{ */

    /** @brief Define o código da disciplina. @param novoCodigo Novo código. */
    void setCodigo(const std::string& novoCodigo);
    /** @brief Define o código da turma. @param novaTurma Novo código de turma. */
    void setCodigoTurma(const std::string& novaTurma);
    /** @brief Define o nome da disciplina. @param novoNome Novo nome. */
    void setNome(const std::string& novoNome);
    /** @brief Define o professor. @param novoProfessor Nome do novo professor. */
    void setProfessor(const std::string& novoProfessor);
    /** @brief Define a sala e o bloco. @param novaSala Nova sala/bloco. */
    void setSalaBloco(const std::string& novaSala);
    /** @brief Define a carga horária. @param novaCargaHoraria Nova carga horária total. */
    void setCargaHoraria(int novaCargaHoraria);
    /** @brief Define a duração da aula. @param novaDuracaoMinutos Nova duração, em minutos. */
    void setDuracaoAulaMinutos(int novaDuracaoMinutos);
    /** @brief Define o tipo da disciplina. @param novoTipo Novo tipo. */
    void setTipo(const std::string& novoTipo);
    /** @brief Define os dias e horários. @param novoHorarioDias Novos dias e horários das aulas. */
    void setHorarioDias(const std::string& novoHorarioDias);
    /** @} */

    /**
     * @brief Converte a disciplina em texto para persistência em arquivo.
     * @return String com os dados serializados da disciplina.
     */
    std::string serializar() const;
};

#endif