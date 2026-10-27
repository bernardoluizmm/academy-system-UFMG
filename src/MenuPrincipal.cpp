#include "MenuPrincipal.hpp"
#include "MenuDisciplina.hpp"
#include "MenuAtividadeAvaliativa.hpp"
#include "MenuFrequencia.hpp"
#include "MenuDetalhamentoDisciplina.hpp"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <vector>

MenuPrincipal::MenuPrincipal(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo)
    : Menu(estudante, gerenciadorArquivo) 
{}

MenuPrincipal::~MenuPrincipal() 
{}
void MenuPrincipal::exibirResumoAcademico() const 
{
    const Curso& curso = this->_estudante.getCurso();
    const HistoricoEscolar& hist = this->_estudante.getHistorico();
    const SemestreAtual* semAtual = hist.getSemestreAtual();

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\n==============================================================================================\n";
    std::cout << "  Seja muito bem-vindo " << this->_estudante.getNome() << "!\n";
    std::cout << "  Curso: " << curso.getNome()
              << " | Ingresso: " << curso.getSemestreIngresso()
              << " | Semestre Atual: " << (semAtual != nullptr ? semAtual->getIdentificador() : "-") << "\n";
    std::cout << "==============================================================================================\n";

    std::cout << "\n[INDICADORES DE RENDIMENTO (NSG)]\n";
    std::cout << " - NSG Parcial do Semestre ("
              << (semAtual != nullptr ? semAtual->getIdentificador() : "-") << "): "
              << (semAtual != nullptr ? semAtual->calcularNSG() : 0.0f) << "\n";
    std::cout << " - NSG Medio do Estudante:                " << hist.calcularNSGMedio() << "\n";
    std::cout << " - NSG Global do Estudante:               " << hist.calcularNSGGlobal() << "\n";

    std::cout << "\n[PROGRESSO DE INTEGRALIZACAO DO CURSO]\n";
    std::cout << " - % Total do Curso Completo:             "
              << this->_estudante.calcularPercentualCursoCompleto() << "% ("
              << hist.calcularTotalHorasIntegralizadas() << "h / "
              << curso.getHorasTotaisCurso() << "h)\n";
    std::cout << " - % Obrigatorias Completas:              "
              << this->_estudante.calcularPercentualObrigatorias() << "% ("
              << hist.calcularTotalHorasObrigatorias() << "h / "
              << curso.getHorasTotaisObrigatorias() << "h)\n";
    std::cout << " - % Formacao Livre Completa:             "
              << this->_estudante.calcularPercentualFormacaoLivre() << "% ("
              << hist.calcularTotalHorasFormacaoLivre() << "h / "
              << curso.getHorasTotaisFormacaoLivre() << "h)\n";
    std::cout << " - % Optativas Completas:                 "
              << this->_estudante.calcularPercentualOptativas() << "% ("
              << hist.calcularTotalHorasOptativas() << "h / "
              << curso.getHorasTotaisOptativas() << "h)\n";
    if (curso.getHorasAdicionais() > 0) 
    {
        std::cout << " - Horas Adicionais Exigidas (Opt/Livre): " << curso.getHorasAdicionais() << "h\n";
    }
}
void MenuPrincipal::exibirTabelaGeralDisciplinas() const 
{
    const SemestreAtual* semAtual = this->_estudante.getHistorico().getSemestreAtual();
    std::cout << "\n----------------------------------------------------------------------------------------------\n";
    std::cout << "                      TABELA GERAL DAS DISCIPLINAS DO SEMESTRE ATUAL                          \n";
    std::cout << "----------------------------------------------------------------------------------------------\n";

    if (semAtual == nullptr || semAtual->getDisciplinas().empty()) 
    {
        std::cout << " Nenhuma disciplina cadastrada no semestre atual.\n";
        return;
    }

    std::cout << std::left
              << std::setw(4)  << "ID"
              << std::setw(24) << "Disciplina"
              << std::setw(12) << "Nota Dist."
              << std::setw(13) << "Nota Obtida"
              << std::setw(13) << "Media Parc."
              << std::setw(10) << "Conceito"
              << std::setw(8)  << "Faltas"
              << std::setw(10) << "Max Faltas" << "\n";
    std::cout << "----------------------------------------------------------------------------------------------\n";

    const std::vector<Disciplina>& disciplinas = semAtual->getDisciplinas();
    for (std::vector<Disciplina>::const_iterator it = disciplinas.begin(); it != disciplinas.end(); ++it) 
    {
        std::cout << std::left
                  << std::setw(4)  << it->getId()
                  << std::setw(24) << it->getNome().substr(0, 22)
                  << std::setw(12) << it->avaliacoes().obterValorTotalConcluido()
                  << std::setw(13) << it->avaliacoes().obterNotaTotalParcial()
                  << std::setw(13) << it->avaliacoes().obterMediaParcial()
                  << std::setw(10) << it->avaliacoes().obterConceitoParcial()
                  << std::setw(8)  << it->frequencia().getFaltasAtuais()
                  << std::setw(10) << it->frequencia().getMaxFaltas() << "\n";
    }
}
void MenuPrincipal::exibir() 
{
    this->exibirResumoAcademico();
    this->exibirTabelaGeralDisciplinas();

    std::cout << "\n==============================================================================================\n";
    std::cout << "                                  OPCOES DO MENU PRINCIPAL                                    \n";
    std::cout << "==============================================================================================\n";
    std::cout << "1 - Gerenciar Disciplinas (Adicionar / Editar / Apagar)\n";
    std::cout << "2 - Gerenciar Atividades Avaliativas (Adicionar / Lancar Nota / Editar / Apagar)\n";
    std::cout << "3 - Gerenciar Frequencia e Faltas\n";
    std::cout << "4 - Ver Detalhamento de Disciplinas e Atividades Avaliativas\n";
    std::cout << "5 - Consolidar Semestre Atual e Iniciar Proximo Semestre\n";
    std::cout << "0 - Salvar e Sair\n";
    std::cout << "==============================================================================================\n";
}
Menu* MenuPrincipal::processarEntrada() 
{
    while (true) 
    {
        int opcao = this->entradaSanitizada<int>("Escolha uma opcao: ");
        if (opcao == 1) 
        {
            return new MenuDisciplina(this->_estudante, this->_gerenciadorArquivo);
        } else if (opcao == 2) 
        {
            return new MenuAtividadeAvaliativa(this->_estudante, this->_gerenciadorArquivo);
        } else if (opcao == 3) 
        {
            return new MenuFrequencia(this->_estudante, this->_gerenciadorArquivo);
        } else if (opcao == 4) 
        {
            return new MenuDetalhamentoDisciplina(this->_estudante, this->_gerenciadorArquivo);
        } else if (opcao == 5) 
        {
            std::cout << "\nDeseja consolidar o semestre atual ("
                      << this->_estudante.getHistorico().getSemestreAtual()->getIdentificador() << ")?\n";
            std::cout << "1 - Consolidar normalmente\n";
            std::cout << "2 - Consolidar como semestre TRANCADO (NSG ignorado)\n";
            std::cout << "0 - Cancelar\n";
            int subOp = this->entradaSanitizada<int>("Opcao: ");
            if (subOp == 1 || subOp == 2) 
            {
                this->_estudante.getHistoricoEditavel().consolidarSemestreAtual(subOp == 2);
                std::cout << "Semestre consolidado com sucesso! Novo semestre atual: "
                          << this->_estudante.getHistorico().getSemestreAtual()->getIdentificador() << "\n";
            }
            return new MenuPrincipal(this->_estudante, this->_gerenciadorArquivo);
        } else if (opcao == 0) 
        {
            try 
            {
                this->_gerenciadorArquivo.salvar(this->_estudante);
                std::cout << "Dados salvos com sucesso em '" << this->_gerenciadorArquivo.getNomeArquivo() << "'. Ate logo!\n";
            } catch (const std::exception& e) 
            {
                std::cout << "[ERRO AO SALVAR] " << e.what() << "\n";
            }
            return nullptr;
        }
        std::cout << "[ERRO] Opcao invalida. Escolha entre 0 e 5.\n";
    }
}