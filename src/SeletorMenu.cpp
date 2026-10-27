#include "SeletorMenu.hpp"
#include "MenuInicial.hpp"

SeletorMenu::SeletorMenu(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo)
    : _estudante(estudante),
      _gerenciadorArquivo(gerenciadorArquivo),
      _menuAtual(new MenuInicial(estudante, gerenciadorArquivo)) {}

SeletorMenu::~SeletorMenu() 
{
    delete this->_menuAtual;
    this->_menuAtual = nullptr;
}

void SeletorMenu::executar() 
{
    while (this->_menuAtual != nullptr) 
    {
        this->_menuAtual->exibir();
        Menu* proximoMenu = this->_menuAtual->processarEntrada();
        if (proximoMenu != this->_menuAtual) 
        {
            delete this->_menuAtual;
            this->_menuAtual = proximoMenu;
        }
    }
}