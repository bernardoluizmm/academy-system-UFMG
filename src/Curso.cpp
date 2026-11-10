#include "Curso.hpp"
#include "Semestre.hpp"
#include <stdexcept>
#include <sstream>

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
    if (opcao !=  OPCAO_CC && opcao != OPCAO_SI) 
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
    if (this->_opcaoCurso == Curso::OPCAO_CC) 
    {
        this->_nome = "Ciencia da Computacao";
        if (anoIngresso < Curso::ANO_REFORMA_CC) 
        {
            this->_horasTotaisObrigatorias = Curso::HORAS_OBRIG_CC_ANTIGO;
            this->_horasTotaisOptativas = Curso::HORAS_OPT_CC_ANTIGO;
            this->_horasTotaisFormacaoLivre = Curso::HORAS_LIVRE_CC_ANTIGO;
            this->_horasAdicionais = Curso::HORAS_ADIC_CC_ANTIGO;
            this->_horasTotaisCurso = Curso::HORAS_TOTAIS_CC_ANTIGO;
        } else 
        {
            this->_horasTotaisObrigatorias = Curso::HORAS_OBRIG_CC_NOVO;
            this->_horasTotaisOptativas = Curso::HORAS_OPT_CC_NOVO;
            this->_horasTotaisFormacaoLivre = Curso::HORAS_LIVRE_CC_NOVO;
            this->_horasAdicionais = Curso::HORAS_ADIC_CC_NOVO;
            this->_horasTotaisCurso = Curso::HORAS_TOTAIS_CC_NOVO;
        }
    } else 
    {
        this->_nome = "Sistemas de Informacao";
        this->_horasTotaisObrigatorias = Curso::HORAS_OBRIG_SI;
        this->_horasTotaisOptativas = Curso::HORAS_OPT_SI;
        this->_horasTotaisFormacaoLivre = Curso::HORAS_LIVRE_SI;
        this->_horasAdicionais = Curso::HORAS_ADIC_SI;
        this->_horasTotaisCurso = Curso::HORAS_TOTAIS_SI;
    }
}

std::string Curso::serializar() const 
{
    std::ostringstream oss;
    oss << "CURSO|" << this->_opcaoCurso << "|" << this->_semestreIngresso;
    return oss.str();
}