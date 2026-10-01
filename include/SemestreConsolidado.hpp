#ifndef SEMESTRECONSOLIDADO_HPP
#define SEMESTRECONSOLIDADO_HPP
#include "Semestre.hpp"

class SemestreConsolidado:public Semestre {
    private:
        double _nsg;

    public:
        SemestreConsolidado(
            const std::string& periodo, 
            double nsg, 
            std::vector<Disciplina> disciplinas
        );
        double getNSG() const override;
        void setNSG(double nsg);
        int calcularTotalHoras()const;
};
#endif