#include "Estudante.hpp"
#include "GerenciadorArquivo.hpp"
#include "SeletorMenu.hpp"

#include <memory>

int main() 
{
    std::unique_ptr<Estudante> estudante(nullptr);
    GerenciadorArquivo gerenciadorArquivo("savePerfilEstudante.txt");
    SeletorMenu seletor(new MenuInicial(estudante, gerenciadorArquivo));
        
    seletor.executar();

    return 0;
}