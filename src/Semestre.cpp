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

void Semestre::validarNSG(float nsg) 
{
    if (nsg < 0.0f || nsg > 100.0f) 
    {
        throw std::invalid_argument("O NSG deve estar entre 0 e 100.");
    }
}

void Semestre::validarHoras(int horas) 
{
    if (horas < 0 || horas % 15 != 0) 
    {
        throw std::invalid_argument("A carga horaria deve ser maior ou igual a 0 e divisivel por 15.");
    }
}

void Semestre::validarIntervaloSemestres(const std::string& semIngresso, const std::string& semAtual) 
{
    if (!Semestre::validarFormatoIdentificador(semIngresso) || !Semestre::validarFormatoIdentificador(semAtual)) 
    {
        throw std::invalid_argument("Formato de semestre invalido. Use AAAA/01 ou AAAA/02.");
    }
    int anoIngresso = Semestre::extrairAno(semIngresso);
    int perIngresso = Semestre::extrairPeriodo(semIngresso);
    int anoAtual = Semestre::extrairAno(semAtual);
    int perAtual = Semestre::extrairPeriodo(semAtual);

    if (anoAtual < anoIngresso || (anoAtual == anoIngresso && perAtual < perIngresso)) 
    {
        throw std::invalid_argument("O semestre atual nao pode ser anterior ao semestre de ingresso.");
    }
    if ((anoAtual - anoIngresso) > 9) 
    {
        throw std::invalid_argument("O ano de ingresso e o ano do semestre atual nao podem ter mais de 9 anos de diferenca.");
    }
}

std::string Semestre::proximoIdentificadorSemestre(const std::string& idAtual) 
{
    int ano = Semestre::extrairAno(idAtual);
    int periodo = Semestre::extrairPeriodo(idAtual);
    std::ostringstream fluxo;
    if (periodo == 1) 
    {
        fluxo << ano << "/02";
    } else 
    {
        fluxo << (ano + 1) << "/01";
    }
    return fluxo.str();
}
std::vector<std::string> Semestre::gerarSemestresAnteriores(const std::string& semIngresso, const std::string& semAtual) 
{
    Semestre::validarIntervaloSemestres(semIngresso, semAtual);
    std::vector<std::string> lista;
    std::string fluxo = semIngresso;
    while (fluxo != semAtual) 
    {
        lista.push_back(fluxo);
        fluxo = Semestre::proximoIdentificadorSemestre(fluxo);
    }
    return lista;
}