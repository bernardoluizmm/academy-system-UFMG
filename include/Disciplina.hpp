#ifndef DISCIPLINA_HPP
#define DISCIPLINA_HPP
#include <string>
#include <vector>

class Disciplina {

    private:
        std::string _nome;
        std::string _codigo;
        std::string _professor;
        std::string _salaBloco;
        std::vector<AtividadeAvaliativa> _atividades;
        ControleFrequencia _frequencia;
        CategoriaDisciplina _categoria;
        int _cargaHoraria;

    public:
        Disciplina(
            const std::string& nome, 
            const std::string& codigo, 
            const std::string& professor, 
            const std::string& salaBloco, 
            CategoriaDisciplina categoria,
            int cargaHoraria,
            int faltasPermitidas
        );
        std::string getNome() const;
        std::string getCodigo() const;
        std::string getProfessor() const;
        std::string getSalaBloco() const;
        int getCargaHoraria() const;
        CategoriaDisciplina getCategoria() const;

        void adicionarAtividade(
            const AtividadeAvaliativa& atividade
        );

        bool editarAtividade(
            int indice,
            const AtividadeAvaliativa& nova
        );

        double calcularMediaFinal() const;
        bool estaAprovado() const;

        const ControleFrequencia& getFrequencia() const;
        ControleFrequencia& getFrequencia();

        const std::vector<AtividadeAvaliativa>& getAtividades() const;

        bool removerAtividade(int indice);
        bool validarCamposObrigatorios() const;
        bool verificarSomaPontos() const;
        double calcularNotaTotal() const;
        char determinarConceitoParcial() const;
};
#endif // DISCIPLINA_HPP