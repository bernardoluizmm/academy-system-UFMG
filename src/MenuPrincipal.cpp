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
