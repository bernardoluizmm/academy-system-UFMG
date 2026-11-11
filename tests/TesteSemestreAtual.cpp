#include "doctest.h"
#include "SemestreAtual.hpp"
#include <stdexcept>
#include <string>

namespace
{
   
    void adicionar(SemestreAtual& semestre, const std::string& nome, int cargaHoraria,
                   const std::string& tipo = "Obrigatoria")
    {
        semestre.adicionarDisciplina("COD", "T1", nome, "Professor", "ICEx 101",
                                     cargaHoraria, 50, tipo, "Seg 10h");
    }

   
    void lancarNota(SemestreAtual& semestre, int idDisciplina, float valorMaximo, float nota)
    {
        Disciplina* disciplina = semestre.buscarDisciplina(idDisciplina);
        REQUIRE(disciplina != nullptr);
        int idAtividade = static_cast<int>(disciplina->avaliacoes().getAtividades().size()) + 1;
        disciplina->avaliacoes().adicionarAtividade(idAtividade, "Prova", "01/05", valorMaximo, nota, true);
    }
}

TEST_CASE("SemestreAtual - construtor e estado inicial")
{
    SemestreAtual semestre("2026/01");

    CHECK(semestre.getIdentificador() == "2026/01");
    CHECK(semestre.isTrancado() == false);
    CHECK(semestre.getDisciplinas().empty());
    CHECK(semestre.calcularNSG() == doctest::Approx(0.0));
    CHECK(semestre.getHorasIntegralizadas() == 0);
}

TEST_CASE("SemestreAtual - construtor rejeita identificador invalido")
{
    CHECK_THROWS_AS(SemestreAtual("2026/1"), std::invalid_argument);
    CHECK_THROWS_AS(SemestreAtual("2026/03"), std::invalid_argument);
    CHECK_THROWS_AS(SemestreAtual(""), std::invalid_argument);
}

TEST_CASE("SemestreAtual - adicionarDisciplina gera IDs automaticos")
{
    SemestreAtual semestre("2026/01");
    adicionar(semestre, "PDS2", 60);
    adicionar(semestre, "ED", 60);

    REQUIRE(semestre.getDisciplinas().size() == 2);
    CHECK(semestre.getDisciplinas()[0].getId() == 1);
    CHECK(semestre.getDisciplinas()[1].getId() == 2);
}

TEST_CASE("SemestreAtual - adicionarDisciplina valida os dados da disciplina")
{
    SemestreAtual semestre("2026/01");

    CHECK_THROWS_AS(adicionar(semestre, "Invalida", 50), std::invalid_argument);        
    CHECK_THROWS_AS(adicionar(semestre, "Invalida", 0), std::invalid_argument);          
    CHECK_THROWS_AS(adicionar(semestre, "Invalida", 60, "Eletiva"), std::invalid_argument);
    CHECK(semestre.getDisciplinas().empty());
}

TEST_CASE("SemestreAtual - adicionarDisciplina pronta rejeita ID repetido")
{
    SemestreAtual semestre("2026/01");
    adicionar(semestre, "PDS2", 60);  

    Disciplina repetida(1, "COD", "T1", "Outra", "Prof", "Sala", 60, 50, "Obrigatoria", "Ter 10h");
    CHECK_THROWS_AS(semestre.adicionarDisciplina(repetida), std::invalid_argument);
    CHECK(semestre.getDisciplinas().size() == 1);
}

TEST_CASE("SemestreAtual - adicionarDisciplina pronta atualiza o contador de IDs")
{
    SemestreAtual semestre("2026/01");

    Disciplina carregada(7, "COD", "T1", "Carregada", "Prof", "Sala", 60, 50, "Obrigatoria", "Seg 10h");
    semestre.adicionarDisciplina(carregada);

    adicionar(semestre, "Nova", 60); 

    REQUIRE(semestre.getDisciplinas().size() == 2);
    CHECK(semestre.getDisciplinas()[1].getId() == 8);
}

TEST_CASE("SemestreAtual - removerDisciplina")
{
    SemestreAtual semestre("2026/01");
    adicionar(semestre, "PDS2", 60);  
    adicionar(semestre, "ED", 60);    

    SUBCASE("remove disciplina existente")
    {
        semestre.removerDisciplina(1);
        REQUIRE(semestre.getDisciplinas().size() == 1);
        CHECK(semestre.getDisciplinas()[0].getId() == 2);
    }

    SUBCASE("ID inexistente lanca excecao e nao altera a lista")
    {
        CHECK_THROWS_AS(semestre.removerDisciplina(99), std::invalid_argument);
        CHECK(semestre.getDisciplinas().size() == 2);
    }
}

