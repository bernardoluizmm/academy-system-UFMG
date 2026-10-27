#include "HistoricoEscolar.hpp"
#include <sstream>

HistoricoEscolar::HistoricoEscolar()
    : _semestreAtual(new SemestreAtual("2026/01")) 
{
}

HistoricoEscolar::HistoricoEscolar(const HistoricoEscolar& outro)
    : _semestresPassados(outro._semestresPassados),
      _semestreAtual(nullptr) 
{
    if (outro._semestreAtual != nullptr) 
    {
        this->_semestreAtual = new SemestreAtual(*(outro._semestreAtual));
    } else 
    {
        this->_semestreAtual = new SemestreAtual("2026/01");
    }
}

HistoricoEscolar& HistoricoEscolar::operator=(const HistoricoEscolar& outro) 
{
    if (this != &outro) 
    {
        this->_semestresPassados = outro._semestresPassados;
        delete this->_semestreAtual;
        if (outro._semestreAtual != nullptr) 
        {
            this->_semestreAtual = new SemestreAtual(*(outro._semestreAtual));
        } else 
        {
            this->_semestreAtual = new SemestreAtual("2026/01");
        }
    }
    return *this;
}

HistoricoEscolar::~HistoricoEscolar() 
{
    delete this->_semestreAtual;
    this->_semestreAtual = nullptr;
}

void HistoricoEscolar::adicionarSemestreConsolidado(const SemestreConsolidado& semestre) 
{
    this->_semestresPassados.push_back(semestre);
}

const std::vector<SemestreConsolidado>& HistoricoEscolar::getSemestresPassados() const 
{
    return this->_semestresPassados;
}

void HistoricoEscolar::limparSemestresPassados() 
{
    this->_semestresPassados.clear();
}

SemestreAtual* HistoricoEscolar::getSemestreAtual() 
{
    return this->_semestreAtual;
}

void HistoricoEscolar::consolidarSemestreAtual(bool trancado) 
{
    if (this->_semestreAtual == nullptr) 
    {
        return;
    }
    std::string idAtual = this->_semestreAtual->getIdentificador();
    float nsgFinal = trancado ? 0.0f : this->_semestreAtual->calcularNSG();
    int hObrig = trancado ? 0 : this->_semestreAtual->getHorasObrigatorias();
    int hOpt = trancado ? 0 : this->_semestreAtual->getHorasOptativas();
    int hLivre = trancado ? 0 : this->_semestreAtual->getHorasFormacaoLivre();

    SemestreConsolidado novoConsolidado(idAtual, nsgFinal, hObrig, hOpt, hLivre, trancado);
    this->_semestresPassados.push_back(novoConsolidado);

    std::string proximoId = Semestre::proximoIdentificadorSemestre(idAtual);
    delete this->_semestreAtual;
    this->_semestreAtual = new SemestreAtual(proximoId);
}