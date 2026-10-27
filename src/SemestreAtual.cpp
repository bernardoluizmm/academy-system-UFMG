#include "SemestreAtual.hpp"
#include <stdexcept>
#include <sstream>

SemestreAtual::SemestreAtual() : Semestre("2026/01", false), _contadorId(1) {}

SemestreAtual::SemestreAtual(const std::string& identificador) : Semestre(identificador, false), _contadorId(1) {}

SemestreAtual::~SemestreAtual() 
{
    this->_disciplinas.clear();
}
float SemestreAtual::calcularNSG() const 
{
    if (this->_disciplinas.empty()) 
    {
        return 0.0f;
    }
    float somaPonderada = 0.0f;
    int somaCargaHoraria = 0;

    for (std::vector<Disciplina>::const_iterator it = this->_disciplinas.begin(); it != this->_disciplinas.end(); ++it) 
    {
        somaPonderada += it->avaliacoes().calcularPercentualAproveitamento() * static_cast<float>(it->getCargaHoraria());
        somaCargaHoraria += it->getCargaHoraria();
    }

    if (somaCargaHoraria == 0) 
    {
        return 0.0f;
    }
    return somaPonderada / static_cast<float>(somaCargaHoraria);
}

    int SemestreAtual::getHorasIntegralizadas() const 
{
    return this->getHorasObrigatorias() + this->getHorasOptativas() + this->getHorasFormacaoLivre();
}

int SemestreAtual::getHorasObrigatorias() const 
{
    int soma = 0;
    for (std::vector<Disciplina>::const_iterator it = this->_disciplinas.begin(); it != this->_disciplinas.end(); ++it) 
    {
        if (it->getTipo() == "Obrigatoria" && it->avaliacoes().obterNotaTotalParcial() >= 60.0f) 
        {
            soma += it->getCargaHoraria();
        }
    }
    return soma;
}
