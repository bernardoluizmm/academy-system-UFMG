#include "MenuPrincipal.hpp"
#include "MenuDisciplina.hpp"
#include "MenuAtividadeAvaliativa.hpp"
#include "MenuFrequencia.hpp"
#include "MenuDetalhamentoDisciplina.hpp"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <vector>

MenuPrincipal::MenuPrincipal(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo)
    : Menu(estudante, gerenciadorArquivo) 
{}

MenuPrincipal::~MenuPrincipal() 
{}