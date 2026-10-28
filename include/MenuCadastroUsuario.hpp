#ifndef MENUCADASTROUSUARIO_HPP
#define MENUCADASTROUSUARIO_HPP

#include "Menu.hpp"

/**
 * @file MenuCadastroUsuario.hpp
 * @brief Declaração da tela de cadastro de um novo perfil de estudante.
 */

/**
 * @class MenuCadastroUsuario
 * @brief Tela que cadastra o perfil do estudante na primeira execução do sistema.
 *
 * Coleta o nome, o curso, o semestre de ingresso e o semestre atual. Para
 * cada semestre anterior entre o ingresso e o semestre atual, pede os dados
 * do semestre consolidado (se foi trancado, o NSG e as horas integralizadas
 * por categoria). Os dados informados são definitivos, então cada etapa pede
 * confirmação antes de ser gravada.
 */
class MenuCadastroUsuario : public Menu 
{
public:
    /**
     * @brief Constrói a tela de cadastro.
     * @param estudante          Estudante que receberá os dados cadastrados (deve viver mais que o Menu).
     * @param gerenciadorArquivo Gerenciador de arquivo repassado às telas seguintes (deve viver mais que o Menu).
     */
    MenuCadastroUsuario(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo);

    /**
     * @brief Destrutor.
     */
    virtual ~MenuCadastroUsuario() override;

    /**
     * @brief Exibe o título da tela e o aviso de que os dados são definitivos.
     */
    virtual void exibir() override;

    /**
     * @brief Conduz todo o cadastro e devolve a tela principal.
     *
     * Cada campo é lido novamente até ser aceito pelo modelo (entradas
     * inválidas mostram a mensagem de erro e pedem de novo). Se o usuário
     * não confirmar uma etapa, ela é repetida. Ao final, o estudante cadastrado
     * substitui o estudante do menu.
     *
     * @return Nova tela MenuPrincipal, alocada com new. Quem recebe o ponteiro
     *         passa a ser responsável por liberá-lo.
     * @throws std::runtime_error Se o fluxo de entrada terminar (EOF) durante o cadastro.
     */
    virtual Menu* processarEntrada() override;
};

#endif