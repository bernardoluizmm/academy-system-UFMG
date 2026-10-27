#include "Estudante.hpp"
#include <stdexcept>
#include <sstream>

Estudante::Estudante() : _nome("Estudante") {}

Estudante::Estudante(const std::string& nome, const Curso& curso, const HistoricoEscolar& historico)
    : _nome(""), _curso(curso), _historico(historico) 
{
    this->setNome(nome);
}

std::string Estudante::getNome() const 
{
    return this->_nome;
}

const Curso& Estudante::getCurso() const 
{
    return this->_curso;
}

Curso& Estudante::getCursoEditavel() 
{
    return this->_curso;
}

const HistoricoEscolar& Estudante::getHistorico() const 
{
    return this->_historico;
}

HistoricoEscolar& Estudante::getHistoricoEditavel() 
{
    return this->_historico;
}

void Estudante::setNome(const std::string& novoNome) 
{
    if (novoNome.empty() || novoNome.length() > 100) 
    {
        throw std::invalid_argument("O nome do estudante deve ter entre 1 e 100 caracteres.");
    }
    this->_nome = novoNome;
}

void Estudante::setCurso(const Curso& novoCurso) 
{
    this->_curso = novoCurso;
}

float Estudante::calcularPercentualCursoCompleto() const 
{
    int totalRequerido = this->_curso.getHorasTotaisCurso();
    if (totalRequerido <= 0) 
    {
        return 0.0f;
    }
    float pct = (static_cast<float>(this->_historico.calcularTotalHorasIntegralizadas()) /
                 static_cast<float>(totalRequerido)) * 100.0f;
    return (pct > 100.0f) ? 100.0f : pct;
}

float Estudante::calcularPercentualObrigatorias() const 
{
    int req = this->_curso.getHorasTotaisObrigatorias();
    if (req <= 0) 
    {
        return 0.0f;
    }
    float pct = (static_cast<float>(this->_historico.calcularTotalHorasObrigatorias()) /
                 static_cast<float>(req)) * 100.0f;
    return (pct > 100.0f) ? 100.0f : pct;
}

float Estudante::calcularPercentualOptativas() const 
{
    int req = this->_curso.getHorasTotaisOptativas();
    if (req <= 0) 
    {
        return 0.0f;
    }
    float pct = (static_cast<float>(this->_historico.calcularTotalHorasOptativas()) /
                 static_cast<float>(req)) * 100.0f;
    return (pct > 100.0f) ? 100.0f : pct;
}

float Estudante::calcularPercentualFormacaoLivre() const 
{
    int req = this->_curso.getHorasTotaisFormacaoLivre();
    if (req <= 0) 
    {
        return 0.0f;
    }
    float pct = (static_cast<float>(this->_historico.calcularTotalHorasFormacaoLivre()) /
                 static_cast<float>(req)) * 100.0f;
    return (pct > 100.0f) ? 100.0f : pct;
}

std::string Estudante::serializar() const 
{
    std::ostringstream oss;
    oss << "ESTUDANTE|" << this->_nome << "\n";
    oss << this->_curso.serializar() << "\n";
    oss << this->_historico.serializar();
    return oss.str();
}