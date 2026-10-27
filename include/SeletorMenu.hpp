#ifndef SELETORMENU_HPP
#define SELETORMENU_HPP

#include "Menu.hpp"
#include "Estudante.hpp"
#include "GerenciadorArquivo.hpp"

/**
 * @file SeletorMenu.hpp
 * @brief Declaração da classe SeletorMenu, que controla a navegação entre as telas.
 */

/**
 * @class SeletorMenu
 * @brief Controla o laço principal do programa, alternando entre as telas (Menu).
 *
 * Começa pelo MenuInicial. A cada volta do laço, exibe a tela atual, processa
 * a entrada do usuário e passa para a tela que ela devolver. O laço termina
 * quando uma tela devolve nullptr. O SeletorMenu é dono da tela atual e libera
 * cada tela assim que ela deixa de ser usada.
 */
class SeletorMenu 
{
private:
    Estudante& _estudante;                   ///< Estudante compartilhado entre as telas (não pertence ao SeletorMenu).
    GerenciadorArquivo& _gerenciadorArquivo; ///< Gerenciador de persistência compartilhado entre as telas (não pertence ao SeletorMenu).
    Menu* _menuAtual;                        ///< Tela atual, de propriedade do SeletorMenu. É nullptr quando o programa deve encerrar.

public:
    /**
     * @brief Constrói o seletor e cria a primeira tela (MenuInicial).
     * @param estudante          Estudante compartilhado entre as telas (deve viver mais que o SeletorMenu).
     * @param gerenciadorArquivo Gerenciador de arquivo compartilhado entre as telas (deve viver mais que o SeletorMenu).
     */
    SeletorMenu(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo);

    /**
     * @brief Destrutor. Libera a tela atual, se houver.
     */
    ~SeletorMenu();

    /**
     * @brief Executa o laço principal do programa.
     *
     * Enquanto houver uma tela atual, exibe a tela e processa a entrada. Se a
     * tela devolver um ponteiro diferente de si mesma, a tela antiga é liberada
     * e a devolvida passa a ser a atual. O laço termina quando a tela devolve
     * nullptr. Exceções lançadas pelas telas (por exemplo, EOF na entrada) não
     * são tratadas aqui e se propagam para quem chamou.
     */
    void executar();
};

#endif
