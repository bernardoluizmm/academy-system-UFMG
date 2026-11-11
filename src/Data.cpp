#include "Data.hpp"
#include <vector>
#include <stdexcept>
#include <cctype>

Data::Data(const std::string& dataInput) 
{
    if (dataInput.length() != 5 || dataInput[2] != '/') 
    {
        throw std::invalid_argument("Formato de entrada invalido. Digite no formato DD/MM.");
    }

    if (!std::isdigit(static_cast<unsigned char>(dataInput[0])) ||
        !std::isdigit(static_cast<unsigned char>(dataInput[1])) ||
        !std::isdigit(static_cast<unsigned char>(dataInput[3])) ||
        !std::isdigit(static_cast<unsigned char>(dataInput[4])))
    {
        throw std::invalid_argument("Formato invalido. Use apenas numeros no formato DD/MM.");
    }

    int dia = 0;
    int mes = 0;

    try
    {
        dia = std::stoi(dataInput.substr(0, 2));
        mes = std::stoi(dataInput.substr(3, 2)); 
    } catch (const std::exception&) 
    {
        throw std::invalid_argument("Formato invalido. Use apenas numeros no formato DD/MM.");
    }

    validarData(dia, mes);

    this->_dia = dia;
    this->_mes = mes; 
    this->_data = dataInput;
}

void Data::validarData(int dia, int mes)
{
    if (mes < 1 || mes > 12) 
    {
        throw std::invalid_argument("Mes invalido. Digite um valor entre 01 e 12.");
    }

    std::vector<int> quantidadesDiasMes = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (dia < 1 || dia > quantidadesDiasMes[mes]) 
    {
        throw std::invalid_argument("Dia invalido para o mes informado.");
    }
}

std::string Data::getDataValidada() const 
{
    return this->_data;
}

bool Data::operator<(const Data& outraData) const 
{
    if (this->_mes != outraData._mes) 
    {
        return this->_mes < outraData._mes;
    }
    return this->_dia < outraData._dia;
}

std::ostream& operator<<(std::ostream& os, const Data& d) 
{
    os << d._data; 
    return os;
}