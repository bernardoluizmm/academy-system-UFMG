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
     * @brief Recalcula o limite de faltas a partir da carga horaria e da duracao da aula.
     *
     * Aplica o novo limite ao controle de frequencia. Se as faltas atuais excederem o novo
     * limite, elas sao reduzidas ate ele (ver ControleFrequencia::setMaxFaltas).
     *
     * @see CalculadorMaxFaltas::calcularDiasMaximosFalta
     */
    void atualizarLimiteFaltas();
 

public:
  /** @name Validadores Estaticos
     *  Metodos estaticos para validacao previa de entradas antes da construcao.
     *  @{ */

    /**
     * @brief Valida o codigo da disciplina.
     * @param codigo Codigo a ser validado.
     * @throws std::invalid_argument Se o codigo for vazio ou tiver mais de 8 caracteres.
     */
    static void validarCodigo(const std::string& codigo);

    /**
     * @brief Valida o codigo da turma.
     * @param turma Codigo da turma a ser validado.
     * @throws std::invalid_argument Se o codigo for vazio ou tiver mais de 6 caracteres.
     */
    static void validarCodigoTurma(const std::string& turma);

    /**
     * @brief Valida o nome da disciplina.
     * @param nome Nome a ser validado.
     * @throws std::invalid_argument Se o nome for vazio ou tiver mais de 22 caracteres.
     */
    static void validarNome(const std::string& nome);

    /**
     * @brief Valida o nome do professor.
     * @param professor Nome a ser validado.
     * @throws std::invalid_argument Se o nome for vazio ou tiver mais de 100 caracteres.
     */
    static void validarProfessor(const std::string& professor);

    /**
     * @brief Valida a sala e o bloco das aulas.
     * @param sala Texto a ser validado.
     * @throws std::invalid_argument Se o texto for vazio ou tiver mais de 100 caracteres.
     */
    static void validarSalaBloco(const std::string& sala);

    /**
     * @brief Valida a carga horaria total.
     * @param cargaHoraria Carga horaria, em horas.
     * @throws std::invalid_argument Se for menor ou igual a zero ou nao for multiplo de 15.
     */
    static void validarCargaHoraria(int cargaHoraria);

    /**
     * @brief Valida a duracao de cada aula.
     * @param duracaoMinutos Duracao da aula, em minutos.
     * @throws std::invalid_argument Se for menor que 50 minutos.
     */
    static void validarDuracaoAulaMinutos(int duracaoMinutos);

    /**
     * @brief Valida o tipo da disciplina.
     * @param tipo Tipo a ser validado.
     * @throws std::invalid_argument Se nao for "Obrigatoria", "Optativa" ou "Formacao Livre".
     */
    static void validarTipo(const std::string& tipo);

    /**
     * @brief Valida o texto de horario e dias das aulas.
     * @param horarioDias Texto a ser validado.
     * @throws std::invalid_argument Se o texto for vazio ou tiver mais de 100 caracteres.
     */
    static void validarHorarioDias(const std::string& horarioDias);
    /** @} */

    /**
     * @brief Constroi uma disciplina com todos os seus dados cadastrais.
     *
     * O limite de faltas e calculado automaticamente a partir da carga horaria e da duracao da aula.
     *
     * @param id Identificador unico da disciplina (nao negativo).
     * @param codigo Codigo da disciplina (1 a 8 caracteres).
     * @param codigoTurma Codigo da turma (1 a 6 caracteres).
     * @param nome Nome da disciplina (1 a 22 caracteres).
     * @param professor Nome do professor (1 a 100 caracteres).
     * @param salaBloco Sala e bloco das aulas (1 a 100 caracteres).
     * @param cargaHoraria Carga horaria total (maior que zero e multiplo de 15).
     * @param duracaoAulaMinutos Duracao de cada aula, em minutos (minimo 50).
     * @param tipo Tipo da disciplina ("Obrigatoria", "Optativa" ou "Formacao Livre").
     * @param horarioDias Dias e horarios das aulas (1 a 100 caracteres).
     * @throws std::invalid_argument Se o id for negativo ou se qualquer dado for invalido.
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