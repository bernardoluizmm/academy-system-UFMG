#include "SeletorMenu.hpp"

SeletorMenu::SeletorMenu(Menu* menuInicial)
{
    if (menuInicial != nullptr) 
    {
        this->_pilhaMenus.push(menuInicial);
    }
}

SeletorMenu::~SeletorMenu() 
{
    this->limparPilha();
}

void SeletorMenu::limparPilha() 
{
    while (!this->_pilhaMenus.empty()) 
    {
        delete this->_pilhaMenus.top();
        this->_pilhaMenus.pop();
    }
}

void SeletorMenu::executar() 
{
    while (!this->_pilhaMenus.empty()) 
    {
        Menu* menuAtual = this->_pilhaMenus.top();
        menuAtual->exibir();
        Menu* proximoMenu = menuAtual->processarEntrada();

        if (proximoMenu == nullptr) 
        {
            delete menuAtual;
            this->_pilhaMenus.pop();
        } else if (proximoMenu != menuAtual) 
        {
            if (menuAtual->substituirPilhaAoTransicionar()) 
            {
                this->limparPilha();
            }
            this->_pilhaMenus.push(proximoMenu);
        }
    }
}