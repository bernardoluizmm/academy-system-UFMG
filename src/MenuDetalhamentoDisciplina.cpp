#include "MenuDetalhamentoDisciplina.hpp"
#include "MenuPrincipal.hpp"
#include "SemestreAtual.hpp"
#include "AtividadeAvaliativa.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

MenuDetalhamentoDisciplina::MenuDetalhamentoDisciplina(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo)
    : Menu(estudante, gerenciadorArquivo) 
{
}

MenuDetalhamentoDisciplina::~MenuDetalhamentoDisciplina() 
{
}