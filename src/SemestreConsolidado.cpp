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
    if (!this->_trancado) 
    {
        this->setNSGFixo(nsgFixo);
        this->setHorasObrigatorias(horasObrigatorias);
        this->setHorasOptativas(horasOptativas);
        this->setHorasFormacaoLivre(horasFormacaoLivre);
    }
}

SemestreConsolidado::~SemestreConsolidado() {}
