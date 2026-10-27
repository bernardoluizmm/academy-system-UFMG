#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "Estudante.hpp"
#include "GerenciadorArquivo.hpp"

class Menu 
{
protected:
    Estudante& _estudante;
    GerenciadorArquivo& _gerenciadorArquivo;

    template <typename T>
    T entradaSanitizada(const std::string& mensagem)
    {
        T valor;
        std::string linha;

        while (true)
        {
            std::cout << mensagem;

            if (!std::getline(std::cin, linha))
            {
                std::cin.clear(); 
                throw std::runtime_error("Erro fatal: Fim inesperado do fluxo (EOF). O arquivo nao contem todas as entradas necessarias."); 
            }

            std::stringstream fluxo(linha);
            
            if (fluxo >> valor)
            {
                fluxo >> std::ws; 
                
                if (fluxo.eof())
                {
                    return valor;
                }
            }
            
            std::cout << "Erro: Tipo de entrada incorreto. Tente novamente.\n";
        }
    }

    bool confirmarDadoImutavel();

public:
    Menu(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo);
    virtual ~Menu();

    virtual void exibir() = 0;
    virtual Menu* processarEntrada() = 0;
};

    template <>
    std::string Menu::entradaSanitizada<std::string>(const std::string& mensagem);

#endif