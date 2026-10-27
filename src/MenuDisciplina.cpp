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