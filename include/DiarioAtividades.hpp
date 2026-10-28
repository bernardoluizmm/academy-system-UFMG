/**
 * @file DiarioAtividades.hpp
 * @brief Declaração da classe DiarioAtividades, que gerencia as atividades avaliativas de uma disciplina.
 */
#ifndef DIARIOATIVIDADES_HPP
#define DIARIOATIVIDADES_HPP

#include "AtividadeAvaliativa.hpp"
#include <vector>
#include <string>

/**
 * @class DiarioAtividades
 * @brief Gerencia as atividades avaliativas de uma disciplina e calcula totais, média e conceito parciais.
 *
 * As atividades são mantidas ordenadas da data mais antiga para a mais recente.
 * Os cálculos "parciais" consideram apenas as atividades já concluídas.
 */
class DiarioAtividades 
{
private:
    std::vector<AtividadeAvaliativa> _atividades; ///< Atividades cadastradas, ordenadas por data.
    int _contadorId;                              ///< Próximo identificador a ser atribuído a uma nova atividade.

    /**
     * @brief Critério de comparação usado na ordenação das atividades.
     * @param a Primeira atividade.
     * @param b Segunda atividade.
     * @return @c true se a data de @p a for anterior à data de @p b.
     */
    static bool compararDataMaisAntiga(const AtividadeAvaliativa& a, const AtividadeAvaliativa& b);

public:
    /**
     * @brief Cria um diário vazio, com o contador de identificadores em zero.
     */
    DiarioAtividades();

    /**
     * @brief Adiciona uma nova atividade, ainda sem nota.
     *
     * O identificador é gerado automaticamente a partir do contador interno,
     * e a lista é reordenada por data após a inserção.
     *
     * @param nome Nome da atividade (1 a 24 caracteres).
     * @param dataInput Data da atividade no formato DD/MM.
     * @param valorMaximo Valor máximo da atividade (maior que zero).
     * @throws std::invalid_argument Se algum dado da atividade for inválido.
     */
    void adicionarAtividade(const std::string& nome, const std::string& dataInput, float valorMaximo);

    /**
     * @brief Adiciona uma atividade com todos os dados informados (por exemplo, ao carregar de arquivo).
     *
     * O contador interno é atualizado para ficar acima de @p id, quando necessário,
     * e a lista é reordenada por data após a inserção.
     *
     * @param id Identificador da atividade.
     * @param nome Nome da atividade (1 a 24 caracteres).
     * @param dataInput Data da atividade no formato DD/MM.
     * @param valorMaximo Valor máximo da atividade (maior que zero).
     * @param notaObtida Nota obtida (considerada apenas se @p concluida for @c true).
     * @param concluida Indica se a atividade já foi concluída.
     * @throws std::invalid_argument Se algum dado da atividade for inválido.
     */
    void adicionarAtividade(int id, const std::string& nome, const std::string& dataInput, float valorMaximo, float notaObtida, bool concluida);

    /**
     * @brief Remove uma atividade do diário.
     * @param idAtividade Identificador da atividade a ser removida.
     * @throws std::invalid_argument Se não existir atividade com o identificador informado.
     */
    void removerAtividade(int idAtividade);

    /**
     * @brief Busca uma atividade pelo identificador.
     * @param idAtividade Identificador da atividade procurada.
     * @return Ponteiro para a atividade encontrada, ou @c nullptr se não existir.
     * @warning O ponteiro pode ser invalidado se atividades forem adicionadas ou removidas.
     */
    AtividadeAvaliativa* buscarAtividade(int idAtividade);

    /**
     * @brief Ordena as atividades da data mais antiga para a mais recente.
     */
    void ordenarAtividades();

    /**
     * @brief Obtém as atividades cadastradas.
     * @return Referência constante para o vetor de atividades, ordenado por data.
     */
    const std::vector<AtividadeAvaliativa>& getAtividades() const;

    /**
     * @brief Calcula a soma dos valores máximos de todas as atividades.
     * @return Valor total planejado.
     */
    float obterValorTotalPlanejado() const;

    /**
     * @brief Calcula a soma dos valores máximos das atividades já concluídas.
     * @return Valor total concluído.
     */
    float obterValorTotalConcluido() const;

    /**
     * @brief Calcula a soma das notas obtidas nas atividades concluídas.
     * @return Nota total parcial.
     */
    float obterNotaTotalParcial() const;

    /**
     * @brief Calcula a média parcial (60% do valor total das atividades concluídas).
     * @return Média parcial.
     * @see CalculadorMedia::calcular
     */
    float obterMediaParcial() const;

    /**
     * @brief Calcula o percentual de aproveitamento nas atividades concluídas.
     *
     * É a nota total parcial dividida pelo valor total concluído, multiplicada por 100.
     *
     * @return Percentual de aproveitamento, ou 0 se nenhuma atividade tiver sido concluída.
     */
    float calcularPercentualAproveitamento() const;

    /**
     * @brief Obtém o conceito parcial com base no percentual de aproveitamento.
     * @return Conceito ('A' a 'F'), ou '-' se nenhuma atividade tiver sido concluída.
     * @see CalculadorConceito::calcular
     */
    char obterConceitoParcial() const;
};

#endif