TEST_CASE("SemestreAtual - buscarDisciplina")
{
    SemestreAtual semestre("2026/01");
    adicionar(semestre, "PDS2", 60);

    SUBCASE("versao editavel")
    {
        Disciplina* encontrada = semestre.buscarDisciplina(1);
        REQUIRE(encontrada != nullptr);
        CHECK(encontrada->getId() == 1);
        CHECK(semestre.buscarDisciplina(99) == nullptr);
    }

    SUBCASE("versao somente leitura")
    {
        const SemestreAtual& constante = semestre;
        const Disciplina* encontrada = constante.buscarDisciplina(1);
        REQUIRE(encontrada != nullptr);
        CHECK(encontrada->getId() == 1);
        CHECK(constante.buscarDisciplina(99) == nullptr);
    }
}

TEST_CASE("SemestreAtual - NSG de uma disciplina e o seu percentual de aproveitamento")
{
    SemestreAtual semestre("2026/01");
    adicionar(semestre, "PDS2", 60);
    lancarNota(semestre, 1, 100.0f, 80.0f);

    CHECK(semestre.calcularNSG() == doctest::Approx(80.0));
}

TEST_CASE("SemestreAtual - NSG e ponderado pela carga horaria")
{
    SemestreAtual semestre("2026/01");
    adicionar(semestre, "Disciplina 1", 60);
    adicionar(semestre, "Disciplina 2", 30);
    lancarNota(semestre, 1, 100.0f, 80.0f);
    lancarNota(semestre, 2, 100.0f, 50.0f);


    CHECK(semestre.calcularNSG() == doctest::Approx(70.0));

 
    Semestre* base = &semestre;
    CHECK(base->calcularNSG() == doctest::Approx(70.0));
}

TEST_CASE("SemestreAtual - NSG ignora disciplina sem atividade concluida")
{
    SemestreAtual semestre("2026/01");
    adicionar(semestre, "Com nota", 60);
    adicionar(semestre, "Sem nota", 60);
    lancarNota(semestre, 1, 100.0f, 90.0f); 

   
    CHECK(semestre.calcularNSG() == doctest::Approx(90.0));
}

TEST_CASE("SemestreAtual - NSG e 0 quando nenhuma disciplina tem atividade concluida")
{
    SemestreAtual semestre("2026/01");
    adicionar(semestre, "Sem nota", 60);

    CHECK(semestre.calcularNSG() == doctest::Approx(0.0));
}

TEST_CASE("SemestreAtual - horas so contam disciplina com nota total parcial de pelo menos 60")
{
    SemestreAtual semestre("2026/01");
    adicionar(semestre, "Aprovada", 60);
    adicionar(semestre, "No limite", 30);
    adicionar(semestre, "Reprovada", 45);
    lancarNota(semestre, 1, 100.0f, 70.0f);
    lancarNota(semestre, 2, 100.0f, 60.0f); 
    lancarNota(semestre, 3, 100.0f, 59.0f);

    CHECK(semestre.getHorasObrigatorias() == 90); 
    CHECK(semestre.getHorasIntegralizadas() == 90);
}

TEST_CASE("SemestreAtual - horas separadas por tipo de disciplina")
{
    SemestreAtual semestre("2026/01");
    adicionar(semestre, "Obrigatoria", 60, "Obrigatoria");
    adicionar(semestre, "Optativa", 30, "Optativa");
    adicionar(semestre, "Livre", 45, "Formacao Livre");
    lancarNota(semestre, 1, 100.0f, 80.0f);
    lancarNota(semestre, 2, 100.0f, 80.0f);
    lancarNota(semestre, 3, 100.0f, 80.0f);

    CHECK(semestre.getHorasObrigatorias() == 60);
    CHECK(semestre.getHorasOptativas() == 30);
    CHECK(semestre.getHorasFormacaoLivre() == 45);
    CHECK(semestre.getHorasIntegralizadas() == 135);
}

TEST_CASE("SemestreAtual - serializar")
{
    SemestreAtual vazio("2026/01");
    CHECK(vazio.serializar() == "SEMESTRE_ATUAL|2026/01\n");

    SemestreAtual comDisciplina("2026/02");
    adicionar(comDisciplina, "PDS2", 60);
    std::string texto = comDisciplina.serializar();
    CHECK(texto.find("SEMESTRE_ATUAL|2026/02\n") == 0);  
    CHECK(texto.find("DISCIPLINA|") != std::string::npos);
}
