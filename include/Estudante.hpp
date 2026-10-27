#ifndef ESTUDANTE_HPP
#define ESTUDANTE_HPP

#include <string>
#include "Curso.hpp"
#include "HistoricoEscolar.hpp"

class Estudante 
{
private:
    std::string _nome;
    Curso _curso;
    HistoricoEscolar _historico;

public:
    Estudante();
    Estudante(const std::string& nome, const Curso& curso, const HistoricoEscolar& historico);

    std::string getNome() const;
    void setNome(const std::string& novoNome);

    const Curso& getCurso() const;
    Curso& getCursoEditavel();
    void setCurso(const Curso& novoCurso);

    const HistoricoEscolar& getHistorico() const;
    HistoricoEscolar& getHistoricoEditavel();

    float calcularPercentualCursoCompleto() const;
    float calcularPercentualObrigatorias() const;
    float calcularPercentualOptativas() const;
    float calcularPercentualFormacaoLivre() const;

    std::string serializar() const;
};

#endif