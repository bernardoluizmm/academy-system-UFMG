#include "ControleFrequencia.hpp"
#include <stdexcept>

ControleFrequencia::ControleFrequencia(int maxFaltas)
    : _maxFaltas(maxFaltas),
      _faltasAtuais(0) {}

int ControleFrequencia::getMaxFaltas() const 
{ 
    return this->_maxFaltas; 
}

int ControleFrequencia::getFaltasAtuais() const 
{ 
    return this->_faltasAtuais; 
}

