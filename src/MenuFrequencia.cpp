#include "MenuFrequencia.hpp"
#include "MenuPrincipal.hpp"
#include "SemestreAtual.hpp"
#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>

MenuFrequencia::MenuFrequencia(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo)
    : Menu(estudante, gerenciadorArquivo) 
{
}

MenuFrequencia::~MenuFrequencia() 
{
}

void MenuFrequencia::exibir() 
{
    const SemestreAtual* semAtual = this->_estudante.getHistorico().getSemestreAtual();

    std::cout << "\n========================================================================\n";
    std::cout << "                    GERENCIAMENTO DE FREQUENCIA E FALTAS                \n";
    std::cout << "========================================================================\n";

    if (semAtual == nullptr || semAtual->getDisciplinas().empty()) 
    {
        std::cout << " Nenhuma disciplina cadastrada no semestre atual.\n";
    } else 
    {
        std::cout << std::left
                  << std::setw(4)  << "ID"
                  << std::setw(10) << "Codigo"
                  << std::setw(28) << "Disciplina"
                  << std::setw(15) << "Faltas Atuais"
                  << std::setw(12) << "Max Faltas" << "\n";
        std::cout << "------------------------------------------------------------------------\n";

        const std::vector<Disciplina>& disciplinas = semAtual->getDisciplinas();
        for (std::vector<Disciplina>::const_iterator it = disciplinas.begin(); it != disciplinas.end(); ++it) 
        {
            std::cout << std::left
                      << std::setw(4)  << it->getId()
                      << std::setw(10) << it->getCodigo().substr(0, 8)
                      << std::setw(28) << it->getNome().substr(0, 26)
                      << std::setw(15) << it->frequencia().getFaltasAtuais()
                      << std::setw(12) << it->frequencia().getMaxFaltas() << "\n";
        }
    }

    std::cout << "========================================================================\n";
    std::cout << "1 - Adicionar 1 falta em uma disciplina\n";
    std::cout << "2 - Remover 1 falta de uma disciplina\n";
    std::cout << "3 - Definir numero de faltas diretamente\n";
    std::cout << "0 - Voltar ao Menu Principal\n";
    std::cout << "========================================================================\n";
}

Menu* MenuFrequencia::processarEntrada() 
{
    while (true) 
    {
        int opcao = this->entradaSanitizada<int>("Escolha uma opcao: ");
        if (opcao == 1) 
        {
            this->fluxoAdicionarFalta();
            return new MenuFrequencia(this->_estudante, this->_gerenciadorArquivo);
        } else if (opcao == 2) 
        {
            this->fluxoRemoverFalta();
            return new MenuFrequencia(this->_estudante, this->_gerenciadorArquivo);
        } else if (opcao == 3) 
        {
            this->fluxoDefinirFaltas();
            return new MenuFrequencia(this->_estudante, this->_gerenciadorArquivo);
        } else if (opcao == 0) 
        {
            return new MenuPrincipal(this->_estudante, this->_gerenciadorArquivo);
        }
        std::cout << "[ERRO] Opcao invalida. Escolha entre 0 e 3.\n";
    }
}

Disciplina* MenuFrequencia::selecionarDisciplina() 
{
    SemestreAtual* semAtual = this->_estudante.getHistoricoEditavel().getSemestreAtual();
    if (semAtual == nullptr || semAtual->getDisciplinas().empty()) 
    {
        std::cout << "[AVISO] Nao ha disciplinas cadastradas no semestre atual.\n";
        return nullptr;
    }

    int idDisc = this->entradaSanitizada<int>("Informe o ID da disciplina (0 para cancelar): ");
    if (idDisc == 0) 
    {
        return nullptr;
    }

    Disciplina* disc = semAtual->buscarDisciplina(idDisc);
    if (disc == nullptr) 
    {
        std::cout << "[ERRO] Disciplina com ID " << idDisc << " nao encontrada.\n";
    }
    return disc;
}

void MenuFrequencia::fluxoAdicionarFalta() 
{
    Disciplina* disc = this->selecionarDisciplina();
    if (disc == nullptr) 
    {
        return;
    }

    try 
    {
        disc->frequencia().adicionarFalta();
        std::cout << "Falta registrada! Faltas em '" << disc->getNome() << "': "
                  << disc->frequencia().getFaltasAtuais() << "/" << disc->frequencia().getMaxFaltas() << "\n";
    } catch (const std::invalid_argument& e) 
    {
        std::cout << "[ERRO] " << e.what() << "\n";
    }
}

void MenuFrequencia::fluxoRemoverFalta() 
{
    Disciplina* disc = this->selecionarDisciplina();
    if (disc == nullptr) 
    {
        return;
    }

    try 
    {
        disc->frequencia().removerFalta();
        std::cout << "Falta removida! Faltas em '" << disc->getNome() << "': "
                  << disc->frequencia().getFaltasAtuais() << "/" << disc->frequencia().getMaxFaltas() << "\n";
    } catch (const std::invalid_argument& e) 
    {
        std::cout << "[ERRO] " << e.what() << "\n";
    }
}

void MenuFrequencia::fluxoDefinirFaltas() 
{
    Disciplina* disc = this->selecionarDisciplina();
    if (disc == nullptr) 
    {
        return;
    }

    while (true) 
    {
        try 
        {
            int novasFaltas = this->entradaSanitizada<int>("Informe o total de faltas atuais (0 a " +
                                                           std::to_string(disc->frequencia().getMaxFaltas()) + "): ");
            disc->frequencia().setFaltasAtuais(novasFaltas);
            std::cout << "Total de faltas atualizado para " << disc->frequencia().getFaltasAtuais()
                      << "/" << disc->frequencia().getMaxFaltas() << "!\n";
            break;
        } catch (const std::invalid_argument& e) 
        {
            std::cout << "[ERRO] " << e.what() << "\n";
        }
    }
}