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

const SemestreAtual* HistoricoEscolar::getSemestreAtual() const 
{
    return this->_semestreAtual;
}

void HistoricoEscolar::definirSemestreAtual(const std::string& identificador) 
{
    SemestreAtual* novoSemestre = new SemestreAtual(identificador);
    delete this->_semestreAtual;
    this->_semestreAtual = novoSemestre;
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

float HistoricoEscolar::calcularNSGMedio() const 
{
    float somaNSG = 0.0f;
    int qtdValidos = 0;

    for (std::vector<SemestreConsolidado>::const_iterator it = this->_semestresPassados.begin();
         it != this->_semestresPassados.end(); ++it) 
    {
        if (!it->isTrancado()) 
        {
            somaNSG += it->calcularNSG();
            qtdValidos++;
        }
    }

    if (qtdValidos == 0) 
    {
        return 0.0f;
    }
    return somaNSG / static_cast<float>(qtdValidos);
}

float HistoricoEscolar::calcularNSGGlobal() const 
{
    float somaPonderada = 0.0f;
    int somaHoras = 0;

    for (std::vector<SemestreConsolidado>::const_iterator it = this->_semestresPassados.begin();
         it != this->_semestresPassados.end(); ++it) 
    {
        if (!it->isTrancado()) 
        {
            int horasSemestre = it->getHorasIntegralizadas();
            somaPonderada += it->calcularNSG() * static_cast<float>(horasSemestre);
            somaHoras += horasSemestre;
        }
    }

    if (somaHoras == 0) 
    {
        return 0.0f;
    }
    return somaPonderada / static_cast<float>(somaHoras);
}

int HistoricoEscolar::calcularTotalHorasObrigatorias() const 
{
    int total = 0;
    for (std::vector<SemestreConsolidado>::const_iterator it = this->_semestresPassados.begin();
         it != this->_semestresPassados.end(); ++it) 
    {
        total += it->getHorasObrigatorias();
    }
    return total;
}

int HistoricoEscolar::calcularTotalHorasOptativas() const 
{
    int total = 0;
    for (std::vector<SemestreConsolidado>::const_iterator it = this->_semestresPassados.begin();
         it != this->_semestresPassados.end(); ++it) 
    {
        total += it->getHorasOptativas();
    }
    return total;
}

int HistoricoEscolar::calcularTotalHorasFormacaoLivre() const 
{
    int total = 0;
    for (std::vector<SemestreConsolidado>::const_iterator it = this->_semestresPassados.begin();
         it != this->_semestresPassados.end(); ++it) 
    {
        total += it->getHorasFormacaoLivre();
    }
    return total;
}

int HistoricoEscolar::calcularTotalHorasIntegralizadas() const 
{
    return this->calcularTotalHorasObrigatorias() +
           this->calcularTotalHorasOptativas() +
           this->calcularTotalHorasFormacaoLivre();
}

std::string HistoricoEscolar::serializar() const 
{
    std::ostringstream oss;
    for (std::vector<SemestreConsolidado>::const_iterator it = this->_semestresPassados.begin();
         it != this->_semestresPassados.end(); ++it) 
    {
        oss << it->serializar() << "\n";
    }
    if (this->_semestreAtual != nullptr) 
    {
        oss << this->_semestreAtual->serializar();
    }
    return oss.str();
}