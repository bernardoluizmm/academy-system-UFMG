#include "MenuDisciplina.hpp"
#include "MenuPrincipal.hpp"
#include "SemestreAtual.hpp"
#include "Disciplina.hpp"
#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>

MenuDisciplina::MenuDisciplina(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo)
    : Menu(estudante, gerenciadorArquivo) 
{}

MenuDisciplina::~MenuDisciplina() {}