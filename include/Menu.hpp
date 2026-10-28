#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "Estudante.hpp"
#include "GerenciadorArquivo.hpp"

/**
 * @file Menu.hpp
 * @brief Declaração da classe abstrata Menu, base de todas as telas do sistema.
 */

/**
 * @class Menu
 * @brief Classe base abstrata das telas de interação via terminal.
 *
 * Guarda referências ao Estudante e ao GerenciadorArquivo, que são
 * compartilhados entre as telas (o Menu não é dono desses objetos).
 * Também oferece utilitários de leitura de entrada. Cada tela concreta
 * implementa exibir() e processarEntrada(), que devolve a próxima tela.
 */
class Menu 
{
protected:
    Estudante& _estudante;                   ///< Estudante manipulado pelas telas (não pertence ao Menu).
    GerenciadorArquivo& _gerenciadorArquivo; ///< Gerenciador de persistência do perfil (não pertence ao Menu).

    /**
     * @brief Lê uma linha do terminal e a converte para o tipo T, repetindo até ser válida.
     *
     * A entrada só é aceita se a linha contiver exatamente um valor do tipo T,
     * sem caracteres sobrando (espaços no final são ignorados). Em caso de
     * entrada inválida, exibe uma mensagem de erro e pede novamente.
     * Para std::string existe uma especialização que devolve a linha sem
     * espaços nas pontas e não aceita linha vazia.
     *
     * @tparam T       Tipo esperado da entrada (ex: int, float, std::string).
     * @param mensagem Texto exibido antes de cada leitura.
     * @return Valor lido e convertido.
     * @throws std::runtime_error Se o fluxo de entrada terminar (EOF) antes de uma entrada válida.
     */
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

    /**
     * @brief Pede ao usuário que confirme o cadastro de um dado que não poderá ser alterado depois.
     *
     * Repete a pergunta até receber 1 ou 2.
     *
     * @return true se o usuário digitou 1 (Sim); false se digitou 2 (Não).
     */
    bool confirmarDadoImutavel();

public:
    /**
     * @brief Constrói um menu associado ao estudante e ao gerenciador de arquivo.
     * @param estudante          Estudante manipulado pela tela (deve viver mais que o Menu).
     * @param gerenciadorArquivo Gerenciador usado para salvar e carregar o perfil (deve viver mais que o Menu).
     */
    Menu(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo);

    /**
     * @brief Destrutor virtual, para permitir a destruição correta via ponteiro de Menu.
     */
    virtual ~Menu();

    /**
     * @brief Exibe o conteúdo da tela no terminal.
     */
    virtual void exibir() = 0;

    /**
     * @brief Lê a entrada do usuário e decide qual será a próxima tela.
     * @return Ponteiro para a próxima tela a ser exibida.
     */
    virtual Menu* processarEntrada() = 0;
};

/**
 * @brief Especialização de Menu::entradaSanitizada para std::string.
 *
 * Remove espaços, tabulações e quebras de linha das pontas e rejeita linhas vazias.
 *
 * @param mensagem Texto exibido antes de cada leitura.
 * @return Texto digitado, sem espaços nas pontas.
 * @throws std::runtime_error Se o fluxo de entrada terminar (EOF).
 */
    template <>
    std::string Menu::entradaSanitizada<std::string>(const std::string& mensagem);

#endif

#endif