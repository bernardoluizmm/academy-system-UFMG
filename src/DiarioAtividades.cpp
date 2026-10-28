#include "DiarioAtividades.hpp"
#include "CalculadorConceito.hpp"
#include "CalculadorMedia.hpp"
#include <stdexcept>
#include <algorithm>

DiarioAtividades::DiarioAtividades() : _contadorId(0) {}

bool DiarioAtividades::compararDataMaisAntiga(const AtividadeAvaliativa& a, const AtividadeAvaliativa& b) 
{
    return a.getData() < b.getData();
}

void DiarioAtividades::ordenarAtividades() 
{
    std::sort(this->_atividades.begin(), this->_atividades.end(), compararDataMaisAntiga);
}

void DiarioAtividades::adicionarAtividade(const std::string& nome, const std::string& dataInput, float valorMaximo) 
{
    AtividadeAvaliativa novaAtividade(this->_contadorId, nome, dataInput, valorMaximo);
    this->_atividades.push_back(novaAtividade);
    this->_contadorId++;
    this->ordenarAtividades();
}

void DiarioAtividades::adicionarAtividade(int id, const std::string& nome, const std::string& dataInput, float valorMaximo, float notaObtida, bool concluida) 
{
    AtividadeAvaliativa atividadeCarregada(id, nome, dataInput, valorMaximo, notaObtida, concluida);
    this->_atividades.push_back(atividadeCarregada);

    if (id >= this->_contadorId) 
    {
        this->_contadorId = id + 1;
    }

    this->ordenarAtividades();
}

void DiarioAtividades::removerAtividade(int idAtividade) 
{
    bool encontrada = false;
    for (std::vector<AtividadeAvaliativa>::iterator it = this->_atividades.begin(); it != this->_atividades.end(); ++it) 
    {
        if (it->getId() == idAtividade) 
        {
            this->_atividades.erase(it);
            encontrada = true;
            break;
        }
    }
    if (!encontrada) 
    {
        throw std::invalid_argument("Atividade avaliativa nao encontrada.");
    }
}

AtividadeAvaliativa* DiarioAtividades::buscarAtividade(int idAtividade) 
{
    for (std::vector<AtividadeAvaliativa>::iterator it = this->_atividades.begin(); it != this->_atividades.end(); ++it) 
    {
        if (it->getId() == idAtividade) 
        {
            return &(*it);
        }
    }
    return nullptr;
}

const std::vector<AtividadeAvaliativa>& DiarioAtividades::getAtividades() const 
{
    return this->_atividades;
}

float DiarioAtividades::obterValorTotalPlanejado() const 
{
    float soma = 0.0f;
    for (std::vector<AtividadeAvaliativa>::const_iterator it = this->_atividades.begin(); it != this->_atividades.end(); ++it) 
    {
        soma += it->getValorMaximo();
    }
    return soma;
}

float DiarioAtividades::obterValorTotalConcluido() const 
{
    float soma = 0.0f;
    for (std::vector<AtividadeAvaliativa>::const_iterator it = this->_atividades.begin(); it != this->_atividades.end(); ++it) 
    {
        if (it->isConcluida()) 
        {
            soma += it->getValorMaximo();
        }
    }
    return soma;
}

float DiarioAtividades::obterNotaTotalParcial() const 
{
    float soma = 0.0f;
    for (std::vector<AtividadeAvaliativa>::const_iterator it = this->_atividades.begin(); it != this->_atividades.end(); ++it) 
    {
        if (it->isConcluida()) 
        {
            soma += it->getNotaObtida();
        }
    }
    return soma;
}

float DiarioAtividades::obterMediaParcial() const 
{
    return CalculadorMedia::calcular(this->obterValorTotalConcluido());
}

float DiarioAtividades::calcularPercentualAproveitamento() const 
{
    float valorConcluido = this->obterValorTotalConcluido();
    if (valorConcluido <= 0.0f) 
    {
        return 0.0f;
    }
    return (this->obterNotaTotalParcial() / valorConcluido) * 100.0f;
}

char DiarioAtividades::obterConceitoParcial() const 
{
    float valorConcluido = this->obterValorTotalConcluido();
    if (valorConcluido <= 0.0f) 
    {
        return '-';
    }
    return CalculadorConceito::calcular(this->calcularPercentualAproveitamento());
}