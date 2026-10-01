/**
 * @file AtividadeAvaliativa.hpp
 * @brief Declaração da classe AtividadeAvaliativa.
 */
#ifndef ATIVIDADE_AVALIATIVA_HPP
#define ATIVIDADE_AVALIATIVA_HPP

#include <string>

/**
 * @class AtividadeAvaliativa
 * @brief Representa uma avaliação individual de uma disciplina (ex: prova, trabalho).
 */
class AtividadeAvaliativa {
private:
    /** @brief Descrição ou título da atividade. */
    std::string _nome;

    /** @brief Data prevista de entrega ou aplicação (formato DD/MM/AAAA). */
    std::string _dataEntrega;

    /** @brief Pontuação máxima que a atividade distribui. */
    double _valorMaximo;

    /** @brief Nota obtida pelo estudante (inicialmente 0.0). */
    double _notaObtida;

public:
    /**
     * @brief Construtor de AtividadeAvaliativa.
     * @param nome Nome ou descrição da atividade.
     * @param dataEntrega Data limite para entrega/realização.
     * @param valorMaximo Pontuação total distribuída pela avaliação.
     */
    AtividadeAvaliativa(const std::string& nome, const std::string& dataEntrega, double valorMaximo);

    /**
     * @brief Retorna o nome da atividade avaliativa.
     * @return Nome da atividade.
     */
    std::string getNome() const;

    /**
     * @brief Retorna a data de realização ou entrega da atividade.
     * @return Data no formato texto.
     */
    std::string getDataEntrega() const;

    /**
     * @brief Retorna a pontuação máxima possível da atividade.
     * @return Valor máximo da atividade.
     */
    double getValorMaximo() const;

    /**
     * @brief Retorna a pontuação obtida pelo estudante.
     * @return Nota obtida.
     */
    double getNotaObtida() const;

    /**
     * @brief Calcula o aproveitamento percentual obtido na atividade.
     * @return Aproveitamento em porcentagem (ex: 85.0 para 85%).
     */
    double calcularAproveitamento() const;

    /**
     * @brief Registra ou atualiza a nota obtida na atividade.
     * @param nota Nota tirada pelo aluno (deve ser entre 0 e valorMaximo).
     * @return true se a nota for válida e registrada; false caso contrário.
     */
    bool registrarNota(double nota);
};

#endif // ATIVIDADE_AVALIATIVA_HPP