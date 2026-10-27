#include "Curso.hpp"
#include "Semestre.hpp"
#include <stdexcept>

Curso::Curso() 
    : _opcaoCurso(1),
      _nome("Ciencia da Computacao"),
      _semestreIngresso("2025/01"),
      _horasTotaisObrigatorias(1980),
      _horasTotaisOptativas(1110),
      _horasTotaisFormacaoLivre(120),
      _horasAdicionais(0),
      _horasTotaisCurso(3210),
      _configurado(false)
{}

Curso::Curso(int opcaoCurso, const std::string& semestreIngresso) 
    : _opcaoCurso(1),
      _nome("Ciencia da Computacao"),
      _semestreIngresso("2025/01"),
      _horasTotaisObrigatorias(1980),
      _horasTotaisOptativas(1110),
      _horasTotaisFormacaoLivre(120),
      _horasAdicionais(0),
      _horasTotaisCurso(3210),
      _configurado(false)
{
    this->inicializarCurso(opcaoCurso, semestreIngresso);
}

int Curso::getOpcaoCurso() const 
{ 
    return this->_opcaoCurso; 
}

std::string Curso::getNome() const 
{ 
    return this->_nome; 
}

std::string Curso::getSemestreIngresso() const 
{ 
    return this->_semestreIngresso; 
}

int Curso::getHorasTotaisObrigatorias() const 
{ 
    return this->_horasTotaisObrigatorias; 
}

int Curso::getHorasTotaisOptativas() const 
{ 
    return this->_horasTotaisOptativas; 
}

int Curso::getHorasTotaisFormacaoLivre() const 
{ 
    return this->_horasTotaisFormacaoLivre; 
}

int Curso::getHorasAdicionais() const 
{ 
    return this->_horasAdicionais; 
}

int Curso::getHorasTotaisCurso() const 
{ 
    return this->_horasTotaisCurso; 
}

void Curso::inicializarCurso(int opcao, const std::string& semIngresso) 
{
    this->setOpcaoCurso(opcao);
    this->setSemestreIngresso(semIngresso);
    this->configurarHorasPorCurriculo();
    this->_configurado = true;
}

void Curso::setOpcaoCurso(int opcao) 
{
    if (this->_configurado) 
    {
        throw std::invalid_argument("Os dados do curso nao podem ser alterados apos definidos.");
    }
    if (opcao != 1 && opcao != 2) 
    {
        throw std::invalid_argument("Opcao de curso invalida. Digite 1 para CC ou 2 para SI.");
    }
    this->_opcaoCurso = opcao;
}

void Curso::setSemestreIngresso(const std::string& semIngresso) 
{
    if (this->_configurado) 
    {
        throw std::invalid_argument("Os dados do curso nao podem ser alterados apos definidos.");
    }
    if (!Semestre::validarFormatoIdentificador(semIngresso)) 
    {
        throw std::invalid_argument("Semestre de ingresso invalido. Use o formato AAAA/01 ou AAAA/02.");
    }
    this->_semestreIngresso = semIngresso;
}

void Curso::configurarHorasPorCurriculo() 
{
    int anoIngresso = Semestre::extrairAno(this->_semestreIngresso);
    if (this->_opcaoCurso == 1) 
    {
        this->_nome = "Ciencia da Computacao";
        if (anoIngresso < 2025) 
        {
            this->_horasTotaisObrigatorias = 2040;
            this->_horasTotaisOptativas = 1020;
            this->_horasTotaisFormacaoLivre = 60;
            this->_horasAdicionais = 120;
            this->_horasTotaisCurso = 3240;
        } else 
        {
            this->_horasTotaisObrigatorias = 1980;
            this->_horasTotaisOptativas = 1110;
            this->_horasTotaisFormacaoLivre = 120;
            this->_horasAdicionais = 0;
            this->_horasTotaisCurso = 3210;
        }
    } else 
    {
        this->_nome = "Sistemas de Informacao";
        this->_horasTotaisObrigatorias = 2100;
        this->_horasTotaisOptativas = 780;
        this->_horasTotaisFormacaoLivre = 120;
        this->_horasAdicionais = 0;
        this->_horasTotaisCurso = 3000;
    }
}