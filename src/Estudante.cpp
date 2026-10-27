#include "Estudante.hpp"

Estudante::Estudante() : _nome("Estudante") {}

Estudante::Estudante(const std::string& nome, const Curso& curso, const HistoricoEscolar& historico)
    : _nome(""), _curso(curso), _historico(historico) 
{
    this->setNome(nome);
}