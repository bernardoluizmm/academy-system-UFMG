#ifndef SEMESTRECONSOLIDADO_HPP
#define SEMESTRECONSOLIDADO_HPP

#include "Semestre.hpp"

/**
 * @class SemestreConsolidado
 * @brief Representa um semestre já encerrado.
 *
 * Herda de Semestre. Diferente de SemestreAtual, o NSG (nota semestral
 * global) não é calculado a partir das disciplinas: é um valor fixo,
 * informado na construção e que pode ser alterado com setNSG().
 *
 * @see Semestre
 * @see SemestreAtual
 * @see Disciplina
 */
class SemestreConsolidado : public Semestre {
    private:
        /** @brief NSG armazenado do semestre consolidado. */
        double _nsg;

    public:
        /**
         * @brief Constrói um semestre consolidado com NSG já definido.
         *
         * @param periodo     Identificador do período letivo (ex.: "2025/2").
         * @param nsg         NSG final do semestre, guardado como está.
         * @param disciplinas Disciplinas cursadas no período (recebidas por
         *                    valor e armazenadas na classe base). Pode ser
         *                    um vetor vazio.
         */
        SemestreConsolidado(
            const std::string& periodo,
            double nsg,
            std::vector<Disciplina> disciplinas
        );

        /**
         * @brief Retorna o NSG armazenado.
         *
         * Não recalcula nada: devolve o valor informado no construtor ou o
         * último valor definido por setNSG().
         *
         * @return NSG do semestre.
         */
        double getNSG() const override;

        /**
         * @brief Altera o NSG armazenado.
         * @param nsg Novo valor do NSG.
         */
        void setNSG(double nsg);

        /**
         * @brief Calcula o total de horas do semestre.
         *
         * Soma a carga horária de todas as disciplinas do semestre.
         *
         * @return Soma das cargas horárias, ou 0 se não houver disciplinas.
         */
        int calcularTotalHoras() const;
};

#endif