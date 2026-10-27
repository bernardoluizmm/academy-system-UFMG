#ifndef SELETORMENU_HPP
#define SELETORMENU_HPP

#include "Menu.hpp"
#include "Estudante.hpp"
#include "GerenciadorArquivo.hpp"

class SeletorMenu 
{
private:
    Estudante& _estudante;
    GerenciadorArquivo& _gerenciadorArquivo;
    Menu* _menuAtual;

public:
    SeletorMenu(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo);
    ~SeletorMenu();

    void executar();
};

#endif