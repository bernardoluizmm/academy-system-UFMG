#include "Disciplina.hpp"
#include "CalculadorMaxFaltas.hpp" 
#include <stdexcept>
#include <sstream>

void Disciplina::validarCodigo(const std::string& codigo) 
{
    if (codigo.empty() || codigo.length() > 8) 
    {
        throw std::invalid_argument("O codigo da disciplina deve ter entre 1 e 8 caracteres.");
    }
}

void Disciplina::validarCodigoTurma(const std::string& turma) 
{
    if (turma.empty() || turma.length() > 6) 
    {
        throw std::invalid_argument("O codigo da turma deve ter entre 1 e 6 caracteres.");
    }
}

void Disciplina::validarNome(const std::string& nome) 
{
    if (nome.empty() || nome.length() > 26) 
    {
        throw std::invalid_argument("O nome da disciplina deve ter entre 1 e 26 caracteres.");
    }
}

void Disciplina::validarProfessor(const std::string& professor) 
{
    if (professor.empty() || professor.length() > 100) 
    {
        throw std::invalid_argument("O nome do professor deve ter entre 1 e 100 caracteres.");
    }
}

void Disciplina::validarSalaBloco(const std::string& sala) 
{
    if (sala.empty() || sala.length() > 100) 
    {
        throw std::invalid_argument("A sala/bloco deve ter entre 1 e 100 caracteres.");
    }
}

void Disciplina::validarCargaHoraria(int cargaHoraria) 
{
    if (cargaHoraria <= 0 || cargaHoraria % 15 != 0) 
    {
        throw std::invalid_argument("A carga horaria deve ser maior que zero e divisivel por 15.");
    }
}

void Disciplina::validarDuracaoAulaMinutos(int duracaoMinutos) 
{
    if (duracaoMinutos < 50) 
    {
        throw std::invalid_argument("A duracao da aula deve ser de, no minimo, 50 minutos.");
    }
}

void Disciplina::validarTipo(const std::string& tipo) 
{
    if (tipo != "Obrigatoria" && tipo != "Optativa" && tipo != "Formacao Livre") 
    {
        throw std::invalid_argument("Tipo invalido. Use 'Obrigatoria', 'Optativa' ou 'Formacao Livre'.");
    }
}

void Disciplina::validarHorarioDias(const std::string& horarioDias) 
{
    if (horarioDias.empty() || horarioDias.length() > 100) 
    {
        throw std::invalid_argument("O horario e dias de aula devem ter entre 1 e 100 caracteres.");
    }
}


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
      _frequencia(CalculadorMaxFaltas::calcularDiasMaximosFalta(cargaHoraria, duracaoAulaMinutos)), 
      _avaliacoes() 
{
        if (id < 0) 
    {
        throw std::invalid_argument("ID da disciplina invalido.");
    }
    Disciplina::validarCargaHoraria(cargaHoraria);
    Disciplina::validarDuracaoAulaMinutos(duracaoAulaMinutos);

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
    int novoMax = CalculadorMaxFaltas::calcularDiasMaximosFalta(this->_cargaHoraria, this->_duracaoAulaMinutos);
    this->_frequencia.setMaxFaltas(novoMax);
}

int Disciplina::getId() const 
{ 
    return this->_id; 
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
     Disciplina::validarCodigo(novoCodigo);
    this->_codigo = novoCodigo;
}

void Disciplina::setCodigoTurma(const std::string& novaTurma) 
{
    Disciplina::validarCodigoTurma(novaTurma);
    this->_codigoTurma = novaTurma;
}

void Disciplina::setNome(const std::string& novoNome) 
{
    Disciplina::validarNome(novoNome);
    this->_nome = novoNome;
}
void Disciplina::setProfessor(const std::string& novoProfessor) 
{
    Disciplina::validarProfessor(novoProfessor);
    this->_professor = novoProfessor;
}

void Disciplina::setSalaBloco(const std::string& novaSala) 
{
    Disciplina::validarSalaBloco(novaSala);
    this->_salaBloco = novaSala;
}

void Disciplina::setCargaHoraria(int novaCargaHoraria) 
{
    Disciplina::validarCargaHoraria(novaCargaHoraria);
    this->_cargaHoraria = novaCargaHoraria;
    this->atualizarLimiteFaltas();
}

void Disciplina::setDuracaoAulaMinutos(int novaDuracaoMinutos) 
{
    Disciplina::validarDuracaoAulaMinutos(novaDuracaoMinutos);
    this->_duracaoAulaMinutos = novaDuracaoMinutos;
    this->atualizarLimiteFaltas();
}

void Disciplina::setTipo(const std::string& novoTipo) 
{
    Disciplina::validarTipo(novoTipo);
    this->_tipo = novoTipo;
}
void Disciplina::setHorarioDias(const std::string& novoHorarioDias) 
{
    Disciplina::validarHorarioDias(novoHorarioDias);
    this->_horarioDias = novoHorarioDias;
}

std::string Disciplina::serializar() const 
{
    std::ostringstream oss;
    oss << "DISCIPLINA|" << this->_id << "|" << this->_codigo << "|" << this->_codigoTurma << "|"
        << this->_nome << "|" << this->_professor << "|" << this->_salaBloco << "|"
        << this->_cargaHoraria << "|" << this->_duracaoAulaMinutos << "|"
        << this->_tipo << "|" << this->_horarioDias << "|" << this->_frequencia.getFaltasAtuais() << "\n";
        
    const std::vector<AtividadeAvaliativa>& atividadesAtual = this->_avaliacoes.getAtividades();
    for (std::vector<AtividadeAvaliativa>::const_iterator it = atividadesAtual.begin(); it != atividadesAtual.end(); ++it) 
    {
        oss << it->serializar() << "\n";
    }
    return oss.str();
}