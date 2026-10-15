#ifndef SEMESTREATUAL_HPP
#define SEMESTREATUAL_HPP

#include "Semestre.hpp"

/**
 * @class SemestreAtual
 * @brief Representa o semestre em andamento.
 *
 * Herda de Semestre. Mantém a lista de disciplinas cursadas no período e
 * calcula o NSG (nota semestral global) a partir das notas lançadas nas
 * atividades avaliativas de cada disciplina.
 *
 * @see Semestre
 * @see Disciplina
 */
class SemestreAtual : public Semestre {
    public:
        /**
         * @brief Constrói um semestre atual sem disciplinas.
         * @param periodo Identificador do período letivo (ex.: "2026/1").
         */
        SemestreAtual(std::string periodo);

        /**
         * @brief Calcula o NSG do semestre.
         *
         * O valor é a média das notas das disciplinas ponderada pela carga
         * horária de cada uma. Se não houver disciplinas, retorna 0.0.
         *
         * @return NSG calculado a partir das disciplinas atuais.
         */
        double getNSG() const override;

        /**
         * @brief Adiciona uma disciplina ao semestre.
         * @param disciplina Disciplina a ser adicionada (armazenada por cópia).
         */
        void adicionarDisciplina(const Disciplina& disciplina);

        /**
         * @brief Remove a disciplina que está na posição indicada.
         *
         * As disciplinas seguintes deslocam uma posição para trás.
         *
         * @param indice Posição da disciplina na lista, começando em 0.
         * @return true se a disciplina foi removida; false se o índice for
         *         inválido (negativo ou maior ou igual ao número de disciplinas).
         */
        bool removerDisciplina(int indice);

        /**
         * @brief Retorna as disciplinas do semestre.
         * @return Referência constante para o vetor de disciplinas, na ordem
         *         em que foram adicionadas.
         */
        const std::vector<Disciplina>& getDisciplinas() const;
};

#endif