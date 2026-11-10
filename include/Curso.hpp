/**
 * @file Curso.hpp
 * @brief Declaracao da classe Curso para gerenciamento das exigencias curriculares.
 */

#ifndef CURSO_HPP
#define CURSO_HPP

#include <string>

/**
 * @class Curso
 * @brief Representa o curso de graduacao do estudante e guarda as suas metas de carga horaria.
 * @details Configura automaticamente as horas exigidas (obrigatorias, optativas, formacao
 *          livre e adicionais) no momento da construcao com base na opcao do curso
 *          (Ciencia da Computacao ou Sistemas de Informacao) e no ano do semestre de ingresso.
 *          Segue o principio RAII: nasce completo e imutavel.
 */
class Curso 
{
public:
    static constexpr int OPCAO_CC = 1;                  /**< Codigo da opcao Ciencia da Computacao. */
    static constexpr int OPCAO_SI = 2;                  /**< Codigo da opcao Sistemas de Informacao. */
    static constexpr int ANO_REFORMA_CC = 2025;         /**< Ano de inicio do novo curriculo de CC. */

    static constexpr int HORAS_OBRIG_CC_ANTIGO = 2040;  /**< Horas obrigatorias de CC (ingresso < 2025). */
    static constexpr int HORAS_OPT_CC_ANTIGO = 1020;    /**< Horas optativas de CC (ingresso < 2025). */
    static constexpr int HORAS_LIVRE_CC_ANTIGO = 60;    /**< Horas de formacao livre de CC (ingresso < 2025). */
    static constexpr int HORAS_ADIC_CC_ANTIGO = 120;    /**< Horas adicionais de CC (ingresso < 2025). */
    static constexpr int HORAS_TOTAIS_CC_ANTIGO = 3240; /**< Total de horas de CC (ingresso < 2025). */

    static constexpr int HORAS_OBRIG_CC_NOVO = 1980;    /**< Horas obrigatorias de CC (ingresso >= 2025). */
    static constexpr int HORAS_OPT_CC_NOVO = 1110;      /**< Horas optativas de CC (ingresso >= 2025). */
    static constexpr int HORAS_LIVRE_CC_NOVO = 120;     /**< Horas de formacao livre de CC (ingresso >= 2025). */
    static constexpr int HORAS_ADIC_CC_NOVO = 0;        /**< Horas adicionais de CC (ingresso >= 2025). */
    static constexpr int HORAS_TOTAIS_CC_NOVO = 3210;   /**< Total de horas de CC (ingresso >= 2025). */

    static constexpr int HORAS_OBRIG_SI = 2100;         /**< Horas obrigatorias de SI. */
    static constexpr int HORAS_OPT_SI = 780;            /**< Horas optativas de SI. */
    static constexpr int HORAS_LIVRE_SI = 120;          /**< Horas de formacao livre de SI. */
    static constexpr int HORAS_ADIC_SI = 0;             /**< Horas adicionais de SI. */
    static constexpr int HORAS_TOTAIS_SI = 3000;        /**< Total de horas de SI. */

private:
    int _opcaoCurso;                 /**< Codigo da opcao de curso (1 = CC, 2 = SI). */
    std::string _nome;               /**< Nome por extenso do curso. */
    std::string _semestreIngresso;   /**< Semestre de ingresso no formato "AAAA/01" ou "AAAA/02". */
    int _horasTotaisObrigatorias;    /**< Carga horaria total exigida em disciplinas obrigatorias. */
    int _horasTotaisOptativas;       /**< Carga horaria total exigida em disciplinas optativas. */
    int _horasTotaisFormacaoLivre;   /**< Carga horaria total exigida em disciplinas de formacao livre. */
    int _horasAdicionais;            /**< Carga horaria adicional exigida pelo curriculo (quando aplicavel). */
    int _horasTotaisCurso;           /**< Carga horaria total necessaria para a integralizacao do curso. */

    /**
     * @brief Define o nome do curso e distribui as cargas horarias de acordo com o curriculo.
     */
    void configurarHorasPorCurriculo();

public:
    /**
     * @brief Construtor parametrizado que valida e inicializa definitivamente o curso (RAII).
     * @param opcaoCurso Codigo do curso (1 para Ciencia da Computacao, 2 para Sistemas de Informacao).
     * @param semestreIngresso Identificador do semestre de ingresso (formato "AAAA/01" ou "AAAA/02").
     * @throws std::invalid_argument Se a opcao de curso ou o formato do semestre forem invalidos.
     */
    Curso(int opcaoCurso, const std::string& semestreIngresso);

    /**
     * @brief Valida se a opcao numerica de curso e permitida (1 para CC ou 2 para SI).
     * @param opcao Codigo do curso a ser validado.
     * @throws std::invalid_argument Se a opcao for diferente de OPCAO_CC e OPCAO_SI.
     */
    static void validarOpcaoCurso(int opcao);

    /**
     * @brief Valida se o identificador do semestre de ingresso segue o formato AAAA/01 ou AAAA/02.
     * @param semIngresso String do semestre de ingresso.
     * @throws std::invalid_argument Se o formato do semestre for invalido.
     */
    static void validarSemestreIngresso(const std::string& semIngresso);

    /**
     * @brief Obtem o codigo numerico da opcao de curso.
     * @return Inteiro representando a opcao (1 ou 2).
     */
    int getOpcaoCurso() const;

    /**
     * @brief Obtem o nome do curso.
     * @return String com o nome do curso ("Ciencia da Computacao" ou "Sistemas de Informacao").
     */
    std::string getNome() const;

    /**
     * @brief Obtem o semestre de ingresso do estudante no curso.
     * @return String com o identificador do semestre de ingresso.
     */
    std::string getSemestreIngresso() const;

    /**
     * @brief Obtem o total de horas obrigatorias exigidas pelo curso.
     * @return Carga horaria obrigatoria total em horas.
     */
    int getHorasTotaisObrigatorias() const;

    /**
     * @brief Obtem o total de horas optativas exigidas pelo curso.
     * @return Carga horaria optativa total em horas.
     */
    int getHorasTotaisOptativas() const;

    /**
     * @brief Obtem o total de horas de formacao livre exigidas pelo curso.
     * @return Carga horaria de formacao livre total em horas.
     */
    int getHorasTotaisFormacaoLivre() const;

    /**
     * @brief Obtem o total de horas adicionais exigidas pelo curriculo do curso.
     * @return Carga horaria adicional em horas.
     */
    int getHorasAdicionais() const;

    /**
     * @brief Obtem a carga horaria total exigida para a conclusao do curso.
     * @return Carga horaria total do curso em horas.
     */
    int getHorasTotaisCurso() const;

    /**
     * @brief Serializa os dados do curso em uma linha de texto delimitada por '|'.
     * @return String no formato "CURSO|<opcaoCurso>|<semestreIngresso>".
     */
    std::string serializar() const;
};

#endif