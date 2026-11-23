# Sistema de Acompanhamento Estudantil

![C++11](https://img.shields.io/badge/C%2B%2B-11-00599C?style=flat&logo=cplusplus&logoColor=white)
![POO](https://img.shields.io/badge/Paradigma-POO-4A90E2?style=flat)
![Tests](https://img.shields.io/badge/Testes-doctest%20%2B%20gcov-2EA44F?style=flat)
![Docs](https://img.shields.io/badge/Docs-Doxygen-2C4AA8?style=flat)

Um sistema de terminal feito por alunos de Computação da UFMG para alunos de Computação da UFMG, criado para centralizar as principais informações que um estudante precisa acompanhar no dia a dia da graduação.

Desenvolvido como projeto final da disciplina **Programação e Desenvolvimento de Software II (PDS II)** — DCC/UFMG (2026/2).

---

## Sobre o Projeto

Durante a graduação, as informações acadêmicas do estudante ficam fragmentadas em diversos ambientes: notas distribuídas entre Moodle, SIGA UFMG e e-mails; controle de frequência nem sempre atualizado; e planos de ensino espalhados por disciplina. Essa descentralização dificulta ter uma visão clara do próprio desempenho ao longo do semestre.

O **Sistema de Acompanhamento Estudantil** resolve esse problema reunindo, em uma interface unificada no terminal, o acompanhamento completo da trajetória do aluno — desde a entrega de uma atividade avaliativa específica até o progresso geral de integralização do curso.

---

## Funcionalidades Principais

* **Progresso de Integralização Curricular:** acompanha o percentual total concluído do curso e o detalhamento por categoria (**Obrigatórias**, **Optativas** e **Formação Livre**), contemplando as matrizes curriculares de Ciência da Computação (pré e pós-reforma de 2025) e Sistemas de Informação.
* **Indicadores de Rendimento (NSG):** calcula automaticamente o **NSG parcial** do semestre em curso, o **NSG médio** (média aritmética dos semestres consolidados) e o **NSG global** (rendimento acumulado ponderado pelas horas integralizadas, considerando toda a graduação como um único período).
* **Gestão de Disciplinas e Avaliações:** permite cadastrar, editar e remover disciplinas e atividades avaliativas (ordenadas cronologicamente por data), exibindo nota obtida, média parcial, conceito parcial e conceito individual por atividade.
* **Controle de Frequência:** gerencia faltas atuais e calcula automaticamente o limite máximo permitido em cada disciplina com base na carga horária e na duração das aulas.
* **Consolidação de Semestres e Persistência:** suporta encerramento de semestre (normal ou trancado) e gravação/carregamento automático do perfil completo do estudante em arquivos `.txt`.

---

## Arquitetura do Sistema

O projeto foi estruturado em **arquitetura em camadas**, mantendo separação estrita entre as regras de negócio e a interface com o usuário:

* **Camada de Domínio (Model):** classes coesas e completamente desacopladas de `std::cin`/`std::cout`, responsáveis pelas regras acadêmicas, cálculos e invariantes (`Estudante`, `Curso`, `HistoricoEscolar`, `Semestre`, `SemestreAtual`, `SemestreConsolidado`, `Disciplina`, `ControleFrequencia`, `DiarioAtividades`, `AtividadeAvaliativa`, `Data` e classes utilitárias `CalculadorMedia`, `CalculadorConceito` e `CalculadorMaxFaltas`).
* **Camada de Interface (CLI / View):** telas polimórficas derivadas da classe abstrata `Menu` (`MenuInicial`, `MenuCadastroUsuario`, `MenuCarregarUsuario`, `MenuPrincipal`, `MenuDisciplina`, `MenuAtividadeAvaliativa`, `MenuFrequencia` e `MenuDetalhamentoDisciplina`), orquestradas por uma máquina de estados baseada em pilha (`SeletorMenu` com `std::stack<Menu*>`) e recebendo apenas as dependências mínimas necessárias.
* **Camada de Persistência:** encapsulada em `GerenciadorArquivo`, responsável por serializar e reconstruir todo o grafo de objetos do estudante em texto estruturado.

---

## Competências e Boas Práticas Aplicadas

Mais do que entregar um sistema funcional, o projeto foi construído de forma incremental ao longo do semestre e passou por ciclos constantes de **refatoração** à medida que novos conceitos de engenharia de software e C++ eram consolidados em aula:

* **Modelagem e Engenharia de Requisitos:** especificação prévia com **User Stories**, critérios de validação, **Cartões CRC** e diagramas de classe antes da implementação.
* **POO em C++11:** aplicação prática de abstração, encapsulamento, herança (`Semestre` e `Menu`), composição (`Estudante` → `Curso`/`HistoricoEscolar`; `Disciplina` → `ControleFrequencia`/`DiarioAtividades`), polimorfismo de inclusão (`virtual`/`override`) e polimorfismo paramétrico (`template` para sanitização de entradas), além de containers, iteradores e algoritmos da **STL**.
* **Refatoração Contínua e Gerência de Memória:** evolução da base de código para reduzir acoplamento, eliminar estados inconsistentes (*RAII* nos construtores), gerenciar memória de forma segura com `std::unique_ptr` e aplicar a **Regra dos Três** (cópia profunda em `HistoricoEscolar`).
* **Programação Defensiva e Exceções:** sanitização centralizada de entradas do terminal, barreiras de validação estáticas (*barricadas*) nas classes de domínio e tratamento estruturado de exceções (`try`/`catch`/`throw`).
* **Qualidade, Automação e Documentação:** suíte de testes unitários automatizados com **doctest**, análise de cobertura com **gcov**, build modular com rastreamento de dependências via **Makefile** e documentação técnica gerada com **Doxygen**.
* **Trabalho em Equipe:** desenvolvimento colaborativo por 5 integrantes utilizando Git e GitHub, com organização modular de arquivos e entregas incrementais por checkpoints.

---

## Estrutura de Diretórios

```text
.
├── src/            # Implementações (.cpp) das classes de domínio, persistência e menus
├── include/        # Cabeçalhos (.hpp) com contratos das classes e documentação Doxygen
├── tests/          # Testes unitários automatizados desenvolvidos com doctest
├── build/          # Arquivos objeto (.o) e rastreamento de dependências (.d) gerados na compilação
├── third_party/    # Bibliotecas externas auxiliares (doctest.h)
├── docs/           # Documentação técnica em HTML gerada pelo Doxygen
├── design/         # Artefatos de modelagem (User Stories, Cartões CRC e diagramas de classe)
├── matriculas/     # Persistência de dados (.txt com os perfis salvos dos estudantes)
├── Makefile        # Automação de compilação, execução, testes e cobertura (gcov)
├── Doxyfile        # Configuração de geração da documentação via Doxygen
├── .gitignore      # Regras de arquivos ignorados pelo Git
└── README.md
