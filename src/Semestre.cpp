#include "Semestre.hpp"
#include <stdexcept>
#include <cctype>
#include <sstream>

Semestre::Semestre(const std::string& identificador, bool trancado)
    : _identificador(identificador), _trancado(trancado) 
{
    if (!validarFormatoIdentificador(_identificador)) {
        throw std::invalid_argument(
            "Identificador de semestre invalido."
        );
    }
}

const std::string& Semestre::getIdentificador() const 
{
    return _identificador;
}

bool Semestre::isTrancado() const 
{
    return this->_trancado;
}

void Semestre::setTrancado(bool estado) 
{
    this->_trancado = estado;
}