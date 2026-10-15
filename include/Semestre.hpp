#ifndef SEMESTRE_HPP
#define SEMESTRE_HPP
#include <string>
#include <vector>
#include "Disciplina.hpp"

class Semestre {
    protected:
        std::string _periodo;
        std::vector<Disciplina> _disciplinas;

    public:
        Semestre(std::string periodo);
        std::string getPeriodo() const;
        const std::vector<Disciplina>& getDisciplinas() const;
        virtual double getNSG() const = 0;
        virtual ~Semestre() = default;
};
#endif