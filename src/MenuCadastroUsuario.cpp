#include "MenuCadastroUsuario.hpp"
#include "MenuPrincipal.hpp"
#include "Semestre.hpp"
#include <iostream>
#include <vector>
#include <stdexcept>

MenuCadastroUsuario::MenuCadastroUsuario(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo)
    : Menu(estudante, gerenciadorArquivo) 
{}

MenuCadastroUsuario::~MenuCadastroUsuario() 
{}
void MenuCadastroUsuario::exibir() 
{
    std::cout << "\n======================================================\n";
    std::cout << "             CADASTRO DE NOVO PERFIL                  \n";
    std::cout << "======================================================\n";
    std::cout << "Atencao: Os dados informados nesta etapa sao definitivos.\n";
}
