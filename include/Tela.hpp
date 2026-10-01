#ifndef TELA_HPP
#define TELA_HPP
 
#include <iostream>
#include <limits>
#include <string>
 
#include "Estudante.hpp"
 
/**
 * @file Tela.hpp
 * @brief Declaração da classe abstrata Tela.
 *
 * Camada 5 do sistema acadêmico (apresentação). Base de todas as telas
 * concretas (TelaMenuPrincipal, TelaPerfil, TelaPainel, TelaDisciplinas,
 * TelaAtividades, TelaFrequencia e TelaHistorico).
 */
 
/**
 * @class Tela
 * @brief Classe base abstrata para todas as telas do sistema.
 *
 * Define a interface polimórfica (executar() e getNome()) e fornece helpers
 * de I/O em terminal (cout/cin) compartilhados por herança.
 *
 * A Tela não é dona do Estudante: apenas mantém uma referência a ele.
 */
class Tela {
public:
    /**
     * @brief Constrói uma tela associada a um estudante.
     * @param estudante Referência ao estudante (a Tela não é dona do objeto).
     */
    Tela(Estudante& estudante);
 
    /**
     * @brief Destrutor virtual (permite destruição polimórfica).
     */
    virtual ~Tela() = default;
 
    /**
     * @brief Executa o fluxo da tela (virtual puro).
     * @return true para voltar ao menu principal.
     */
    virtual bool executar() = 0;
 
    /**
     * @brief Retorna o nome identificador da tela (virtual puro).
     * @return Nome da tela.
     */
    virtual std::string getNome() const = 0;
 
protected:
    /**
     * @brief Exibe um cabeçalho formatado com separadores.
     * @param titulo Título a ser exibido.
     */
    void exibirCabecalho(const std::string& titulo) const;
 
    /**
     * @brief Exibe uma mensagem informativa com o prefixo [INFO].
     * @param msg Mensagem a ser exibida.
     */
    void exibirMensagem(const std::string& msg) const;
 
    /**
     * @brief Exibe uma mensagem de erro com o prefixo [ERRO].
     * @param msg Mensagem de erro a ser exibida.
     */
    void exibirErro(const std::string& msg) const;
 
    /**
     * @brief Lê um inteiro do usuário, validando o intervalo [min, max].
     * @param min Menor valor aceito.
     * @param max Maior valor aceito.
     * @return Inteiro lido dentro do intervalo.
     */
    int lerOpcao(int min, int max) const;
 
    /**
     * @brief Lê um texto do usuário, exibindo um prompt.
     * @param prompt Texto exibido antes da leitura.
     * @return Texto digitado pelo usuário.
     */
    std::string lerTexto(const std::string& prompt) const;
 
    /**
     * @brief Lê um número double do usuário, exibindo um prompt.
     * @param prompt Texto exibido antes da leitura.
     * @return Número digitado pelo usuário.
     */
    double lerNumero(const std::string& prompt) const;
 
    /**
     * @brief Faz uma pergunta de sim/não ao usuário.
     * @param pergunta Pergunta a ser exibida.
     * @return true se o usuário confirmar; false caso contrário.
     */
    bool confirmar(const std::string& pergunta) const;
 
    Estudante& estudante_;  
};
 
#endif