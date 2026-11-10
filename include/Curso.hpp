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

    static constexpr int OPCAO_CC = 1;        
    static constexpr int OPCAO_SI = 2;                  
    static constexpr int ANO_REFORMA_CC = 2025;         

    static constexpr int HORAS_OBRIG_CC_ANTIGO = 2040;  
    static constexpr int HORAS_OPT_CC_ANTIGO = 1020;    
    static constexpr int HORAS_LIVRE_CC_ANTIGO = 60;    
    static constexpr int HORAS_ADIC_CC_ANTIGO = 120;    
    static constexpr int HORAS_TOTAIS_CC_ANTIGO = 3240; 

    static constexpr int HORAS_OBRIG_CC_NOVO = 1980;    
    static constexpr int HORAS_OPT_CC_NOVO = 1110;      
    static constexpr int HORAS_LIVRE_CC_NOVO = 120;     
    static constexpr int HORAS_ADIC_CC_NOVO = 0;        
    static constexpr int HORAS_TOTAIS_CC_NOVO = 3210;   

    static constexpr int HORAS_OBRIG_SI = 2100;         
    static constexpr int HORAS_OPT_SI = 780;            
    static constexpr int HORAS_LIVRE_SI = 120;          
    static constexpr int HORAS_ADIC_SI = 0;             
    static constexpr int HORAS_TOTAIS_SI = 3000; 

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
     * @brief Construtor parametrizado que inicializa e trava a configuração do curso.
     * @param opcaoCurso Código do curso (1 para Ciência da Computação, 2 para Sistemas de Informação).
     * @param semestreIngresso Identificador do semestre de ingresso (formato "AAAA/01" ou "AAAA/02").
     * @throws std::invalid_argument Se a opção de curso ou o formato do semestre forem inválidos.
     */
    Curso(int opcaoCurso, const std::string& semestreIngresso);

    static void validarOpcaoCurso(int opcao);

    static void validarSemestreIngresso(const std::string& semIngresso);
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