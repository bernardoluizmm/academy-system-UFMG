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
void SemestreAtual::adicionarDisciplina(const std::string& codigo,
                                        const std::string& codigoTurma,
                                        const std::string& nome,
                                        const std::string& professor,
                                        const std::string& salaBloco,
                                        int cargaHoraria,
                                        int duracaoAulaMinutos,
                                        const std::string& tipo,
                                        const std::string& horarioDias) 
{
    Disciplina novaDisciplina(this->_contadorId,
                              codigo,
                              codigoTurma,
                              nome,
                              professor,
                              salaBloco,
                              cargaHoraria,
                              duracaoAulaMinutos,
                              tipo,
                              horarioDias);

    this->_disciplinas.push_back(novaDisciplina);
    this->_contadorId++;
}

void SemestreAtual::adicionarDisciplina(const Disciplina& disciplina) 
{
    for (std::vector<Disciplina>::const_iterator it = this->_disciplinas.begin(); it != this->_disciplinas.end(); ++it) 
    {
        if (it->getId() == disciplina.getId()) 
        {
            throw std::invalid_argument("Ja existe uma disciplina com este ID no semestre atual.");
        }
    }

    this->_disciplinas.push_back(disciplina);

    if (disciplina.getId() >= this->_contadorId) 
    {
        this->_contadorId = disciplina.getId() + 1;
    }
}

void SemestreAtual::removerDisciplina(int idDisciplina) 
{
    for (std::vector<Disciplina>::iterator it = this->_disciplinas.begin(); it != this->_disciplinas.end(); ++it) 
    {
        if (it->getId() == idDisciplina) 
        {
            this->_disciplinas.erase(it);
            return;
        }
    }
    throw std::invalid_argument("Disciplina nao encontrada para remocao.");
}

Disciplina* SemestreAtual::buscarDisciplina(int idDisciplina) 
{
    for (std::vector<Disciplina>::iterator it = this->_disciplinas.begin(); it != this->_disciplinas.end(); ++it) 
    {
        if (it->getId() == idDisciplina) 
        {
            return &(*it);
        }
    }
    return nullptr;
}

const std::vector<Disciplina>& SemestreAtual::getDisciplinas() const 
{
    return this->_disciplinas;
}

std::vector<Disciplina>& SemestreAtual::getDisciplinasEditavel() 
{
    return this->_disciplinas;
}
std::string SemestreAtual::serializar() const 
{
    std::ostringstream oss;
    oss << "SEMESTRE_ATUAL|" << getIdentificador() << "\n";
    for (std::vector<Disciplina>::const_iterator it = this->_disciplinas.begin(); it != this->_disciplinas.end(); ++it) 
    {
        oss << it->serializar();
    }
    return oss.str();
}