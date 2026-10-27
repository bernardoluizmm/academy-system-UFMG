#include "Estudante.hpp"
#include "GerenciadorArquivo.hpp"
#include "SeletorMenu.hpp"

int main() 
{
        Estudante estudante;
        GerenciadorArquivo gerenciadorArquivo("savePerfilEstudante.txt");
        SeletorMenu seletor(estudante, gerenciadorArquivo);
}