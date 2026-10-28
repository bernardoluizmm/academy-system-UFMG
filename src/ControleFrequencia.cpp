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

void ControleFrequencia::setMaxFaltas(int novoMaxFaltas) 
{
    this->_maxFaltas = novoMaxFaltas;
    if (this->_faltasAtuais > this->_maxFaltas) 
    {
        this->_faltasAtuais = this->_maxFaltas;
    }
}

void ControleFrequencia::setFaltasAtuais(int novasFaltas) 
{
    if (novasFaltas < 0 || novasFaltas > this->_maxFaltas) 
    {
        throw std::invalid_argument("Faltas invalidas: nao podem ser menores que 0 nem ultrapassar o maximo de faltas.");
    }
    this->_faltasAtuais = novasFaltas;
}

