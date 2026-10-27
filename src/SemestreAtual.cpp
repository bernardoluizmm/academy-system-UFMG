#include "SemestreAtual.hpp"
#include <stdexcept>
#include <sstream>

SemestreAtual::SemestreAtual() : Semestre("2026/01", false), _contadorId(1) {}

SemestreAtual::SemestreAtual(const std::string& identificador) : Semestre(identificador, false), _contadorId(1) {}

SemestreAtual::~SemestreAtual() 
{
    this->_disciplinas.clear();
}
