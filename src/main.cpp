#include "Estudante.hpp"
#include "GerenciadorArquivo.hpp"
#include "SeletorMenu.hpp"
#include "MenuInicial.hpp"
#include <memory>
#include <iostream>
#include <exception>

int main() 
{
    try 
    {
        std::unique_ptr<Estudante> estudante(nullptr);
        GerenciadorArquivo gerenciadorArquivo("savePerfilEstudante.txt");
        SeletorMenu seletor(new MenuInicial(estudante, gerenciadorArquivo));
        
        seletor.executar();
    } catch (const std::exception& e) 
    {
        std::cout << "\n[ERRO FATAL] " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}