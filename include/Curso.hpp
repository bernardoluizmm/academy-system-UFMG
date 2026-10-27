#ifndef CURSO_HPP
#define CURSO_HPP

#include <string>

class Curso 
{
private:
    int _opcaoCurso;
    std::string _nome;
    std::string _semestreIngresso;
    int _horasTotaisObrigatorias;
    int _horasTotaisOptativas;
    int _horasTotaisFormacaoLivre;
    int _horasAdicionais;
    int _horasTotaisCurso;
    bool _configurado;

    void configurarHorasPorCurriculo();

public:
    Curso();
    Curso(int opcaoCurso, const std::string& semestreIngresso);

    void inicializarCurso(int opcao, const std::string& semIngresso);

    void setOpcaoCurso(int opcao);
    void setSemestreIngresso(const std::string& semIngresso);

    int getOpcaoCurso() const;
    std::string getNome() const;
    std::string getSemestreIngresso() const;
    int getHorasTotaisObrigatorias() const;
    int getHorasTotaisOptativas() const;
    int getHorasTotaisFormacaoLivre() const;
    int getHorasAdicionais() const;
    int getHorasTotaisCurso() const;

    std::string serializar() const;
};

#endif
