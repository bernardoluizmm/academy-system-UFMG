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

