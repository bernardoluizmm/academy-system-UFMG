#include "MenuCarregarUsuario.hpp"
#include "MenuPrincipal.hpp"
#include <iostream>
#include <stdexcept>

MenuCarregarUsuario::MenuCarregarUsuario(std::unique_ptr<Estudante>& estudante, GerenciadorArquivo& gerenciadorArquivo)
    : Menu(), _estudante(estudante), _gerenciadorArquivo(gerenciadorArquivo) {}

bool MenuCarregarUsuario::substituirPilhaAoTransicionar() const 
{
    return true;
}

void MenuCarregarUsuario::exibir() 
{
    std::cout << "\n--- CARREGAR PERFIL DE USUARIO ---\n";
}

Menu* MenuCarregarUsuario::processarEntrada() 
{
    try 
    {
        this->_estudante = this->_gerenciadorArquivo.carregar();
        std::cout << "\nSeja muito bem-vindo " << this->_estudante->getNome() << "!\n";
        return new MenuPrincipal(*(this->_estudante), this->_gerenciadorArquivo);
    } catch (const std::exception& e) 
    {
        std::cout << "[ERRO] Nao foi possivel carregar o perfil: " << e.what() << "\n";
        std::cout << "Retornando ao Menu Inicial...\n";
        return nullptr;
    }
}