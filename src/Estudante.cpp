#include "Estudante.hpp"
#include <stdexcept>

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

