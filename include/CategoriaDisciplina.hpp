#ifndef DIARIOATIVIDADES_HPP
#define DIARIOATIVIDADES_HPP

#include "AtividadeAvaliativa.hpp"
#include <vector>
#include <string>

class DiarioAtividades 
{
private:
    std::vector<AtividadeAvaliativa> _atividades;
    int _contadorId;

    static bool compararDataMaisAntiga(const AtividadeAvaliativa& a, const AtividadeAvaliativa& b);
public:
    DiarioAtividades();

    void adicionarAtividade(const std::string& nome, const std::string& dataInput, float valorMaximo);
    void adicionarAtividade(int id, const std::string& nome, const std::string& dataInput, float valorMaximo, float notaObtida, bool concluida);

    void removerAtividade(int idAtividade);
    AtividadeAvaliativa* buscarAtividade(int idAtividade);
    void ordenarAtividades();

    const std::vector<AtividadeAvaliativa>& getAtividades() const;

    float obterValorTotalPlanejado() const;
    float obterValorTotalConcluido() const;
    float obterNotaTotalParcial() const;
    float obterMediaParcial() const;
    float calcularPercentualAproveitamento() const;
    char obterConceitoParcial() const;
};

#endif