#ifndef GERENCIADORPERFIL_HPP
#define GERENCIADORPERFIL_HPP
 
#include <string>
 
#include "Estudante.hpp"
 
/**
 * @file GerenciadorPerfil.hpp
 * @brief Declaração da classe GerenciadorPerfil.
 *
 * Camada 4 do sistema acadêmico (depende de Estudante e, transitivamente,
 * de Curso, SemestreAtual, SemestreConsolidado, Disciplina etc.).
 */
 
/**
 * @class GerenciadorPerfil
 * @brief Classe utilitária (sem estado) para persistência do perfil em arquivo .txt.
 *
 * Serializa e desserializa o perfil completo do estudante em um arquivo de
 * texto tabular, com campos separados por ponto e vírgula (`;`).
 * Erros são sinalizados por retorno `bool` (true = sucesso, false = erro).
 */
class GerenciadorPerfil {
public:
    /**
     * @brief Serializa o perfil completo do estudante em um arquivo .txt.
     * @param estudante Estudante a ser salvo.
     * @param caminho   Caminho do arquivo de destino.
     * @return true se o arquivo foi gravado com sucesso;
     *         false em caso de erro de I/O.
     */
    static bool salvarPerfil(const Estudante& estudante, const std::string& caminho);
 
    /**
     * @brief Lê, valida e desserializa o perfil a partir de um arquivo .txt.
     * @param estudante Estudante que receberá os dados carregados.
     * @param caminho   Caminho do arquivo de origem.
     * @return true se o perfil foi carregado com sucesso;
     *         false se o arquivo for inválido, corrompido ou inexistente.
     */
    static bool carregarPerfil(Estudante& estudante, const std::string& caminho);
 
    /**
     * @brief Verifica se o arquivo possui formato válido, sem carregar os dados.
     * @param caminho Caminho do arquivo a ser verificado.
     * @return true se o formato é válido; false caso contrário.
     */
    static bool validarFormato(const std::string& caminho);
};
 
#endif 
 