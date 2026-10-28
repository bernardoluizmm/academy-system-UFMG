/**
 * @file AtividadeAvaliativa.hpp
 * @brief Declaração da classe AtividadeAvaliativa, que representa uma atividade com nota.
 */
#ifndef ATIVIDADEAVALIATIVA_HPP
#define ATIVIDADEAVALIATIVA_HPP

#include "Data.hpp"
#include <string>

/**
 * @class AtividadeAvaliativa
 * @brief Representa uma atividade avaliativa (prova, trabalho etc.) com data, valor e nota obtida.
 *
 * Uma atividade é considerada concluída quando uma nota é lançada nela.
 */
class AtividadeAvaliativa 
{
private:
    int _id;            ///< Identificador da atividade.
    std::string _nome;  ///< Nome da atividade (1 a 24 caracteres).
    Data _data;         ///< Data da atividade (DD/MM).
    float _valor;       ///< Valor máximo (pontuação total) da atividade; sempre maior que zero.
    float _notaObtida;  ///< Nota obtida; 0 enquanto a atividade não estiver concluída.
    bool _concluida;    ///< Indica se a nota já foi lançada.

public:
    /**
     * @brief Constrói uma atividade ainda não concluída (sem nota lançada).
     * @param id Identificador da atividade.
     * @param nome Nome da atividade (1 a 24 caracteres).
     * @param data Data da atividade no formato DD/MM.
     * @param valorMaximo Valor máximo da atividade (maior que zero).
     * @throws std::invalid_argument Se a data, o nome ou o valor máximo forem inválidos.
     */
    AtividadeAvaliativa(int id, const std::string& nome, const std::string& data, float valorMaximo);

    /**
     * @brief Constrói uma atividade com todos os dados, incluindo nota e estado de conclusão.
     *
     * Útil ao carregar atividades salvas. A nota só é aplicada se @p concluida for @c true;
     * caso contrário, a atividade começa sem nota.
     *
     * @param id Identificador da atividade.
     * @param nome Nome da atividade (1 a 24 caracteres).
     * @param data Data da atividade no formato DD/MM.
     * @param valorMaximo Valor máximo da atividade (maior que zero).
     * @param notaObtida Nota obtida (usada apenas se @p concluida for @c true).
     * @param concluida Indica se a atividade já foi concluída.
     * @throws std::invalid_argument Se a data, o nome, o valor máximo ou a nota forem inválidos.
     */
    AtividadeAvaliativa(int id, const std::string& nome, const std::string& data, float valorMaximo, float notaObtida, bool concluida);

    /**
     * @brief Obtém o identificador da atividade.
     * @return Identificador da atividade.
     */
    int getId() const;

    /**
     * @brief Obtém o nome da atividade.
     * @return Nome da atividade.
     */
    std::string getNome() const;

    /**
     * @brief Obtém a data da atividade.
     * @return Referência constante para a Data da atividade.
     */
    const Data& getData() const;

    /**
     * @brief Obtém o valor máximo da atividade.
     * @return Valor máximo.
     */
    float getValorMaximo() const;

    /**
     * @brief Obtém a nota obtida na atividade.
     * @return Nota obtida (0 se a atividade não estiver concluída).
     */
    float getNotaObtida() const;

    /**
     * @brief Informa se a atividade já foi concluída.
     * @return @c true se a nota já foi lançada; @c false caso contrário.
     */
    bool isConcluida() const;

    /**
     * @brief Altera o nome da atividade.
     * @param novoNome Novo nome (1 a 24 caracteres).
     * @throws std::invalid_argument Se o nome estiver vazio ou tiver mais de 24 caracteres.
     */
    void setNome(const std::string& novoNome);

    /**
     * @brief Altera a data da atividade.
     * @param novaData Nova data no formato DD/MM.
     * @throws std::invalid_argument Se a data for inválida.
     */
    void setData(const std::string& novaData);

    /**
     * @brief Altera o valor máximo da atividade.
     * @param novoValor Novo valor máximo (maior que zero).
     * @throws std::invalid_argument Se @p novoValor não for maior que zero ou se a atividade
     *         estiver concluída e a nota obtida for maior que @p novoValor.
     */
    void setValorMaximo(float novoValor);

    /**
     * @brief Lança a nota obtida e marca a atividade como concluída.
     * @param novaNota Nota obtida (de 0 até o valor máximo da atividade).
     * @throws std::invalid_argument Se a nota for negativa ou maior que o valor máximo.
     */
    void setNotaObtida(float novaNota);

    /**
     * @brief Remove a nota lançada: zera a nota e marca a atividade como não concluída.
     */
    void removerLancamentoNota();

    /**
     * @brief Calcula a média da atividade (60% do valor máximo).
     * @return Média da atividade, independentemente de ela estar concluída.
     * @see CalculadorMedia::calcular
     */
    float obterMedia() const;

    /**
     * @brief Obtém o conceito da atividade, a partir do percentual da nota em relação ao valor máximo.
     * @return Conceito ('A' a 'F'), ou '-' se a atividade ainda não estiver concluída.
     * @see CalculadorConceito::calcular
     */
    char obterConceito() const;

    /**
     * @brief Serializa a atividade em uma linha de texto, para persistência em arquivo.
     *
     * Formato: @c ATIVIDADE|id|nome|data|valor|notaObtida|concluida,
     * onde @c concluida é 1 ou 0.
     *
     * @return String com os dados da atividade.
     */
    std::string serializar() const;
};

#endif