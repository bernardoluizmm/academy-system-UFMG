#include "Curso.hpp"
#include "Semestre.hpp"

Curso::Curso() 
    : _opcaoCurso(1),
      _nome("Ciencia da Computacao"),
      _semestreIngresso("2025/01"),
      _horasTotaisObrigatorias(1980),
      _horasTotaisOptativas(1110),
      _horasTotaisFormacaoLivre(120),
      _horasAdicionais(0),
      _horasTotaisCurso(3210),
      _configurado(false)
{}

Curso::Curso(int opcaoCurso, const std::string& semestreIngresso) 
    : _opcaoCurso(1),
      _nome("Ciencia da Computacao"),
      _semestreIngresso("2025/01"),
      _horasTotaisObrigatorias(1980),
      _horasTotaisOptativas(1110),
      _horasTotaisFormacaoLivre(120),
      _horasAdicionais(0),
      _horasTotaisCurso(3210),
      _configurado(false)
{
    this->inicializarCurso(opcaoCurso, semestreIngresso);
}