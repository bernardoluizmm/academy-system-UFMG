/**
 * @file Curso.hpp
 * @brief Declaração da classe Curso para gerenciamento das exigências curriculares.
 */

#ifndef CURSO_HPP
#define CURSO_HPP

#include <string>

/**
 * @class Curso
 * @brief Representa o curso de graduação do estudante e guarda as suas metas de carga horária.
 * @details Configura automaticamente as horas exigidas (obrigatórias, optativas, formação
 *          livre e adicionais) com base na opção do curso (Ciência da Computação ou Sistemas
 *          de Informação) e no ano do semestre de ingresso. Uma vez inicializado, os dados
 *          tornam-se imutáveis.
 */
class Curso 
{
private:
    int _opcaoCurso;                 /**< Código da opção de curso (1 = Ciência da Computação, 2 = Sistemas de Informação). */
    std::string _nome;               /**< Nome por extenso do curso. */
    std::string _semestreIngresso;   /**< Semestre de ingresso no formato "AAAA/01" ou "AAAA/02". */
    int _horasTotaisObrigatorias;    /**< Carga horária total exigida em disciplinas obrigatórias. */
    int _horasTotaisOptativas;       /**< Carga horária total exigida em disciplinas optativas. */
    int _horasTotaisFormacaoLivre;   /**< Carga horária total exigida em disciplinas de formação livre. */
    int _horasAdicionais;            /**< Carga horária adicional exigida pelo currículo (quando aplicável). */
    int _horasTotaisCurso;           /**< Carga horária total necessária para a integralização do curso. */
    bool _configurado;               /**< Indica se o curso já foi consolidado/inicializado (impede alterações posteriores). */

    /**
     * @brief Define o nome do curso e distribui as cargas horárias de acordo com o currículo.
     * @details Verifica a opção de curso e o ano extraído de `_semestreIngresso` (diferenciando
     *          os dados anteriores a 2025 e a partir de 2025 para Ciência da Computação, como previsto pela UFMG).
     */
    void configurarHorasPorCurriculo();

public:
    /**
     * @brief Construtor padrão da classe Curso.
     * @details Inicializa o objeto em estado não configurado (`_configurado = false`) com
     *          pseudovalores padrão correspondentes a Ciência da Computação (ingresso 2025/01).
     */
    Curso();

    /**
     * @brief Construtor parametrizado que inicializa e trava a configuração do curso.
     * @param opcaoCurso Código do curso (1 para Ciência da Computação, 2 para Sistemas de Informação).
     * @param semestreIngresso Identificador do semestre de ingresso (formato "AAAA/01" ou "AAAA/02").
     * @throws std::invalid_argument Se a opção de curso ou o formato do semestre forem inválidos.
     */
    Curso(int opcaoCurso, const std::string& semestreIngresso);

    /**
     * @brief Configura definitivamente o curso e atribui as cargas horárias do currículo.
     * @details Após a execução deste método com sucesso, o atributo `_configurado` passa a ser
     *          verdadeiro, bloqueando futuras chamadas aos métodos setters, já que essas informações são imutáveis.
     * @param opcao Código do curso (1 para CC, 2 para SI).
     * @param semIngresso Semestre de ingresso no formato "AAAA/01" ou "AAAA/02".
     * @throws std::invalid_argument Se o curso já estiver configurado ou se os parâmetros forem inválidos.
     */
    void inicializarCurso(int opcao, const std::string& semIngresso);

    /**
     * @brief Define a opção de curso antes da consolidação.
     * @param opcao Código do curso (1 para Ciência da Computação, 2 para Sistemas de Informação).
     * @throws std::invalid_argument Se o curso já tiver sido configurado ou se a opção for diferente de 1 e 2.
     */
    void setOpcaoCurso(int opcao);

    /**
     * @brief Define o semestre de ingresso antes da consolidação.
     * @param semIngresso Semestre de ingresso no formato "AAAA/01" ou "AAAA/02".
     * @throws std::invalid_argument Se o curso já tiver sido configurado ou se o formato do semestre for inválido.
     */
    void setSemestreIngresso(const std::string& semIngresso);

    /**
     * @brief Obtém o código numérico da opção de curso.
     * @return Inteiro representando a opção (1 ou 2).
     */
    int getOpcaoCurso() const;

    /**
     * @brief Obtém o nome do curso.
     * @return String com o nome do curso ("Ciencia da Computacao" ou "Sistemas de Informacao").
     */
    std::string getNome() const;

    /**
     * @brief Obtém o semestre de ingresso do estudante no curso.
     * @return String com o identificador do semestre de ingresso.
     */
    std::string getSemestreIngresso() const;

    /**
     * @brief Obtém o total de horas obrigatórias exigidas pelo curso.
     * @return Carga horária obrigatória total em horas.
     */
    int getHorasTotaisObrigatorias() const;

    /**
     * @brief Obtém o total de horas optativas exigidas pelo curso.
     * @return Carga horária optativa total em horas.
     */
    int getHorasTotaisOptativas() const;

    /**
     * @brief Obtém o total de horas de formação livre exigidas pelo curso.
     * @return Carga horária de formação livre total em horas.
     */
    int getHorasTotaisFormacaoLivre() const;

    /**
     * @brief Obtém o total de horas adicionais exigidas pelo currículo do curso.
     * @return Carga horária adicional em horas.
     */
    int getHorasAdicionais() const;

    /**
     * @brief Obtém a carga horária total exigida para a conclusão do curso.
     * @return Carga horária total do curso em horas.
     */
    int getHorasTotaisCurso() const;

    /**
     * @brief Serializa os dados do curso em uma linha de texto delimitada por '|'.
     * @return String no formato "CURSO|<opcaoCurso>|<semestreIngresso>".
     */
    std::string serializar() const;
};

#endif