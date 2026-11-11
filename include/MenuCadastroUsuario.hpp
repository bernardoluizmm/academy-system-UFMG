#ifndef MENUCADASTROUSUARIO_HPP
#define MENUCADASTROUSUARIO_HPP

#include <memory>
#include "Menu.hpp"
#include "Estudante.hpp"
#include "GerenciadorArquivo.hpp"

/**
 * @file MenuCadastroUsuario.hpp
 * @brief Declaracao da tela de cadastro de um novo perfil de estudante.
 */

/**
 * @class MenuCadastroUsuario
 * @brief Tela que coleta e valida todos os dados cadastrais e instancia o Estudante via RAII.
 */
class MenuCadastroUsuario : public Menu 
{
private:
    std::unique_ptr<Estudante>& _estudante;  ///< Ponteiro inteligente do estudante da sessao.
    GerenciadorArquivo& _gerenciadorArquivo; ///< Gerenciador de arquivo repassado ao MenuPrincipal.

public:
    MenuCadastroUsuario(std::unique_ptr<Estudante>& estudante, GerenciadorArquivo& gerenciadorArquivo);

    virtual void exibir() override;
    virtual Menu* processarEntrada() override;
    virtual bool substituirPilhaAoTransicionar() const override;
};

#endif