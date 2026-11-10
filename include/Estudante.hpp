/**
 * @file Estudante.hpp
 * @brief Declaração da classe Estudante para representação do perfil acadêmico do usuário.
 */

#ifndef ESTUDANTE_HPP
#define ESTUDANTE_HPP

#include <string>
#include "Curso.hpp"
#include "HistoricoEscolar.hpp"

/**
 * @class Estudante
 * @brief Representa o estudante e agrega as informações de seu curso e do seu histórico escolar.
 * @details Fornece métodos para consulta e manipulação dos dados cadastrais, cálculo do
 *          progresso de integralização de carga horária (total e por categoria) e
 *          serialização completa do perfil para persistência em arquivo.
 */
class Estudante 
{
private:
    std::string _nome;           /**< Nome completo ou de identificação do estudante. */
    Curso _curso;                /**< Dados e exigências curriculares do curso vinculado. */
    HistoricoEscolar _historico; /**< Histórico contendo as informações dos semestres consolidados e do semestre atual. */

    float calcularPercentual(int horasCumpridas, int horasRequeridas) const;
public:
    /**
     * @brief Construtor padrão da classe Estudante.
     * @details Inicializa o estudante com o pseudonome padrão "Estudante", além de instâncias
     *          padrão de Curso e HistoricoEscolar.
     */
    Estudante();

    /**
     * @brief Construtor parametrizado da classe Estudante.
     * @param nome Nome do estudante (deve conter entre 1 e 100 caracteres).
     * @param curso Objeto Curso devidamente configurado.
     * @param historico Objeto HistoricoEscolar do estudante.
     * @throws std::invalid_argument Se o nome informado for vazio ou exceder 100 caracteres.
     */
    Estudante(const std::string& nome, const Curso& curso, const HistoricoEscolar& historico);

    /**
     * @brief Obtém o nome do estudante.
     * @return String contendo o nome do estudante.
     */
    std::string getNome() const;

    /**
     * @brief Define o nome do estudante. Uma vez definido, este nome é inalterável.
     * @param novoNome Novo nome a ser atribuído (entre 1 e 100 caracteres).
     * @throws std::invalid_argument Se o nome for vazio ou possuir mais de 100 caracteres.
     */
    void setNome(const std::string& novoNome);

    /**
     * @brief Obtém uma referência constante para o curso do estudante.
     * @return Referência constante para o objeto Curso.
     */
    const Curso& getCurso() const;

    /**
     * @brief Obtém uma referência editável para o curso do estudante.
     * @return Referência para o objeto Curso permitindo modificações.
     */
    Curso& getCursoEditavel();

    /**
     * @brief Substitui o objeto Curso associado ao estudante.
     * @param novoCurso Novo objeto Curso a ser atribuído.
     */
    void setCurso(const Curso& novoCurso);

    /**
     * @brief Obtém uma referência constante para o histórico escolar do estudante.
     * @return Referência constante para o objeto HistoricoEscolar.
     */
    const HistoricoEscolar& getHistorico() const;

    /**
     * @brief Obtém uma referência editável para o histórico escolar do estudante.
     * @return Referência para o objeto HistoricoEscolar permitindo modificações.
     */
    HistoricoEscolar& getHistoricoEditavel();

    /**
     * @brief Calcula o percentual de conclusão total do curso.
     * @details Relaciona o total de horas integralizadas no histórico com a carga horária
     *          total exigida pelo currículo do curso, limitando o teto em 100%.
     * @return Percentual de conclusão total (de 0.0f a 100.0f).
     */
    float calcularPercentualCursoCompleto() const;

    /**
     * @brief Calcula o percentual de conclusão da carga horária de disciplinas obrigatórias.
     * @return Percentual de horas obrigatórias cumpridas (de 0.0f a 100.0f).
     */
    float calcularPercentualObrigatorias() const;

    /**
     * @brief Calcula o percentual de conclusão da carga horária de disciplinas optativas.
     * @return Percentual de horas optativas cumpridas (de 0.0f a 100.0f).
     */
    float calcularPercentualOptativas() const;

    /**
     * @brief Calcula o percentual de conclusão da carga horária de formação livre.
     * @return Percentual de horas de formação livre cumpridas (de 0.0f a 100.0f).
     */
    float calcularPercentualFormacaoLivre() const;

    /**
     * @brief Serializa todos os dados do estudante em formato textual.
     * @details Concatena o registro do estudante, a serialização do curso e a serialização
     *          do histórico escolar em múltiplas linhas delimitadas por '|'.
     * @return String formatada pronta para gravação em arquivo.
     */
    std::string serializar() const;
};

#endif