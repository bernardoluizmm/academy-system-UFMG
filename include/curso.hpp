/**
 * @file Curso.hpp
 * @brief Declaração da classe Curso
 *
 * Depende de: SemestreConsolidado, CategoriaDisciplina, PontoGrafico.
 */
#ifndef CURSO_HPP
#define CURSO_HPP

#include <string>
#include <vector>
 
#include "SemestreConsolidado.hpp"
#include "CategoriaDisciplina.hpp"
#include "PontoGrafico.hpp"

/**
 * @class Curso
 * @brief Representa o curso do estudante.
 *
 * Armazena os limites curriculares de horas (obrigatórias, optativas e
 * formação livre) e o histórico de semestres consolidados.
 */

class Curso 
{
   /** @brief Nome do curso (ex: "Ciência da Computação"). */
   std::string _nome;
 
    /** @brief Horas exigidas em disciplinas obrigatórias. */
    int _horasObrigatorias;
 
    /** @brief Horas exigidas em disciplinas optativas. */
    int _horasOptativas;
 
    /** @brief Horas exigidas em formação livre. */
    int _horasFormacaoLivre;
 
    /** @brief Lista ordenada de semestres consolidados. */
    std::vector<SemestreConsolidado> _semestresConsolidados;

    public:
    /**
     * @brief Construtor do curso.
     *
     * A lista de semestres consolidados começa vazia.
     *
     * @param nome Nome do curso.
     * @param horasObrigatorias Horas exigidas em obrigatórias.
     * @param horasOptativas Horas exigidas em optativas.
     * @param horasFormacaoLivre Horas exigidas em formação livre.
     */
    Curso(std::string nome, int horasObrigatorias, int horasOptativas, int horasFormacaoLivre);
    /**
     * @brief Retorna o nome do curso.
     * @return Nome do curso.
     */
    std::string getNome() const;
 
    /**
     * @brief Altera o nome do curso.
     * @param nome Novo nome.
     */
    void setNome(const std::string& nome);
 
    /**
     * @brief Retorna as horas exigidas em disciplinas obrigatórias.
     * @return Horas obrigatórias exigidas.
     */
    int getHorasObrigatorias() const;
 
    /**
     * @brief Retorna as horas exigidas em disciplinas optativas.
     * @return Horas optativas exigidas.
     */
    int getHorasOptativas() const;
 
    /**
     * @brief Retorna as horas exigidas em formação livre.
     * @return Horas de formação livre exigidas.
     */
    int getHorasFormacaoLivre() const;
 
    /**
     * @brief Altera as horas exigidas em formação livre.
     * @param horas Nova quantidade de horas.
     */
    void setHorasFormacaoLivre(int horas);
 
    /**
     * @brief Retorna o total de horas exigidas pelo curso.
     * @return horasObrigatorias_ + horasOptativas_ + horasFormacaoLivre_.
     */
    int getTotalHorasExigidas() const;
 
    /**
     * @brief Adiciona um semestre consolidado à lista.
     * @param sem Semestre consolidado a ser adicionado.
     */
    void adicionarSemestreConsolidado(SemestreConsolidado sem);
 
    /**
     * @brief Remove o semestre consolidado no índice informado.
     * @param indice Posição do semestre na lista.
     * @return true se removido com sucesso; false se o índice for inválido.
     */
    bool removerSemestreConsolidado(int indice);
 
    /**
     * @brief Acesso somente leitura à lista de semestres consolidados.
     * @return Referência constante ao vetor de semestres.
     */
    const std::vector<SemestreConsolidado>& getSemestresConsolidados() const;
 
    /**
     * @brief Acesso mutável à lista de semestres consolidados.
     *
     * Usado, por exemplo, para edição do NSG de um semestre.
     *
     * @return Referência ao vetor de semestres.
     */
    std::vector<SemestreConsolidado> &getSemestresConsolidados();
 
    /**
     * @brief Calcula o percentual de integralização do curso.
     * @return (total de horas cursadas / getTotalHorasExigidas()) * 100.
     */
    double calcularPercentualIntegralizacao() const;
 
    /**
     * @brief Calcula o percentual de integralização de uma categoria.
     * @param categoria Categoria curricular a ser avaliada.
     * @return (horas cursadas na categoria / horas exigidas da categoria) * 100,
     *         limitado ao máximo de 100.0.
     */
    double calcularPercentualCategoria(CategoriaDisciplina categoria) const;
 
    /**
     * @brief Gera os dados para o gráfico de evolução do NSG.
     *
     * Retorna pares (período, NSG) de cada semestre consolidado, filtrando
     * os semestres com NSG == 0.
     *
     * @return Vetor de PontoGrafico; vazio se não houver semestres consolidados.
     */
    std::vector<PontoGrafico> gerarDadosGrafico() const;
};
 
#endif // CURSO_HPP
    