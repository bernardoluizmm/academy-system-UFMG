#ifndef SELETORMENU_HPP
#define SELETORMENU_HPP

#include <stack>
#include "Menu.hpp"

/**
 * @file SeletorMenu.hpp
 * @brief Declaracao da classe SeletorMenu, que controla a navegacao entre as telas via pilha (std::stack).
 */

/**
 * @class SeletorMenu
 * @brief Controla o laco principal do programa utilizando uma pilha de telas (LIFO).
 *
 * Totalmente desacoplado de Estudante e GerenciadorArquivo: gerencia apenas objetos
 * polimorficos do tipo Menu*. Empilha novas telas ao avancar e desempilha ao receber nullptr.
 */
class SeletorMenu 
{
private:
    std::stack<Menu*> _pilhaMenus; ///< Pilha de telas ativas, onde o topo e a tela em exibicao.

    /**
     * @brief Desaloca e remove todas as telas presentes na pilha.
     */
    void limparPilha();

public:
    /**
     * @brief Constroi o seletor empilhando a primeira tela do sistema.
     * @param menuInicial Ponteiro para a tela inicial alocada dinamicamente.
     */
    explicit SeletorMenu(Menu* menuInicial);

    /**
     * @brief Destrutor. Libera todas as telas restantes na pilha (garantia RAII).
     */
    ~SeletorMenu();

    /**
     * @brief Executa o laco principal do programa enquanto a pilha nao estiver vazia.
     */
    void executar();
};

#endif