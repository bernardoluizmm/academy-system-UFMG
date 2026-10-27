#include "Disciplina.hpp"
#include "CalculadorMaxFaltas.hpp" 
#include <stdexcept>
#include <sstream>

Disciplina::Disciplina(int id,
                       const std::string& codigo,
                       const std::string& codigoTurma,
                       const std::string& nome,
                       const std::string& professor,
                       const std::string& salaBloco,
                       int cargaHoraria,
                       int duracaoAulaMinutos,
                       const std::string& tipo,
                       const std::string& horarioDias)
    : _id(id),
      _cargaHoraria(cargaHoraria),
      _duracaoAulaMinutos(duracaoAulaMinutos),
      _frequencia(CalcularMaxFaltas::calcularDiasMaximosFalta(cargaHoraria, duracaoAulaMinutos)), 
      _avaliacoes() 
{
    if (id < 0) 
    {
        throw std::invalid_argument("ID da disciplina invalido.");
    }
    if (cargaHoraria <= 0 || cargaHoraria % 15 != 0) 
    {
        throw std::invalid_argument("A carga horaria deve ser maior que zero e divisivel por 15.");
    }
    if (duracaoAulaMinutos < 50) 
    {
        throw std::invalid_argument("A duracao da aula deve ser de, no minimo, 50 minutos.");
    }

    this->setCodigo(codigo);
    this->setCodigoTurma(codigoTurma);
    this->setNome(nome);
    this->setProfessor(professor);
    this->setSalaBloco(salaBloco);
    this->setTipo(tipo);
    this->setHorarioDias(horarioDias);
}

void Disciplina::atualizarLimiteFaltas() 
{
    int novoMax = CalcularMaxFaltas::calcularDiasMaximosFalta(this->_cargaHoraria, this->_duracaoAulaMinutos);
    this->_frequencia.setMaxFaltas(novoMax);
}

his->_id; 
}
std::string Disciplina::getCodigo() const 
{ 
    return this->_codigo; 
}
std::string Disciplina::getCodigoTurma() const 
{ 
    return this->_codigoTurma; 
}
std::string Disciplina::getNome() const 
{ 
    return this->_nome; 
}
std::string Disciplina::getProfessor() const 
{ 
    return this->_professor; 
}
std::string Disciplina::getSalaBloco() const 
{ 
    return this->_salaBloco; 
}
int Disciplina::getCargaHoraria() const 
{ 
    return this->_cargaHoraria; 
}
int Disciplina::getDuracaoAulaMinutos() const 
{ 
    return this->_duracaoAulaMinutos; 
}
std::string Disciplina::getTipo() const 
{ 
    return this->_tipo; 
}
std::string Disciplina::getHorarioDias() const 
{ 
    return this->_horarioDias; 
}
ControleFrequencia& Disciplina::frequencia() 
{ 
    return this->_frequencia; 
}
const ControleFrequencia& Disciplina::frequencia() const 
{ 
    return this->_frequencia; 
}
DiarioAtividades& Disciplina::avaliacoes() 
{ 
    return this->_avaliacoes; 
}
const DiarioAtividades& Disciplina::avaliacoes() const 
{ 
    return this->_avaliacoes; 
}
void Disciplina::setCodigo(const std::string& novoCodigo) 
{
    if (novoCodigo.empty() || novoCodigo.length() > 8) 
    {
        throw std::invalid_argument("O codigo da disciplina deve ter entre 1 e 100 caracteres.");
    }
    this->_codigo = novoCodigo;
}

void Disciplina::setCodigoTurma(const std::string& novaTurma) 
{
    if (novaTurma.empty() || novaTurma.length() > 6) 
    {
        throw std::invalid_argument("O codigo da turma deve ter entre 1 e 100 caracteres.");
    }
    this->_codigoTurma = novaTurma;
}

void Disciplina::setNome(const std::string& novoNome) 
{
    if (novoNome.empty() || novoNome.length() > 22) 
    {
        throw std::invalid_argument("O nome da disciplina deve ter entre 1 e 100 caracteres.");
    }
    this->_nome = novoNome;
}
void Disciplina::setProfessor(const std::string& novoProfessor) 
{
    if (novoProfessor.empty() || novoProfessor.length() > 100) 
    {
        throw std::invalid_argument("O nome do professor deve ter entre 1 e 100 caracteres.");
    }
    this->_professor = novoProfessor;
}

void Disciplina::setSalaBloco(const std::string& novaSala) 
{
    if (novaSala.empty() || novaSala.length() > 100) 
    {
        throw std::invalid_argument("A sala/bloco deve ter entre 1 e 100 caracteres.");
    }
    this->_salaBloco = novaSala;
}
void Disciplina::setHorarioDias(const std::string& novoHorarioDias) 
{
    if (novoHorarioDias.empty() || novoHorarioDias.length() > 100) 
    {
        throw std::invalid_argument("O horario e dias de aula devem ter entre 1 e 100 caracteres.");
    }
    this->_horarioDias = novoHorarioDias;
}
void Disciplina::setCargaHoraria(int novaCargaHoraria) 
{
    if (novaCargaHoraria <= 0 || novaCargaHoraria % 15 != 0) 
    {
        throw std::invalid_argument("A carga horaria deve ser maior que zero e divisivel por 15.");
    }
    this->_cargaHoraria = novaCargaHoraria;
    this->atualizarLimiteFaltas(); 
}

void Disciplina::setDuracaoAulaMinutos(int novaDuracaoMinutos) 
{
    if (novaDuracaoMinutos < 50) 
    {
        throw std::invalid_argument("A duracao da aula deve ser de no minimo 50 minutos.");
    }
    this->_duracaoAulaMinutos = novaDuracaoMinutos;
    this->atualizarLimiteFaltas();
}

void Disciplina::setTipo(const std::string& novoTipo) 
{
    if (novoTipo != "Obrigatoria" && novoTipo != "Optativa" && novoTipo != "Formacao Livre") 
    {
        throw std::invalid_argument("Tipo invalido. Use 'Obrigatoria', 'Optativa' ou 'Formacao Livre'.");
    }
    this->_tipo = novoTipo;
}