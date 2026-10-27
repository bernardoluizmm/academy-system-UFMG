#include "MenuCarregarUsuario.hpp"
#include "MenuPrincipal.hpp"
#include "MenuInicial.hpp"
#include <iostream>
#include <stdexcept>

MenuCarregarUsuario::MenuCarregarUsuario(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo)
    : Menu(estudante, gerenciadorArquivo) {}

MenuCarregarUsuario::~MenuCarregarUsuario() {}

