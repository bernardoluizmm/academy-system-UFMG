/**
 * @file Estudante.hpp
 * @brief Declaracao da classe Estudante para representacao do perfil academico do usuario.
 */

#ifndef ESTUDANTE_HPP
#define ESTUDANTE_HPP

#include <string>
#include "Curso.hpp"
#include "HistoricoEscolar.hpp"

/**
 * @class Estudante
 * @brief Agregado raiz que representa o estudante e compoe as informacoes de seu curso e historico escolar.
 * @details Segue estritamente o principio RAII: o objeto so pode ser instanciado com todos os
 *          seus dados validados (nome, curso e historico), mantendo sua identidade e vinculo
 *          curricular imutaveis apos a construcao. Fornece metodos para consulta cadastral,
 *          manipulacao do historico escolar, calculo do progresso de integralizacao e
 *          serializacao completa do perfil.
 */
class Estudante 
{
private:
    std::string _nome;           /**< Nome de identificacao do estudante (imutavel apos construcao). */
    Curso _curso;                /**< Dados do vincular currical (imutavel apos construcao). */
    HistoricoEscolar _historico; /**< Historico contendo os semestres consolidados e o semestre atual. */

     /**
     * @brief Calcula o percentual base de horas cumpridas em relação a uma meta exigida.
     * @details Método auxiliar genérico que centraliza a lógica matemática de porcentagem.
     *          Implementa programação defensiva para evitar divisão por zero e aplica 
     *          um teto máximo, garantindo que o progresso nunca ultrapasse 100%.
     * 
     * @param horasCumpridas Total de horas já integralizadas pelo estudante em uma categoria específica.
     * @param horasRequeridas Total de horas exigidas pelo currículo do curso para essa mesma categoria.
     * @return Percentual de conclusão (de 0.0f a 100.0f). Se horasRequeridas for <= 0, retorna 0.0f.
     */
    float calcularPercentual(int horasCumpridas, int horasRequeridas) const;
public:
    /**
     * @brief Valida se o nome informado para o estudante respeita os limites de tamanho (1 a 100 caracteres).
     * @details Metodo estatico utilizado como barricada tanto pelos fluxos de cadastro/carregamento
     *          quanto pelo construtor parametrizado da classe.
     * @param nome String contendo o nome a ser verificado.
     * @throws std::invalid_argument Se o nome for vazio ou possuir mais de 100 caracteres.
     */
    static void validarNome(const std::string& nome);

    /**
     * @brief Construtor parametrizado da classe Estudante (RAII).
     * @details Define o nome, o curso e o historico escolar no momento do cadastro ou carregamento
     *          do perfil. Uma vez construido o objeto, o nome e o curso nao podem ser alterados.
     * @param nome Nome do estudante (deve conter entre 1 e 100 caracteres).
     * @param curso Objeto Curso devidamente configurado.
     * @param historico Objeto HistoricoEscolar do estudante.
     * @throws std::invalid_argument Se o nome informado for vazio ou exceder 100 caracteres.
     */
    Estudante(const std::string& nome, const Curso& curso, const HistoricoEscolar& historico);

    /**
     * @brief Obtem o nome do estudante.
     * @return String contendo o nome do estudante.
     */
    std::string getNome() const;

    /**
     * @brief Obtem uma referencia constante (somente leitura) para o curso do estudante.
     * @return Referencia constante para o objeto Curso.
     */
    const Curso& getCurso() const;

    /**
     * @brief Obtem uma referencia constante para o historico escolar do estudante.
     * @return Referencia constante para o objeto HistoricoEscolar.
     */
    const HistoricoEscolar& getHistorico() const;

    /**
     * @brief Obtem uma referencia editavel para o historico escolar do estudante.
     * @return Referencia para o objeto HistoricoEscolar permitindo modificacoes na vida academica.
     */
    HistoricoEscolar& getHistoricoEditavel();

    /**
     * @brief Calcula o percentual de conclusao total do curso.
     * @details Relaciona o total de horas integralizadas no historico com a carga horaria
     *          total exigida pelo curriculo do curso, limitando o teto em 100%.
     * @return Percentual de conclusao total (de 0.0f a 100.0f).
     */
    float calcularPercentualCursoCompleto() const;

    /**
     * @brief Calcula o percentual de conclusao da carga horaria de disciplinas obrigatorias.
     * @return Percentual de horas obrigatorias cumpridas (de 0.0f a 100.0f).
     */
    float calcularPercentualObrigatorias() const;

    /**
     * @brief Calcula o percentual de conclusao da carga horaria de disciplinas optativas.
     * @return Percentual de horas optativas cumpridas (de 0.0f a 100.0f).
     */
    float calcularPercentualOptativas() const;

    /**
     * @brief Calcula o percentual de conclusao da carga horaria de formacao livre.
     * @return Percentual de horas de formacao livre cumpridas (de 0.0f a 100.0f).
     */
    float calcularPercentualFormacaoLivre() const;

    /**
     * @brief Serializa todos os dados do estudante em formato textual.
     * @details Concatena o registro do estudante, a serializacao do curso e a serializacao
     *          do historico escolar em multiplas linhas delimitadas por '|'.
     * @return String formatada pronta para gravacao em arquivo.
     */
    std::string serializar() const;
};

#endif