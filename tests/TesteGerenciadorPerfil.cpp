#include "doctest.h"
#include "GerenciadorPerfil.hpp"
#include <fstream>
#include <cstdio>

TEST_CASE("GerenciadorPerfil - Salvar e Carregar Perfil (Round-Trip)") 
{
    Curso curso("Ciencia da Computacao", 2400, 600, 300);
    SemestreAtual semestre("2026/1");
    Disciplina d("PDS2", "DCC204", "Douglas", "ICEx", CategoriaDisciplina::OBRIGATORIA, 60, 15);
    semestre.adicionarDisciplina(d);

    Estudante estudanteOriginal("Lucas Venturini", curso, "2024/1", semestre);

    const std::string arquivoTeste = "teste_perfil_temp.txt";

    SUBCASE("Salvar perfil em arquivo e validar")
    {
        bool salvou = GerenciadorPerfil::salvarPerfil(estudanteOriginal, arquivoTeste);
        CHECK(salvou == true);

        CHECK(GerenciadorPerfil::validarFormato(arquivoTeste) == true);

        Curso cursoVazio("", 0, 0, 0);
        SemestreAtual semVazio("");
        Estudante estudanteCarregado("", cursoVazio, "", semVazio);

        bool carregou = GerenciadorPerfil::carregarPerfil(estudanteCarregado, arquivoTeste);
        CHECK(carregou == true);
        CHECK(estudanteCarregado.getNome() == "Lucas Venturini");
        CHECK(estudanteCarregado.getSemestreIngresso() == "2024/1");
        CHECK(estudanteCarregado.getCurso().getNome() == "Ciencia da Computacao");

        std::remove(arquivoTeste.c_str());
    }
}

TEST_CASE("GerenciadorPerfil - Casos de Erro / Arquivos Invalidos") 
{
    SUBCASE("Arquivo inexistente")
    {
        CHECK(GerenciadorPerfil::validarFormato("arquivo_que_nao_existe_12345.txt") == false);

        Curso cursoVazio("", 0, 0, 0);
        SemestreAtual semVazio("");
        Estudante est("", cursoVazio, "", semVazio);
        CHECK(GerenciadorPerfil::carregarPerfil(est, "arquivo_que_nao_existe_12345.txt") == false);
    }

    SUBCASE("Arquivo com conteudo invalido/corrompido")
    {
        const std::string arquivoCorrompido = "perfil_corrompido_temp.txt";
        std::ofstream out(arquivoCorrompido);
        out << "CONTEUDO_TOTALMENTE_INVALIDO_SEM_FORMATO";
        out.close();

        CHECK(GerenciadorPerfil::validarFormato(arquivoCorrompido) == false);

        std::remove(arquivoCorrompido.c_str());
    }
}
