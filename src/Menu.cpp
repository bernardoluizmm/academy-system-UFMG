#include "Menu.hpp"
#include <iostream>

Menu::Menu(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo)
    : _estudante(estudante), _gerenciadorArquivo(gerenciadorArquivo) 
{
}

Menu::~Menu() 
{
}
