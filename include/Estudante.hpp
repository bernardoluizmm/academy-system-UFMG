#ifndef ESTUDANTE_HPP
#define ESTUDANTE_HPP
 
#include <string>
 
#include "Curso.hpp"
#include "SemestreAtual.hpp"
 
/**
 * @file Estudante.hpp
 * @brief Declaração da classe Estudante.
 *
 * Camada 3 do sistema acadêmico (depende de Curso e SemestreAtual).
 */
 
/**
 * @class Estudante
 * @brief Representa o estudante e fornece acesso ao seu curso e ao semestre atual.
 *
 * O Estudante é dono do Curso e do SemestreAtual (composição por valor).
 * Os acessores não-const permitem que as telas e o GerenciadorPerfil
 * modifiquem esses objetos diretamente.
 */
class Estudante {
public:
    /**
     * @brief Constrói um estudante.
     * @param nome              Nome do estudante.
     * @param curso             Curso do estudante (copiado/movido para o objeto).
     * @param semestreIngresso  Semestre de ingresso (ex: "2024/01").
     * @param semestreAtual     Semestre em curso (copiado/movido para o objeto).
     */
    Estudante(std::string nome, Curso curso, std::string semestreIngresso,
              SemestreAtual semestreAtual);
 
    /**
     * @brief Retorna o nome do estudante.
     * @return Nome do estudante.
     */
    std::string getNome() const;
 
    /**
     * @brief Altera o nome do estudante.
     * @param nome Novo nome.
     */
    void setNome(const std::string& nome);
 
    /**
     * @brief Retorna o semestre de ingresso.
     * @return Semestre de ingresso (ex: "2024/01").
     */
    std::string getSemestreIngresso() const;
 
    /**
     * @brief Altera o semestre de ingresso.
     * @param semestre Novo semestre de ingresso.
     */
    void setSemestreIngresso(const std::string& semestre);
 
    /**
     * @brief Acesso somente-leitura ao curso.
     * @return Referência constante ao Curso.
     */
    const Curso& getCurso() const;
 
    /**
     * @brief Acesso mutável ao curso.
     * @return Referência ao Curso.
     */
    Curso& getCurso();
 
    /**
     * @brief Acesso somente-leitura ao semestre atual.
     * @return Referência constante ao SemestreAtual.
     */
    const SemestreAtual& getSemestreAtual() const;
 
    /**
     * @brief Acesso mutável ao semestre atual.
     * @return Referência ao SemestreAtual.
     */
    SemestreAtual& getSemestreAtual();
 
private:
    std::string nome_;              
    std::string semestreIngresso_;  
    Curso curso_;                   
    SemestreAtual semestreAtual_;   
};
 
#endif // ESTUDANTE_HPP
 