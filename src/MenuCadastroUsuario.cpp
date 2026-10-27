#include "MenuCadastroUsuario.hpp"
#include "MenuPrincipal.hpp"
#include "Semestre.hpp"
#include <iostream>
#include <vector>
#include <stdexcept>

MenuCadastroUsuario::MenuCadastroUsuario(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo)
    : Menu(estudante, gerenciadorArquivo) 
{}

MenuCadastroUsuario::~MenuCadastroUsuario() 
{}

