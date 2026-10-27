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

int Curso::getOpcaoCurso() const 
{ 
    return this->_opcaoCurso; 
}

std::string Curso::getNome() const 
{ 
    return this->_nome; 
}

std::string Curso::getSemestreIngresso() const 
{ 
    return this->_semestreIngresso; 
}

int Curso::getHorasTotaisObrigatorias() const 
{ 
    return this->_horasTotaisObrigatorias; 
}

int Curso::getHorasTotaisOptativas() const 
{ 
    return this->_horasTotaisOptativas; 
}

int Curso::getHorasTotaisFormacaoLivre() const 
{ 
    return this->_horasTotaisFormacaoLivre; 
}

int Curso::getHorasAdicionais() const 
{ 
    return this->_horasAdicionais; 
}

int Curso::getHorasTotaisCurso() const 
{ 
    return this->_horasTotaisCurso; 
}

void Curso::inicializarCurso(int opcao, const std::string& semIngresso) 
{
    this->setOpcaoCurso(opcao);
    this->setSemestreIngresso(semIngresso);
    this->configurarHorasPorCurriculo();
    this->_configurado = true;
}

