#include "Estudante.hpp"
#include <stdexcept>
#include <sstream>

Estudante::Estudante(const std::string& nome, const Curso& curso, const HistoricoEscolar& historico)
    : _nome(nome), _curso(curso), _historico(historico) 
{
    Estudante::validarNome(nome);
}

void Estudante::validarNome(const std::string& nome) 
{
    if (nome.empty() || nome.length() > 100) 
    {
        throw std::invalid_argument("O nome do estudante deve ter entre 1 e 100 caracteres.");
    }
}

std::string Estudante::getNome() const 
{
    return this->_nome;
}

const Curso& Estudante::getCurso() const 
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

float Estudante::calcularPercentual(int horasIntegralizadas, int horasRequeridas) const 
{
    if (horasRequeridas <= 0) 
    {
        return 0.0f;
    }
    float porcentagem = (static_cast<float>(horasIntegralizadas) / static_cast<float>(horasRequeridas)) * 100.0f;
    return (porcentagem > 100.0f) ? 100.0f : porcentagem;
}

float Estudante::calcularPercentualCursoCompleto() const 
{
    return calcularPercentual(_historico.calcularTotalHorasIntegralizadas(), 
        _curso.getHorasTotaisCurso());
}

float Estudante::calcularPercentualObrigatorias() const 
{
    return calcularPercentual(_historico.calcularTotalHorasObrigatorias(),
        _curso.getHorasTotaisObrigatorias()
    );
}

float Estudante::calcularPercentualOptativas() const 
{
    return calcularPercentual(_historico.calcularTotalHorasOptativas(),
        _curso.getHorasTotaisOptativas()
    );
}

float Estudante::calcularPercentualFormacaoLivre() const 
{
    return calcularPercentual(_historico.calcularTotalHorasFormacaoLivre(),
        _curso.getHorasTotaisFormacaoLivre()
    );
}

std::string Estudante::serializar() const 
{
    std::ostringstream oss;
    oss << "ESTUDANTE|" << this->_nome << "\n";
    oss << this->_curso.serializar() << "\n";
    oss << this->_historico.serializar();
    return oss.str();
}