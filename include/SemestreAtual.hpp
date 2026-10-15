#ifndef SEMESTREATUAL_HPP
#define SEMESTREATUAL_HPP
#include "Semestre.hpp"

class SemestreAtual:public Semestre {
    public:
        SemestreAtual(std::string periodo);
        double getNSG() const override;
        void adicionarDisciplina(const Disciplina& disciplina);
        bool removerDisciplina(int indice);
        const std::vector<Disciplina>& getDisciplinas() const;
};
#endif