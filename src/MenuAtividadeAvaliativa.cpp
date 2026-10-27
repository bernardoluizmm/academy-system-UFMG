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
