#include "AtividadeAvaliativa.hpp"
#include "CalculadorConceito.hpp"
#include "CalculadorMedia.hpp"
#include <stdexcept>
#include <sstream>

AtividadeAvaliativa::AtividadeAvaliativa(int id, const std::string& nome, const std::string& dataInput, float valorMaximo) 
    : _id(id), _data(Data(dataInput)), _notaObtida(0.0f), _concluida(false) 
{
    this->setNome(nome);
    this->setValorMaximo(valorMaximo);
}

AtividadeAvaliativa::AtividadeAvaliativa(int id, const std::string& nome, const std::string& dataInput, float valorMaximo, float notaObtida, bool concluida) 
    : _id(id), _data(Data(dataInput)), _notaObtida(0.0f), _concluida(false) 
{
    this->setNome(nome);
    this->setValorMaximo(valorMaximo);
    if (concluida) 
    {
        this->setNotaObtida(notaObtida); 
    }
}

int AtividadeAvaliativa::getId() const 
{ 
    return this->_id; 
}

std::string AtividadeAvaliativa::getNome() const 
{ 
    return this->_nome; 
}

const Data& AtividadeAvaliativa::getData() const 
{
    return this->_data;
}

float AtividadeAvaliativa::getValorMaximo() const 
{ 
    return this->_valor; 
}

float AtividadeAvaliativa::getNotaObtida() const 
{ 
    return this->_notaObtida; 
}

bool AtividadeAvaliativa::isConcluida() const 
{ 
    return this->_concluida; 
}

void AtividadeAvaliativa::setNome(const std::string& novoNome) 
{
    if (novoNome.empty() || novoNome.length() > 24) {
        throw std::invalid_argument("O nome da atividade deve ter entre 1 e 24 caracteres.");
    }
    this->_nome = novoNome;
}

void AtividadeAvaliativa::setData(const std::string& novaData) 
{
    this->_data = Data(novaData);
}

void AtividadeAvaliativa::setValorMaximo(float novoValor) 
{
    if (novoValor <= 0.0f) 
    {
        throw std::invalid_argument("O valor da atividade deve ser maior que zero.");
    }
    if (this->_concluida && this->_notaObtida > novoValor) 
    {
        throw std::invalid_argument("A nota obtida nao pode maior menor que o valor da atividade.");
    }
    this->_valor = novoValor;
}

void AtividadeAvaliativa::setNotaObtida(float novaNota) 
{
    if (novaNota < 0.0f || novaNota > this->_valor) 
    {
        throw std::invalid_argument("A nota obtida deve estar entre 0 e o valor maximo da atividade.");
    }
    this->_notaObtida = novaNota;
    this->_concluida = true;
}

void AtividadeAvaliativa::removerLancamentoNota() 
{
    this->_notaObtida = 0.0f;
    this->_concluida = false;
}

float AtividadeAvaliativa::obterMedia() const 
{
    return CalculadorMedia::calcular(this->_valor);
}

char AtividadeAvaliativa::obterConceito() const 
{
    if (!this->_concluida || this->_valor <= 0.0f) 
    {
        return '-';
    }
    float percentual = (this->_notaObtida / this->_valor) * 100.0f;
    return CalculadorConceito::calcular(percentual);
}

std::string AtividadeAvaliativa::serializar() const 
{
    std::ostringstream fluxo;
    fluxo << "ATIVIDADE|" << this->_id << "|" << this->_nome << "|" << this->_data << "|"
        << this->_valor << "|" << this->_notaObtida << "|" << (this->_concluida ? 1 : 0);
    return fluxo.str();
}