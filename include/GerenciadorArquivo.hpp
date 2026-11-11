#ifndef GERENCIADORARQUIVO_HPP
#define GERENCIADORARQUIVO_HPP

#include <string>
#include <vector>
#include <memory>
#include "Estudante.hpp"

/**
 * @file GerenciadorArquivo.hpp
 * @brief Declaracao da classe GerenciadorArquivo, responsavel pela persistencia do perfil.
 */

/**
 * @class GerenciadorArquivo
 * @brief Salva e carrega o perfil do Estudante em um arquivo de texto.
 *
 * O arquivo e composto por registros, um por linha, com campos separados
 * por '|'. O primeiro campo identifica o tipo do registro (ESTUDANTE, CURSO,
 * SEMESTRE_CONSOLIDADO, SEMESTRE_ATUAL, DISCIPLINA e ATIVIDADE). Registros
 * de ATIVIDADE pertencem a ultima DISCIPLINA lida.
 */
class GerenciadorArquivo 
{
private:
    std::string _nomeArquivo; ///< Caminho do arquivo de perfil.

    /**
     * @brief Divide uma linha em campos usando um delimitador.
     * @param linha       Linha a ser dividida.
     * @param delimitador Caractere que separa os campos.
     * @return Vetor com os campos, na ordem em que aparecem.
     */
    static std::vector<std::string> dividirLinha(const std::string& linha, char delimitador);

public:
    /**
     * @brief Constroi o gerenciador para um arquivo.
     * @param nomeArquivo Caminho do arquivo de perfil (padrao: "perfil_estudante.txt").
     */
    GerenciadorArquivo(const std::string& nomeArquivo = "perfil_estudante.txt");

    /**
     * @brief Verifica se o arquivo de perfil existe e pode ser lido.
     * @return true se o arquivo existe; false caso contrario.
     */
    bool arquivoExiste() const;

    /**
     * @brief Salva o estudante no arquivo, sobrescrevendo o conteudo anterior.
     * @param estudante Estudante a ser salvo (serializado via Estudante::serializar()).
     * @throws std::runtime_error Se o arquivo nao puder ser aberto para escrita.
     */
    void salvar(const Estudante& estudante) const;

    /**
     * @brief Carrega o estudante a partir do arquivo aplicando RAII via std::unique_ptr.
     * @return Ponteiro inteligente contendo o Estudante reconstruido com os dados do arquivo.
     * @throws std::runtime_error Se o arquivo nao for encontrado, nao puder ser aberto ou estiver incompleto.
     */
    std::unique_ptr<Estudante> carregar() const;

    /**
     * @brief Retorna o caminho do arquivo de perfil.
     * @return Nome do arquivo usado por este gerenciador.
     */
    std::string getNomeArquivo() const;
};

#endif