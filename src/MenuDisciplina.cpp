#include "MenuDisciplina.hpp"
#include "MenuPrincipal.hpp"
#include "SemestreAtual.hpp"
#include "Disciplina.hpp"
#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>

MenuDisciplina::MenuDisciplina(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo)
    : Menu(estudante, gerenciadorArquivo) 
{}

MenuDisciplina::~MenuDisciplina() {}

std::string MenuDisciplina::escolherTipoDisciplina() 
{
    while (true) 
    {
        std::cout << "Selecione o tipo da disciplina:\n";
        std::cout << "  1 - Obrigatoria\n";
        std::cout << "  2 - Optativa\n";
        std::cout << "  3 - Formacao Livre\n";
        int op = this->entradaSanitizada<int>("Opcao (1 a 3): ");
        if (op == 1) 
        {
            return "Obrigatoria";
        } else if (op == 2) 
        {
            return "Optativa";
        } else if (op == 3) 
        {
            return "Formacao Livre";
        }
        std::cout << "[ERRO] Opcao invalida. Escolha 1, 2 ou 3.\n";
    }
}

void MenuDisciplina::exibir() 
{
    const SemestreAtual* semAtual = this->_estudante.getHistorico().getSemestreAtual();

    std::cout << "\n========================================================================\n";
    std::cout << "                      GERENCIAMENTO DE DISCIPLINAS                      \n";
    std::cout << "========================================================================\n";

    if (semAtual == nullptr || semAtual->getDisciplinas().empty()) 
    {
        std::cout << " Nenhuma disciplina cadastrada no semestre atual.\n";
    } else 
    {
        std::cout << std::left
                  << std::setw(4)  << "ID"
                  << std::setw(10) << "Codigo"
                  << std::setw(8)  << "Turma"
                  << std::setw(26) << "Nome"
                  << std::setw(8)  << "CH"
                  << std::setw(16) << "Tipo" << "\n";
        std::cout << "------------------------------------------------------------------------\n";

        const std::vector<Disciplina>& disciplinas = semAtual->getDisciplinas();
        for (std::vector<Disciplina>::const_iterator it = disciplinas.begin(); it != disciplinas.end(); ++it) 
        {
            std::cout << std::left
                      << std::setw(4)  << it->getId()
                      << std::setw(10) << it->getCodigo().substr(0, 8)
                      << std::setw(8)  << it->getCodigoTurma().substr(0, 6)
                      << std::setw(26) << it->getNome().substr(0, 24)
                      << std::setw(8)  << (std::to_string(it->getCargaHoraria()) + "h")
                      << std::setw(16) << it->getTipo() << "\n";
        }
    }

    std::cout << "========================================================================\n";
    std::cout << "1 - Criar nova disciplina\n";
    std::cout << "2 - Editar disciplina existente\n";
    std::cout << "3 - Apagar disciplina existente\n";
    std::cout << "0 - Voltar ao Menu Principal\n";
    std::cout << "========================================================================\n";
}

Menu* MenuDisciplina::processarEntrada() 
{
    while (true) 
    {
        int opcao = this->entradaSanitizada<int>("Escolha uma opcao: ");
        if (opcao == 1) 
        {
            this->fluxoCriarDisciplina();
            return new MenuDisciplina(this->_estudante, this->_gerenciadorArquivo);
        } else if (opcao == 2) 
        {
            this->fluxoEditarDisciplina();
            return new MenuDisciplina(this->_estudante, this->_gerenciadorArquivo);
        } else if (opcao == 3) 
        {
            this->fluxoApagarDisciplina();
            return new MenuDisciplina(this->_estudante, this->_gerenciadorArquivo);
        } else if (opcao == 0) 
        {
            return new MenuPrincipal(this->_estudante, this->_gerenciadorArquivo);
        }
        std::cout << "[ERRO] Opcao invalida. Escolha entre 0 e 3.\n";
    }
}