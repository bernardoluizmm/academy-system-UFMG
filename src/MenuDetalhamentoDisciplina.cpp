#include "MenuDetalhamentoDisciplina.hpp"
#include "AtividadeAvaliativa.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

MenuDetalhamentoDisciplina::MenuDetalhamentoDisciplina(const SemestreAtual& semestreAtual)
    : Menu(), _semestreAtual(semestreAtual) {}

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

void MenuDetalhamentoDisciplina::fluxoDetalharDisciplinaEspecifica() 
{
    SemestreAtual* semAtual = this->_estudante.getHistoricoEditavel().getSemestreAtual();
    if (semAtual == nullptr || semAtual->getDisciplinas().empty()) 
    {
        std::cout << "[AVISO] Nenhuma disciplina cadastrada no semestre atual.\n";
        return;
    }

    int idDisc = this->entradaSanitizada<int>("Informe o ID da disciplina que deseja visualizar (0 para cancelar): ");
    if (idDisc == 0) 
    {
        return;
    }

    const Disciplina* disc = semAtual->buscarDisciplina(idDisc);
    if (disc == nullptr) 
    {
        std::cout << "[ERRO] Disciplina com ID " << idDisc << " nao encontrada.\n";
        return;
    }

    this->exibirDetalhamentoDisciplina(*disc);
}

void MenuDetalhamentoDisciplina::fluxoDetalharTodasDisciplinas() const 
{
    const SemestreAtual* semAtual = this->_estudante.getHistorico().getSemestreAtual();
    if (semAtual == nullptr || semAtual->getDisciplinas().empty()) 
    {
        std::cout << "[AVISO] Nenhuma disciplina cadastrada no semestre atual.\n";
        return;
    }

    const std::vector<Disciplina>& disciplinas = semAtual->getDisciplinas();
    for (std::vector<Disciplina>::const_iterator it = disciplinas.begin(); it != disciplinas.end(); ++it) 
    {
        this->exibirDetalhamentoDisciplina(*it);
    }
}

void MenuDetalhamentoDisciplina::exibir() 
{
    const SemestreAtual* semAtual = this->_estudante.getHistorico().getSemestreAtual();

    std::cout << "\n========================================================================\n";
    std::cout << "           DETALHAMENTO DE DISCIPLINAS E ATIVIDADES AVALIATIVAS         \n";
    std::cout << "========================================================================\n";

    if (semAtual == nullptr || semAtual->getDisciplinas().empty()) 
    {
        std::cout << " Nenhuma disciplina cadastrada no semestre atual.\n";
    } else 
    {
        std::cout << "Disciplinas disponiveis no semestre atual:\n";
        const std::vector<Disciplina>& disciplinas = semAtual->getDisciplinas();
        for (std::vector<Disciplina>::const_iterator it = disciplinas.begin(); it != disciplinas.end(); ++it) 
        {
            std::cout << "  [" << it->getId() << "] " << it->getCodigo() << " - " << it->getNome() << "\n";
        }
    }

    std::cout << "========================================================================\n";
    std::cout << "1 - Visualizar detalhamento de uma disciplina especifica\n";
    std::cout << "2 - Visualizar detalhamento de todas as disciplinas\n";
    std::cout << "0 - Voltar ao Menu Principal\n";
    std::cout << "========================================================================\n";
}
Menu* MenuDetalhamentoDisciplina::processarEntrada() 
{
    while (true) 
    {
        int opcao = this->entradaSanitizada<int>("Escolha uma opcao: ");
        if (opcao == 1) 
        {
            this->fluxoDetalharDisciplinaEspecifica();
            return new MenuDetalhamentoDisciplina(this->_estudante, this->_gerenciadorArquivo);
        } else if (opcao == 2) 
        {
            this->fluxoDetalharTodasDisciplinas();
            return new MenuDetalhamentoDisciplina(this->_estudante, this->_gerenciadorArquivo);
        } else if (opcao == 0) 
        {
            return new MenuPrincipal(this->_estudante, this->_gerenciadorArquivo);
        }
        std::cout << "[ERRO] Opcao invalida. Escolha entre 0 e 2.\n";
    }
}