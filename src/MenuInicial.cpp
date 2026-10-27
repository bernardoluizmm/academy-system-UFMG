#include "MenuInicial.hpp"
#include "MenuCadastroUsuario.hpp"
#include "MenuCarregarUsuario.hpp"
#include <iostream>

MenuInicial::MenuInicial(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo)
    : Menu(estudante, gerenciadorArquivo) {}

MenuInicial::~MenuInicial() {}

void MenuInicial::exibir() 
{
    std::cout << "\n======================================================\n";
    std::cout << "       SISTEMA DE GESTAO ACADEMICA - UFMG (PDS II)    \n";
    std::cout << "======================================================\n";
    std::cout << "1 - Carregar perfil salvo\n";
    std::cout << "2 - Criar novo perfil de estudante\n";
    std::cout << "0 - Sair do programa\n";
    std::cout << "======================================================\n";
}