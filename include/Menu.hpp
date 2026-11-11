#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>

/**
 * @file Menu.hpp
 * @brief Declaracao da classe abstrata Menu, base desacoplada de todas as telas do sistema.
 */

/**
 * @class Menu
 * @brief Classe base abstrata das telas de interacao via terminal.
 *
 * Totalmente desacoplada das classes de dominio: oferece apenas o contrato polimorfico
 * de exibicao e transicao de telas (para uso na pilha do SeletorMenu) e os utilitarios
 * de leitura e sanitizacao de entrada.
 */
class Menu 
{
protected:
    /**
     * @brief Le uma linha do terminal e a converte para o tipo T, repetindo ate ser valida.
     *
     * @tparam T       Tipo esperado da entrada (ex: int, float, std::string).
     * @param mensagem Texto exibido antes de cada leitura.
     * @return Valor lido e convertido.
     * @throws std::runtime_error Se o fluxo de entrada terminar (EOF) antes de uma entrada valida.
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
     * @brief Pede ao usuario que confirme o cadastro de um dado que nao podera ser alterado depois.
     * @return true se o usuario digitou 1 (Sim); false se digitou 2 (Nao).
     */
    bool confirmarDadoImutavel();

public:
    /**
     * @brief Construtor padrao.
     */
    Menu();

    /**
     * @brief Destrutor virtual, para permitir a destruicao correta via ponteiro de Menu.
     */
    virtual ~Menu();

    /**
     * @brief Exibe o conteudo da tela no terminal.
     */
    virtual void exibir() = 0;

    /**
     * @brief Le a entrada do usuario e decide a transicao na pilha de menus.
     * @return Ponteiro para uma nova tela a empilhar, @c this para permanecer na tela atual,
     *         ou @c nullptr para desempilhar a tela atual e voltar a tela anterior.
     */
    virtual Menu* processarEntrada() = 0;

    /**
     * @brief Indica ao SeletorMenu se, ao avancar para uma nova tela, a pilha anterior deve ser substituida.
     * @return @c true se a nova tela deve substituir toda a pilha anterior (ex.: entrada no MenuPrincipal);
     *         @c false (padrao) para apenas empilhar a nova tela sobre a atual.
     */
    virtual bool substituirPilhaAoTransicionar() const;
};

/**
 * @brief Especializacao de Menu::entradaSanitizada para std::string.
 */
template <>
std::string Menu::entradaSanitizada<std::string>(const std::string& mensagem);

#endif