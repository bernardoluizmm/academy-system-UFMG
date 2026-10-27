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

bool Semestre::validarFormatoIdentificador(const std::string& idStr) 
{
    if (idStr.length() != 7 || idStr[4] != '/') 
    {
        return false;
    }
    for (int i = 0; i < 4; ++i) 
    {
        if (!std::isdigit(static_cast<unsigned char>(idStr[i]))) 
        {
            return false;
        }
    }
    std::string periodo = idStr.substr(5, 2);
    if (periodo != "01" && periodo != "02") 
    {
        return false;
    }
    int ano = Semestre::extrairAno(idStr);
    return (ano >= 2016 && ano <= 2100);
}

int Semestre::extrairAno(const std::string& idStr) 
{
    return (idStr[0] - '0') * 1000 +
           (idStr[1] - '0') * 100 +
           (idStr[2] - '0') * 10 +
           (idStr[3] - '0');
}

int Semestre::extrairPeriodo(const std::string& idStr) 
{
    return (idStr[5] - '0') * 10 + (idStr[6] - '0');
}