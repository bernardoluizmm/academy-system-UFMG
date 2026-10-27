#include "MenuDetalhamentoDisciplina.hpp"
#include "MenuPrincipal.hpp"
#include "SemestreAtual.hpp"
#include "AtividadeAvaliativa.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

MenuDetalhamentoDisciplina::MenuDetalhamentoDisciplina(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo)
    : Menu(estudante, gerenciadorArquivo) 
{
}

MenuDetalhamentoDisciplina::~MenuDetalhamentoDisciplina() 
{
}

void MenuDetalhamentoDisciplina::exibirDetalhamentoDisciplina(const Disciplina& disciplina) const 
{
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\n========================================================================================\n";
    std::cout << "Disciplina [" << disciplina.getId() << "]: " << disciplina.getNome() << "\n";
    std::cout << "Codigo: " << disciplina.getCodigo()
              << " | Turma: " << disciplina.getCodigoTurma()
              << " | Prof.: " << disciplina.getProfessor()
              << " | Sala/Bloco: " << disciplina.getSalaBloco()
              << " | CH: " << disciplina.getCargaHoraria() << "h"
              << " | Tipo: " << disciplina.getTipo()
              << " | Horario/Dias: " << disciplina.getHorarioDias() << "\n";
    std::cout << "----------------------------------------------------------------------------------------\n";
    std::cout << std::left
              << std::setw(4)  << "ID"
              << std::setw(28) << "Atividade Avaliativa"
              << std::setw(10) << "Data"
              << std::setw(12) << "Valor"
              << std::setw(14) << "Nota Obtida"
              << std::setw(10) << "Conceito"
              << std::setw(10) << "Media" << "\n";
    std::cout << "----------------------------------------------------------------------------------------\n";

    const std::vector<AtividadeAvaliativa>& atividades = disciplina.avaliacoes().getAtividades();
    for (std::vector<AtividadeAvaliativa>::const_iterator ait = atividades.begin();
         ait != atividades.end(); ++ait) 
    {
        std::ostringstream notaStr;
        notaStr << std::fixed << std::setprecision(2);
        if (ait->isConcluida()) 
        {
            notaStr << ait->getNotaObtida();
        } else 
        {
            notaStr << "Pendente";
        }

        std::cout << std::left
                  << std::setw(4)  << ait->getId()
                  << std::setw(28) << ait->getNome().substr(0, 26)
                  << std::setw(10) << ait->getData().getDataValidada()
                  << std::setw(12) << ait->getValorMaximo()
                  << std::setw(14) << notaStr.str()
                  << std::setw(10) << ait->obterConceito()
                  << std::setw(10) << ait->obterMedia() << "\n";
    }

    std::cout << "----------------------------------------------------------------------------------------\n";
    std::cout << std::left
              << std::setw(4)  << ""
              << std::setw(28) << "TOTAL"
              << std::setw(10) << "-"
              << std::setw(12) << disciplina.avaliacoes().obterValorTotalConcluido()
              << std::setw(14) << disciplina.avaliacoes().obterNotaTotalParcial()
              << std::setw(10) << disciplina.avaliacoes().obterConceitoParcial()
              << std::setw(10) << disciplina.avaliacoes().obterMediaParcial() << "\n";
    std::cout << "========================================================================================\n";
}