/**
 * @file Semestre.hpp
 * @brief Declaração da classe base abstrata Semestre.
 */
#ifndef SEMESTRE_HPP
#define SEMESTRE_HPP

#include <string>
#include <vector>

/**
 * @class Semestre
 * @brief Classe base abstrata que representa um semestre letivo.
 *
 * Guarda o identificador (formato AAAA/01 ou AAAA/02) e o estado de trancamento,
 * e define o contrato de calculo de NSG e de horas integralizadas que as classes
 * derivadas (SemestreAtual e SemestreConsolidado) devem implementar.
 * Tambem reune utilitarios estaticos de validacao e manipulacao de identificadores.
 */
class Semestre 
{
private:
    std::string _identificador; 
    bool _trancado;             

public:
    /**
     * @brief Constroi um semestre validando o identificador.
     * @param identificador Identificador do semestre (AAAA/01 ou AAAA/02, ano entre 2016 e 2100).
     * @param trancado Indica se o semestre esta trancado (padrao: false).
     * @throws std::invalid_argument Se o identificador nao respeitar o formato esperado.
     * @see validarFormatoIdentificador
     */
    Semestre(const std::string& identificador, bool trancado = false);

    /** @brief Destrutor virtual. */
    virtual ~Semestre() = default;

    /**
     * @brief Obtém o identificador do semestre.
     * @return Referência constante ao identificador.
     */
    const std::string& getIdentificador() const;

    /**
     * @brief Informa se o semestre foi trancado.
     * @return @c true se o semestre esta trancado; @c false caso contrario.
     */
    bool isTrancado() const;

    /**
     * @brief Define o estado de trancamento.
     * @param estado Novo estado (@c true para trancado).
     */
    void setTrancado(bool estado);

    /**
     * @brief Calcula o NSG (Nota do Semestre Global) do semestre.
     * @return NSG entre 0 e 100.
     */
    virtual float calcularNSG() const = 0;

    /**
     * @brief Obtém o total de horas integralizadas.
     * @return Soma das horas obrigatórias, optativas e de formação livre.
     */
    virtual int getHorasIntegralizadas() const = 0;

    /** @brief Obtém as horas integralizadas em disciplinas obrigatórias. */
    virtual int getHorasObrigatorias() const = 0;

    /** @brief Obtém as horas integralizadas em disciplinas optativas. */
    virtual int getHorasOptativas() const = 0;

    /** @brief Obtém as horas integralizadas em formação livre. */
    virtual int getHorasFormacaoLivre() const = 0;

   /**
     * @brief Calcula o identificador do semestre seguinte.
     * @param idAtual Identificador atual (ex.: "2026/02").
     * @return Identificador seguinte (ex.: "2027/01").
     */
    static std::string proximoIdentificadorSemestre(const std::string& idAtual);

    /**
     * @brief Extrai o ano de um identificador.
     * @param idStr Identificador no formato AAAA/PP.
     * @return Ano como inteiro.
     */
    static int extrairAno(const std::string& idStr);

    /**
     * @brief Extrai o período de um identificador.
     * @param idStr Identificador no formato AAAA/PP.
     * @return Período (1 ou 2).
     */
    static int extrairPeriodo(const std::string& idStr);


    /**
     * @brief Valida o formato de um identificador de semestre.
     * @param idStr Identificador a validar.
     * @return true se válido (AAAA/01 ou AAAA/02, ano entre 2016 e 2100).
     */
    static bool validarFormatoIdentificador(const std::string& idStr);

    /**
     * @brief Valida um valor de NSG.
     * @param nsg Valor a validar.
     * @throws std::invalid_argument Se estiver fora do intervalo [0, 100].
     */
    static void validarNSG(float nsg);

    /**
     * @brief Valida uma carga horária.
     * @param horas Valor em horas.
     * @throws std::invalid_argument Se for negativa ou não divisível por 15.
     */
    static void validarHoras(int horas);

    /**
     * @brief Valida o intervalo entre semestre de ingresso e semestre atual.
     * @param semIngresso Semestre de ingresso.
     * @param semAtual Semestre atual.
     * @throws std::invalid_argument Se algum formato for inválido, se o atual
     *         for anterior ao ingresso ou se a diferença passar de 9 anos.
     */
    static void validarIntervaloSemestres(const std::string& semIngresso, const std::string& semAtual);

    /**
     * @brief Gera a lista de semestres entre o ingresso e o atual (exclusivo).
     * @param semIngresso Semestre de ingresso.
     * @param semAtual Semestre atual (não incluído na lista).
     * @return Vetor com os identificadores dos semestres anteriores.
     * @throws std::invalid_argument Conforme validarIntervaloSemestres().
     */
    static std::vector<std::string> gerarSemestresAnteriores(const std::string& semIngresso, const std::string& semAtual);
};

#endif
