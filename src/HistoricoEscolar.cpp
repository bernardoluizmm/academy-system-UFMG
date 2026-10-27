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
