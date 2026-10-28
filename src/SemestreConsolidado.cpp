#include "SemestreConsolidado.hpp"
#include <sstream>

SemestreConsolidado::SemestreConsolidado(const std::string& identificador,
                                         float nsgFixo,
                                         int horasObrigatorias,
                                         int horasOptativas,
                                         int horasFormacaoLivre,
                                         bool trancado)
    : Semestre(identificador, trancado),
      _nsgFixo(0.0f),
      _horasObrigatorias(0),
      _horasOptativas(0),
      _horasFormacaoLivre(0) 
{
    if (!this->isTrancado()) 
    {
        this->setNSGFixo(nsgFixo);
        this->setHorasObrigatorias(horasObrigatorias);
        this->setHorasOptativas(horasOptativas);
        this->setHorasFormacaoLivre(horasFormacaoLivre);
    }
}

SemestreConsolidado::~SemestreConsolidado() {}
void SemestreConsolidado::setNSGFixo(float nsgFixo) 
{
    Semestre::validarNSG(nsgFixo);
    this->_nsgFixo = nsgFixo;
}

void SemestreConsolidado::setHorasObrigatorias(int horasObrigatorias) 
{
    Semestre::validarHoras(horasObrigatorias);
    this->_horasObrigatorias = horasObrigatorias;
}

void SemestreConsolidado::setHorasOptativas(int horasOptativas) 
{
    Semestre::validarHoras(horasOptativas);
    this->_horasOptativas = horasOptativas;
}

void SemestreConsolidado::setHorasFormacaoLivre(int horasFormacaoLivre) 
{
    Semestre::validarHoras(horasFormacaoLivre);
    this->_horasFormacaoLivre = horasFormacaoLivre;
}

float SemestreConsolidado::calcularNSG() const 
{
    if (this->isTrancado()) 
    {
        return 0.0f;
    }
    return this->_nsgFixo;
}

int SemestreConsolidado::getHorasIntegralizadas() const 
{
    if (this->isTrancado()) 
    {
        return 0;
    }
    return this->_horasObrigatorias + this->_horasOptativas + this->_horasFormacaoLivre;
}

int SemestreConsolidado::getHorasObrigatorias() const 
{
    return this->isTrancado() ? 0 : this->_horasObrigatorias;
}

int SemestreConsolidado::getHorasOptativas() const 
{
    return this->isTrancado() ? 0 : this->_horasOptativas;
}

int SemestreConsolidado::getHorasFormacaoLivre() const 
{
    return this->isTrancado() ? 0 : this->_horasFormacaoLivre;
}

std::string SemestreConsolidado::serializar() const 
{
    std::ostringstream oss;
    oss << "SEMESTRE_CONSOLIDADO|" << this->getIdentificador() << "|"
        << this->_nsgFixo << "|" << this->_horasObrigatorias << "|"
        << this->_horasOptativas << "|" << this->_horasFormacaoLivre << "|"
        << (this->isTrancado() ? 1 : 0);
    return oss.str();
}