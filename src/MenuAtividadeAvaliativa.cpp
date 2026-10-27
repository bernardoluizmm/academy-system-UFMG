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
Menu* MenuAtividadeAvaliativa::processarEntrada() 
{
    while (true) 
    {
        int opcao = this->entradaSanitizada<int>("Escolha uma opcao: ");
        if (opcao == 1) 
        {
            this->fluxoCriarAtividade();
            return new MenuAtividadeAvaliativa(this->_estudante, this->_gerenciadorArquivo);
        } else if (opcao == 2) 
        {
            this->fluxoLancarNota();
            return new MenuAtividadeAvaliativa(this->_estudante, this->_gerenciadorArquivo);
        } else if (opcao == 3) 
        {
            this->fluxoEditarAtividade();
            return new MenuAtividadeAvaliativa(this->_estudante, this->_gerenciadorArquivo);
        } else if (opcao == 4) 
        {
            this->fluxoApagarAtividade();
            return new MenuAtividadeAvaliativa(this->_estudante, this->_gerenciadorArquivo);
        } else if (opcao == 0) 
        {
            return new MenuPrincipal(this->_estudante, this->_gerenciadorArquivo);
        }
        std::cout << "[ERRO] Opcao invalida. Escolha entre 0 e 4.\n";
    }
}
