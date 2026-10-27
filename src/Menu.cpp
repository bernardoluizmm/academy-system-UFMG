#include "Menu.hpp"
#include <iostream>

Menu::Menu(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo)
    : _estudante(estudante), _gerenciadorArquivo(gerenciadorArquivo) 
{
}

Menu::~Menu() 
{
}
template <>
std::string Menu::entradaSanitizada<std::string>(const std::string& mensagem)
{
    std::string linha;

    while (true)
    {
        std::cout << mensagem;

        if (!std::getline(std::cin, linha))
        {
            std::cin.clear();
            throw std::runtime_error("Erro fatal: Fim inesperado do fluxo (EOF). O arquivo nao contem todas as entradas necessarias.");
        }

        size_t inicio = linha.find_first_not_of(" \t\r\n");
        if (inicio != std::string::npos)
        {
            size_t fim = linha.find_last_not_of(" \t\r\n");
            return linha.substr(inicio, fim - inicio + 1);
        }

        std::cout << "Erro: Tipo de entrada incorreto. Tente novamente.\n";
    }
}
bool Menu::confirmarDadoImutavel() 
{
    while (true) 
    {
        int entrada = this->entradaSanitizada<int>("Voce tem certeza disso? Essa informacao nao podera ser alterada depois (1 - Sim / 2 - Nao): ");
        if (entrada == 1) 
        {
            return true;
        } else if (entrada == 2) 
        {
            return false;
        }
        std::cout << "[ERRO] Opcao invalida. Digite 1 para Sim ou 2 para Nao.\n";
    }
}
