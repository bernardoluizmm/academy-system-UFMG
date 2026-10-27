/**
 * @file MenuInicial.hpp
 * @brief Declaração da classe MenuInicial para a tela de abertura do sistema.
 */

#ifndef MENUINICIAL_HPP
#define MENUINICIAL_HPP

#include "Menu.hpp"

/**
 * @class MenuInicial
 * @brief Representa o menu de entrada exibido ao iniciar a aplicação.
 * @details Herda da classe abstrata Menu e oferece ao usuário as opções de carregar
 *          um perfil salvo anteriormente, iniciar o cadastro de um novo estudante
 *          ou encerrar a execução do programa.
 */
class MenuInicial : public Menu 
{
public:
    /**
     * @brief Construtor da classe MenuInicial.
     * @param estudante Referência para o objeto Estudante em memória.
     * @param gerenciadorArquivo Referência para o gerenciador de persistência em arquivo.
     */
    MenuInicial(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo);

    /**
     * @brief Destrutor virtual da classe MenuInicial.
     */
    ~MenuInicial() override;

    /**
     * @brief Exibe no terminal o cabeçalho do sistema e as opções iniciais disponíveis.
     */
    virtual void exibir() override;

    /**
     * @brief Lê e valida(validação por tipo de entrada apenas) a opção escolhida pelo usuário, realizando, ao final, a transição de tela. Podem ocorrer cin intermediários até a troca de tela.
     * @return Ponteiro para `MenuCarregarUsuario` (opção 1), `MenuCadastroUsuario` (opção 2)
     *         ou `nullptr` (opção 0) para sinalizar o encerramento do sistema.
     */
    virtual Menu* processarEntrada() override;
};

#endif