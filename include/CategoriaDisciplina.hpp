/**
 * @file CategoriaDisciplina.hpp
 * @brief Enumeração das categorias curriculares de uma disciplina.
 */
#ifndef CATEGORIA_DISCIPLINA_HPP
#define CATEGORIA_DISCIPLINA_HPP

/**
 * @enum CategoriaDisciplina
 * @brief Define os tipos de classificação de uma disciplina na grade curricular.
 */
enum class CategoriaDisciplina {
    OBRIGATORIA,     ///< Disciplina de cumprimento obrigatório pelo curso.
    OPTATIVA,        ///< Disciplina optativa da grade do curso.
    FORMACAO_LIVRE   ///< Disciplina de formação livre cursada pelo estudante.
};

#endif // CATEGORIA_DISCIPLINA_HPP