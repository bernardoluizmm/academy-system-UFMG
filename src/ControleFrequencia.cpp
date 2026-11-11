#include "ControleFrequencia.hpp"
#include <stdexcept>

ControleFrequencia::ControleFrequencia(int maxFaltas)
    : _maxFaltas(maxFaltas),
      _faltasAtuais(0) 
      {
        if (maxFaltas < 0)
        {
            throw std::invalid_argument("O maximo de faltas nao pode ser negativo.");
        }
      }

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
    if (novoMaxFaltas < 0)
    {
        throw std::invalid_argument("O maximo de faltas nao pode ser negativo.");
    }

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

void ControleFrequencia::adicionarFalta() 
{
    if (this->_faltasAtuais >= this->_maxFaltas) 
    {
        throw std::invalid_argument("Nao e possivel adicionar mais uma falta. Voce ja atingiu o maximo permitido.");
    }
    this->_faltasAtuais++;
}

void ControleFrequencia::removerFalta() 
{
    if (this->_faltasAtuais <= 0) 
    {
        throw std::invalid_argument("Nao e possivel remover uma falta.");
    }
    this->_faltasAtuais--;
}