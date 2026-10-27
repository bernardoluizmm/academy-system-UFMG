#include "MenuInicial.hpp"
#include "MenuCadastroUsuario.hpp"
#include "MenuCarregarUsuario.hpp"
#include <iostream>

MenuInicial::MenuInicial(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo)
    : Menu(estudante, gerenciadorArquivo) {}

MenuInicial::~MenuInicial() {}