#include "MenuAtividadeAvaliativa.hpp"
#include "MenuPrincipal.hpp"
#include "SemestreAtual.hpp"
#include "AtividadeAvaliativa.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <stdexcept>

MenuAtividadeAvaliativa::MenuAtividadeAvaliativa(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo)
    : Menu(estudante, gerenciadorArquivo) 
{
}

MenuAtividadeAvaliativa::~MenuAtividadeAvaliativa() 
{
}

void MenuAtividadeAvaliativa::exibir() 
{
    const SemestreAtual* semAtual = this->_estudante.getHistorico().getSemestreAtual();

    std::cout << "\n========================================================================\n";
    std::cout << "                 GERENCIAMENTO DE ATIVIDADES AVALIATIVAS                \n";
    std::cout << "========================================================================\n";

    if (semAtual == nullptr || semAtual->getDisciplinas().empty()) 
    {
        std::cout << " Nenhuma disciplina cadastrada no semestre atual.\n";
    } else 
    {
        const std::vector<Disciplina>& disciplinas = semAtual->getDisciplinas();
        for (std::vector<Disciplina>::const_iterator it = disciplinas.begin(); it != disciplinas.end(); ++it) 
        {
            this->exibirAtividadesDaDisciplina(*it);
        }
    }

    std::cout << "\n========================================================================\n";
    std::cout << "1 - Criar nova atividade avaliativa\n";
    std::cout << "2 - Lancar / Atualizar nota obtida em atividade\n";
    std::cout << "3 - Editar atividade avaliativa existente\n";
    std::cout << "4 - Apagar atividade avaliativa existente\n";
    std::cout << "0 - Voltar ao Menu Principal\n";
    std::cout << "========================================================================\n";
}