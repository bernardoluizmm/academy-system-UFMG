#include "GerenciadorArquivo.hpp"
#include <fstream>
#include <stdexcept>

GerenciadorArquivo::GerenciadorArquivo(const std::string& nomeArquivo)
    : _nomeArquivo(nomeArquivo) 
{
}

std::vector<std::string> GerenciadorArquivo::dividirLinha(const std::string& linha, char delimitador)
{
    std::vector<std::string> partes;
    std::string::size_type inicio = 0;
    while (true)
    {
        std::string::size_type pos = linha.find(delimitador, inicio);
        if (pos == std::string::npos)
        {
            partes.push_back(linha.substr(inicio));
            break;
        }
        partes.push_back(linha.substr(inicio, pos - inicio));
        inicio = pos + 1;
    }
    return partes;
}

bool GerenciadorArquivo::arquivoExiste() const 
{
    std::ifstream ifs(this->_nomeArquivo);
    return ifs.good();
}

void GerenciadorArquivo::salvar(const Estudante& estudante) const 
{
    std::ofstream ofs(this->_nomeArquivo);
    if (!ofs.is_open()) 
    {
        throw std::runtime_error("Nao foi possivel abrir o arquivo para salvar os dados.");
    }
    ofs << estudante.serializar();
    ofs.close();
}

std::unique_ptr<Estudante> GerenciadorArquivo::carregar() const 
{
    std::ifstream ifs(this->_nomeArquivo);
    if (!ifs.is_open()) 
    {
        throw std::runtime_error("Arquivo de perfil nao encontrado.");
    }

    bool temNome = false;
    std::string nomeLido;
    std::unique_ptr<Curso> cursoLido(nullptr);
    std::unique_ptr<HistoricoEscolar> historicoLido(nullptr);
    std::vector<SemestreConsolidado> semestresConsolidadosLidos;
    int idUltimaDisciplina = -1;

    std::string linha;
    try 
    {
        while (std::getline(ifs, linha)) 
        {
            if (!linha.empty() && linha[linha.length() - 1] == '\r') 
            {
                linha.erase(linha.length() - 1);
            }
            if (linha.empty()) 
            {
                continue;
            }
            std::vector<std::string> campos = GerenciadorArquivo::dividirLinha(linha, '|');
            if (campos.empty()) 
            {
                continue;
            }

            const std::string& tipoRegistro = campos[0];
            if (tipoRegistro == "ESTUDANTE" && campos.size() >= 2) 
            {
                Estudante::validarNome(campos[1]);
                nomeLido = campos[1];
                temNome = true;
            } else if (tipoRegistro == "CURSO" && campos.size() >= 3) 
            {
                int opcao = std::stoi(campos[1]);
                cursoLido.reset(new Curso(opcao, campos[2]));
            } else if (tipoRegistro == "SEMESTRE_CONSOLIDADO" && campos.size() >= 7) 
            {
                std::string idSem = campos[1];
                float nsg = std::stof(campos[2]);
                int hObrig = std::stoi(campos[3]);
                int hOpt = std::stoi(campos[4]);
                int hLivre = std::stoi(campos[5]);
                bool trancado = (std::stoi(campos[6]) != 0);

                SemestreConsolidado semCons(idSem, nsg, hObrig, hOpt, hLivre, trancado);
                if (historicoLido != nullptr) 
                {
                    historicoLido->adicionarSemestreConsolidado(semCons);
                } else 
                {
                    semestresConsolidadosLidos.push_back(semCons);
                }
            } else if (tipoRegistro == "SEMESTRE_ATUAL" && campos.size() >= 2) 
            {
                historicoLido.reset(new HistoricoEscolar(campos[1]));
                for (std::size_t i = 0; i < semestresConsolidadosLidos.size(); ++i) 
                {
                    historicoLido->adicionarSemestreConsolidado(semestresConsolidadosLidos[i]);
                }
                semestresConsolidadosLidos.clear();
                idUltimaDisciplina = -1;
            } else if (tipoRegistro == "DISCIPLINA" && campos.size() >= 12 && historicoLido != nullptr) 
            {
                int idDisc = std::stoi(campos[1]);
                std::string cod = campos[2];
                std::string turma = campos[3];
                std::string nomeDisc = campos[4];
                std::string prof = campos[5];
                std::string sala = campos[6];
                int ch = std::stoi(campos[7]);
                int duracao = std::stoi(campos[8]);
                std::string tipoDisc = campos[9];
                std::string horario = campos[10];
                int faltas = std::stoi(campos[11]);

                Disciplina disc(idDisc, cod, turma, nomeDisc, prof, sala, ch, duracao, tipoDisc, horario);
                disc.frequencia().setFaltasAtuais(faltas);
                historicoLido->getSemestreAtual()->adicionarDisciplina(disc);
                idUltimaDisciplina = idDisc;
            } else if (tipoRegistro == "ATIVIDADE" && campos.size() >= 7 && historicoLido != nullptr && idUltimaDisciplina != -1) 
            {
                int idAtiv = std::stoi(campos[1]);
                std::string nomeAtiv = campos[2];
                std::string dataAtiv = campos[3];
                float valorMax = std::stof(campos[4]);
                float notaObt = std::stof(campos[5]);
                bool concl = (std::stoi(campos[6]) != 0);

                Disciplina* disc = historicoLido->getSemestreAtual()->buscarDisciplina(idUltimaDisciplina);
                if (disc != nullptr) 
                {
                    disc->avaliacoes().adicionarAtividade(idAtiv, nomeAtiv, dataAtiv, valorMax, notaObt, concl);
                }
            } else 
            {
                throw std::runtime_error("Linha com formato desconhecido ou incompleto.");
            }
        }
    } catch (const std::exception&) 
    {
        ifs.close();
        throw std::runtime_error("Arquivo de perfil corrompido ou com dados invalidos.");
    }

    ifs.close();

    if (!temNome || cursoLido == nullptr || historicoLido == nullptr) 
    {
        throw std::runtime_error("Arquivo de perfil incompleto ou corrompido.");
    }

    return std::unique_ptr<Estudante>(new Estudante(nomeLido, *cursoLido, *historicoLido));
}

std::string GerenciadorArquivo::getNomeArquivo() const 
{
    return this->_nomeArquivo;
}