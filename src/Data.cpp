#include "Data.hpp"
#include <vector>
#include <stdexcept>

Data::Data(const std::string& dataInput) 
{
    if (dataInput.length() != 5 || dataInput[2] != '/') 
    {
        throw std::invalid_argument("Formato de entrada inválido. Digite no formato DD/MM.");
    }

    int dia = 0;
    int mes = 0;

    try
    {
        dia = std::stoi(dataInput.substr(0, 2));
        mes = std::stoi(dataInput.substr(3, 2)); 
    } catch (const std::exception& e) 
    {
        throw std::invalid_argument("Formato inválido. Use apenas números no formato DD/MM.");
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
        throw std::invalid_argument("Mês inválido. Digite um valor entre 01 e 12.");
    }

    std::vector<int> quantidadesDiasMes = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (dia < 1 || dia > quantidadesDiasMes[mes]) 
    {
        throw std::invalid_argument("Dia inválido para o mês informado.");
    }
}

