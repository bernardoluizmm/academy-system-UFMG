#include "doctest.h"
#include "GerenciadorArquivo.hpp"
#include <fstream>
#include <cstdio>
#include <stdexcept>

TEST_CASE("Teste 01: GerenciadorArquivo - Inicializacao padrao do nome do arquivo") {
    GerenciadorArquivo gerenciador;
    CHECK(gerenciador.getNomeArquivo() == "perfil_estudante.txt");
}

TEST_CASE("Teste 02: GerenciadorArquivo - Inicializacao com nome de arquivo personalizado") {
    GerenciadorArquivo gerenciador("meu_perfil.txt");
    CHECK(gerenciador.getNomeArquivo() == "meu_perfil.txt");
}

TEST_CASE("Teste 03: GerenciadorArquivo - Verifica que arquivo inexistente retorna false") {
    std::remove("arquivo_inexistente_teste.txt");
    GerenciadorArquivo gerenciador("arquivo_inexistente_teste.txt");

    CHECK(gerenciador.arquivoExiste() == false);
}

TEST_CASE("Teste 04: GerenciadorArquivo - Salvar perfil cria o arquivo corretamente") {
    const std::string nomeArq = "teste_salvar.txt";
    std::remove(nomeArq.c_str());

    Curso curso(1, "2024/01");
    HistoricoEscolar historico("2025/01");
    Estudante estudante("Lucas Silva", curso, historico);

    GerenciadorArquivo gerenciador(nomeArq);
    gerenciador.salvar(estudante);

    CHECK(gerenciador.arquivoExiste() == true);
    std::remove(nomeArq.c_str());
}

TEST_CASE("Teste 05: GerenciadorArquivo - Carregar recupera os dados salvos do estudante") {
    const std::string nomeArq = "teste_carregar.txt";
    std::remove(nomeArq.c_str());

    Curso curso(1, "2024/01");
    HistoricoEscolar historico("2025/01");
    historico.adicionarSemestreConsolidado(SemestreConsolidado("2024/01", 85.0f, 60, 0, 0, false));

    Disciplina pds2(1, "DCC204", "TM1", "PDS II", "Prof. Douglas", "ICEx", 60, 50, "Obrigatoria", "Ter/Qui");
    pds2.frequencia().setFaltasAtuais(2);
    pds2.avaliacoes().adicionarAtividade(1, "TP1", "10/05", 30.0f, 25.0f, true);
    historico.getSemestreAtual()->adicionarDisciplina(pds2);

    Estudante original("Ana Clara", curso, historico);

    GerenciadorArquivo gerenciador(nomeArq);
    gerenciador.salvar(original);

    std::unique_ptr<Estudante> carregado = gerenciador.carregar();

    CHECK(carregado->getNome() == "Ana Clara");
    CHECK(carregado->getCurso().getNome() == "Ciencia da Computacao");
    CHECK(carregado->getCurso().getSemestreIngresso() == "2024/01");
    CHECK(carregado->getHistorico().getSemestresPassados().size() == 1);
    CHECK(carregado->getHistorico().getSemestreAtual()->getIdentificador() == "2025/01");
    CHECK(carregado->getHistorico().getSemestreAtual()->getDisciplinas().size() == 1);
    CHECK(carregado->getHistorico().getSemestreAtual()->getDisciplinas()[0].getCodigo() == "DCC204");
    CHECK(carregado->getHistorico().getSemestreAtual()->getDisciplinas()[0].frequencia().getFaltasAtuais() == 2);

    std::remove(nomeArq.c_str());
}

TEST_CASE("Teste 06: GerenciadorArquivo - Falha ao carregar arquivo inexistente") {
    GerenciadorArquivo gerenciador("nao_existe_12345.txt");
    CHECK_THROWS_AS(gerenciador.carregar(), std::runtime_error);
}

TEST_CASE("Teste 07: GerenciadorArquivo - Falha ao carregar arquivo corrompido") {
    const std::string nomeArq = "teste_corrompido.txt";
    std::ofstream arquivo(nomeArq);
    arquivo << "LINHA_INVALIDA|123\n";
    arquivo.close();

    GerenciadorArquivo gerenciador(nomeArq);
    CHECK_THROWS_AS(gerenciador.carregar(), std::runtime_error);

    std::remove(nomeArq.c_str());
}
