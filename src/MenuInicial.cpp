#include "MenuInicial.hpp"
#include "MenuCadastroUsuario.hpp"
#include "MenuCarregarUsuario.hpp"
#include <iostream>

MenuInicial::MenuInicial(std::unique_ptr<Estudante>& estudante, GerenciadorArquivo& gerenciadorArquivo)
    : Menu(), _estudante(estudante), _gerenciadorArquivo(gerenciadorArquivo) {}

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

Menu* MenuInicial::processarEntrada() 
{
    while (true) 
    {
        int opcao = this->entradaSanitizada<int>("Escolha uma opcao: ");

        switch (opcao) 
        {
            case 0:
                std::cout << "Encerrando o sistema...\n";
                return nullptr;
            case 1:
                return new MenuCarregarUsuario(this->_estudante, this->_gerenciadorArquivo);
            case 2:
                return new MenuCadastroUsuario(this->_estudante, this->_gerenciadorArquivo);
            default:
                std::cout << "[ERRO] Opcao invalida. Escolha 1, 2 ou 0.\n";
                break;
        }
    }
}