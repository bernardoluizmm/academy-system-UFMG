#ifndef GERENCIADORARQUIVO_HPP
#define GERENCIADORARQUIVO_HPP

#include <string>
#include <vector>
#include "Estudante.hpp"

/**
 * @file GerenciadorArquivo.hpp
 * @brief Declaração da classe GerenciadorArquivo, responsável pela persistência do perfil.
 */

/**
 * @class GerenciadorArquivo
 * @brief Salva e carrega o perfil do Estudante em um arquivo de texto.
 *
 * O arquivo é composto por registros, um por linha, com campos separados
 * por '|'. O primeiro campo identifica o tipo do registro (ESTUDANTE, CURSO,
 * SEMESTRE_CONSOLIDADO, SEMESTRE_ATUAL, DISCIPLINA e ATIVIDADE). Registros
 * de ATIVIDADE pertencem à última DISCIPLINA lida.
 */
class GerenciadorArquivo 
{
private:
    std::string _nomeArquivo; ///< Caminho do arquivo de perfil.

    /**
     * @brief Divide uma linha em campos usando um delimitador.
     * @param linha       Linha a ser dividida.
     * @param delimitador Caractere que separa os campos.
     * @return Vetor com os campos, na ordem em que aparecem. Campos vazios são mantidos,
     *         e uma linha sem delimitador resulta em um único campo.
     */
    static std::vector<std::string> dividirLinha(const std::string& linha, char delimitador);

public:
    /**
     * @brief Constrói o gerenciador para um arquivo.
     * @param nomeArquivo Caminho do arquivo de perfil (padrão: "perfil_estudante.txt").
     */
    GerenciadorArquivo(const std::string& nomeArquivo = "perfil_estudante.txt");

    /**
     * @brief Verifica se o arquivo de perfil existe e pode ser lido.
     * @return true se o arquivo existe; false caso contrário.
     */
    bool arquivoExiste() const;

    /**
     * @brief Salva o estudante no arquivo, sobrescrevendo o conteúdo anterior.
     * @param estudante Estudante a ser salvo (serializado via Estudante::serializar()).
     * @throws std::runtime_error Se o arquivo não puder ser aberto para escrita.
     */
    void salvar(const Estudante& estudante) const;

    /**
     * @brief Carrega o estudante a partir do arquivo.
     *
     * Linhas vazias, registros desconhecidos e registros com campos faltando
     * são ignorados.
     *
     * @return Estudante reconstruído com os dados do arquivo.
     * @throws std::runtime_error Se o arquivo não for encontrado ou não puder ser aberto.
     */
    Estudante carregar() const;

    /**
     * @brief Retorna o caminho do arquivo de perfil.
     * @return Nome do arquivo usado por este gerenciador.
     */
    std::string getNomeArquivo() const;
};

#endif

#endif