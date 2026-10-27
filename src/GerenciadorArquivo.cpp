#include "GerenciadorArquivo.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>

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
    std::ifstream ifs(this->_nomeArquivo.c_str());
    return ifs.good();
}

void GerenciadorArquivo::salvar(const Estudante& estudante) const 
{
    std::ofstream ofs(this->_nomeArquivo.c_str());
    if (!ofs.is_open()) 
    {
        throw std::runtime_error("Nao foi possivel abrir o arquivo para salvar os dados.");
    }
    ofs << estudante.serializar();
    ofs.close();
}

Estudante GerenciadorArquivo::carregar() const 
{
    std::ifstream ifs(this->_nomeArquivo.c_str());
    if (!ifs.is_open()) 
    {
        throw std::runtime_error("Arquivo de perfil nao encontrado.");
    }

    Estudante estudante;
    estudante.getHistoricoEditavel().limparSemestresPassados();
    int idUltimaDisciplina = -1;

    std::string linha;
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
            estudante.setNome(campos[1]);
        } else if (tipoRegistro == "CURSO" && campos.size() >= 3) 
        {
            int opcao = std::atoi(campos[1].c_str());
            Curso novoCurso(opcao, campos[2]);
            estudante.setCurso(novoCurso);
        } else if (tipoRegistro == "SEMESTRE_CONSOLIDADO" && campos.size() >= 7) 
        {
            std::string idSem = campos[1];
            float nsg = static_cast<float>(std::atof(campos[2].c_str()));
            int hObrig = std::atoi(campos[3].c_str());
            int hOpt = std::atoi(campos[4].c_str());
            int hLivre = std::atoi(campos[5].c_str());
            bool trancado = (std::atoi(campos[6].c_str()) != 0);

            SemestreConsolidado semCons(idSem, nsg, hObrig, hOpt, hLivre, trancado);
            estudante.getHistoricoEditavel().adicionarSemestreConsolidado(semCons);
        } else if (tipoRegistro == "SEMESTRE_ATUAL" && campos.size() >= 2) 
        {
            estudante.getHistoricoEditavel().definirSemestreAtual(campos[1]);
            idUltimaDisciplina = -1;
        } else if (tipoRegistro == "DISCIPLINA" && campos.size() >= 12) 
        {
            int idDisc = std::atoi(campos[1].c_str());
            std::string cod = campos[2];
            std::string turma = campos[3];
            std::string nomeDisc = campos[4];
            std::string prof = campos[5];
            std::string sala = campos[6];
            int ch = std::atoi(campos[7].c_str());
            int duracao = std::atoi(campos[8].c_str());
            std::string tipoDisc = campos[9];
            std::string horario = campos[10];
            int faltas = std::atoi(campos[11].c_str());

            Disciplina disc(idDisc, cod, turma, nomeDisc, prof, sala, ch, duracao, tipoDisc, horario);
            disc.frequencia().setFaltasAtuais(faltas);
            estudante.getHistoricoEditavel().getSemestreAtual()->adicionarDisciplina(disc);
            idUltimaDisciplina = idDisc;
        } else if (tipoRegistro == "ATIVIDADE" && campos.size() >= 7 && idUltimaDisciplina != -1) 
        {
            int idAtiv = std::atoi(campos[1].c_str());
            std::string nomeAtiv = campos[2];
            std::string dataAtiv = campos[3];
            float valorMax = static_cast<float>(std::atof(campos[4].c_str()));
            float notaObt = static_cast<float>(std::atof(campos[5].c_str()));
            bool concl = (std::atoi(campos[6].c_str()) != 0);

            Disciplina* disc = estudante.getHistoricoEditavel().getSemestreAtual()->buscarDisciplina(idUltimaDisciplina);
            if (disc != nullptr) 
            {
                disc->avaliacoes().adicionarAtividade(idAtiv, nomeAtiv, dataAtiv, valorMax, notaObt, concl);
            }
        }
    }

    ifs.close();
    return estudante;
}

std::string GerenciadorArquivo::getNomeArquivo() const 
{
    return this->_nomeArquivo;
}