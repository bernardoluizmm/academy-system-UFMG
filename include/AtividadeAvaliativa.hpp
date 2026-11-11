/**
 * @file AtividadeAvaliativa.hpp
 * @brief Declaracao da classe AtividadeAvaliativa, que representa uma atividade com nota.
 */
#ifndef ATIVIDADEAVALIATIVA_HPP
#define ATIVIDADEAVALIATIVA_HPP

#include "Data.hpp"
#include <string>

/**
 * @class AtividadeAvaliativa
 * @brief Representa uma atividade avaliativa (prova, trabalho etc.) com data, valor e nota obtida.
 *
 * Uma atividade e considerada concluida quando uma nota e lancada nela.
 */
class AtividadeAvaliativa 
{
private:
    int _id;            ///< Identificador da atividade.
    std::string _nome;  ///< Nome da atividade (1 a 24 caracteres).
    Data _data;         ///< Data da atividade (DD/MM).
    float _valor;       ///< Valor maximo (pontuacao total) da atividade; sempre maior que zero.
    float _notaObtida;  ///< Nota obtida; 0 enquanto a atividade nao estiver concluida.
    bool _concluida;    ///< Indica se a nota ja foi lancada.

public:
    /**
     * @brief Valida se o nome da atividade respeita os limites de tamanho (1 a 24 caracteres).
     * @param nome Nome a ser validado.
     * @throws std::invalid_argument Se o nome for vazio ou tiver mais de 24 caracteres.
     */
    static void validarNome(const std::string& nome);

    /**
     * @brief Valida se o valor maximo da atividade e estritamente positivo.
     * @param valor Valor maximo a ser validado.
     * @throws std::invalid_argument Se o valor for menor ou igual a zero.
     */
    static void validarValorMaximo(float valor);

    /**
     * @brief Constroi uma atividade ainda nao concluida (sem nota lancada).
     * @param id Identificador da atividade.
     * @param nome Nome da atividade (1 a 24 caracteres).
     * @param data Data da atividade no formato DD/MM.
     * @param valorMaximo Valor maximo da atividade (maior que zero).
     * @throws std::invalid_argument Se a data, o nome ou o valor maximo forem invalidos.
     */
    AtividadeAvaliativa(int id, const std::string& nome, const std::string& data, float valorMaximo);

    /**
     * @brief Constroi uma atividade com todos os dados, incluindo nota e estado de conclusao.
     *
     * Util ao carregar atividades salvas. A nota so e aplicada se @p concluida for @c true;
     * caso contrario, a atividade comeca sem nota.
     *
     * @param id Identificador da atividade.
     * @param nome Nome da atividade (1 a 24 caracteres).
     * @param data Data da atividade no formato DD/MM.
     * @param valorMaximo Valor maximo da atividade (maior que zero).
     * @param notaObtida Nota obtida (usada apenas se @p concluida for @c true).
     * @param concluida Indica se a atividade ja foi concluida.
     * @throws std::invalid_argument Se a data, o nome, o valor maximo ou a nota forem invalidos.
     */
    AtividadeAvaliativa(int id, const std::string& nome, const std::string& data, float valorMaximo, float notaObtida, bool concluida);

    /**
     * @brief Obtem o identificador da atividade.
     * @return Identificador da atividade.
     */
    int getId() const;

    /**
     * @brief Obtem o nome da atividade.
     * @return Nome da atividade.
     */
    std::string getNome() const;

    /**
     * @brief Obtem a data da atividade.
     * @return Referencia constante para a Data da atividade.
     */
    const Data& getData() const;

    /**
     * @brief Obtem o valor maximo da atividade.
     * @return Valor maximo.
     */
    float getValorMaximo() const;

    /**
     * @brief Obtem a nota obtida na atividade.
     * @return Nota obtida (0 se a atividade nao estiver concluida).
     */
    float getNotaObtida() const;

    /**
     * @brief Informa se a atividade ja foi concluida.
     * @return @c true se a nota ja foi lancada; @c false caso contrario.
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
     * @throws std::invalid_argument Se a data for invalida.
     */
    void setData(const std::string& novaData);

    /**
     * @brief Altera o valor maximo da atividade.
     * @param novoValor Novo valor maximo (maior que zero).
     * @throws std::invalid_argument Se @p novoValor nao for maior que zero ou se a atividade
     *         estiver concluida e a nota obtida for maior que @p novoValor.
     */
    void setValorMaximo(float novoValor);

    /**
     * @brief Lanca a nota obtida e marca a atividade como concluida.
     * @param novaNota Nota obtida (de 0 ate o valor maximo da atividade).
     * @throws std::invalid_argument Se a nota for negativa ou maior que o valor maximo.
     */
    void setNotaObtida(float novaNota);

    /**
     * @brief Remove a nota lancada: zera a nota e marca a atividade como nao concluida.
     */
    void removerLancamentoNota();

    /**
     * @brief Calcula a media da atividade (60% do valor maximo).
     * @return Media da atividade, independentemente de ela estar concluida.
     * @see CalculadorMedia::calcular
     */
    float obterMedia() const;

    /**
     * @brief Obtem o conceito da atividade, a partir do percentual da nota em relacao ao valor maximo.
     * @return Conceito ('A' a 'F'), ou '-' se a atividade ainda nao estiver concluida.
     * @see CalculadorConceito::calcular
     */
    char obterConceito() const;

    /**
     * @brief Serializa a atividade em uma linha de texto, para persistencia em arquivo.
     *
     * Formato: @c ATIVIDADE|id|nome|data|valor|notaObtida|concluida,
     * onde @c concluida e 1 ou 0.
     *
     * @return String com os dados da atividade.
     */
    std::string serializar() const;
};

#endif