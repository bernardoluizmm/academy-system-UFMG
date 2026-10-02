Sistema Acadêmico

Trabalho prático da disciplina de Programação e Desenvolvimento de Software 2 (PDS2), UFMG, 2026/2. Grupo 42.

Integrantes

Bernardo Luiz Magri Mendes, Bernardo Koji Fuzikawa Bicalho Cotta, Lucas da Silva Venturini, Pedro Calijorne Soares Dias Alves e Samuel Coelho Facco.

Sobre o projeto

Durante a graduação, as informações acadêmicas de um estudante ficam espalhadas: as notas de cada atividade vão para planilhas ou para o caderno, a conta das faltas é feita de cabeça perto do fim do semestre, e quase ninguém sabe dizer ao certo quanto do curso já cumpriu em cada categoria de disciplinas. O problema que o grupo escolheu tratar é justamente esse: reunir tudo num só lugar, de forma que o estudante acompanhe o semestre em andamento e também a trajetória do curso como um todo.

O sistema é um programa em C++ que roda no terminal e mantém o perfil acadêmico de um estudante. Para o semestre atual, ele controla as disciplinas, as atividades avaliativas com suas notas e o limite de faltas de cada matéria, calculando o conceito parcial e a Nota Semestral Global (NSG). Para os semestres anteriores, guarda um histórico consolidado, a partir do qual calcula o percentual de integralização do curso por categoria (obrigatórias, optativas e formação livre) e mostra um gráfico de evolução da NSG. O perfil é salvo em arquivo de texto, então os dados continuam disponíveis na próxima vez que o programa for aberto.

A escolha foi motivada por ser um problema que o próprio grupo vive, o que ajuda a decidir o que realmente faz falta na ferramenta. Além disso, o domínio rende uma boa modelagem orientada a objetos: composição entre classes (disciplina, atividade, frequência), herança com polimorfismo (semestres e telas) e persistência em arquivo, que são justamente os conceitos trabalhados na disciplina.

Objetivos

O objetivo principal é oferecer ao estudante uma ferramenta simples para acompanhar a vida acadêmica sem depender apenas dos sistemas da UFMG, que normalmente não proporciona a melhor experiência de usuário. Para isso, o sistema permite cadastrar disciplinas, atividades avaliativas e notas do semestre atual, controlar as faltas de cada disciplina em relação ao limite permitido e calcular o conceito parcial de cada matéria e a NSG do semestre. Também mantém o histórico de semestres consolidados, acompanha o progresso de integralização do curso por categoria, exibe a evolução da NSG ao longo dos semestres e salva e carrega o perfil do estudante em arquivo .txt.

Organização do código

O projeto segue o padrão C++11/14 e usa composição por valor e containers da STL, sem alocação manual de memória. A interface é feita com cin/cout, e cada funcionalidade fica numa tela própria, todas herdando de uma classe abstrata Tela. Uma classe Menu apenas controla o loop principal e chama a tela escolhida.

As classes se dividem em quatro grupos. As classes de base são AtividadeAvaliativa, ControleFrequencia, CategoriaDisciplina e PontoGrafico. O domínio é formado por Disciplina e pela hierarquia Semestre, com SemestreAtual e SemestreConsolidado. O modelo e a persistência ficam a cargo de Curso, Estudante e GerenciadorPerfil. A apresentação reúne Tela, TelaMenuPrincipal, TelaPerfil, TelaPainel, TelaDisciplinas, TelaAtividades, TelaFrequencia, TelaHistorico e Menu.

Os cabeçalhos (.hpp), com as assinaturas e a documentação de cada classe, ficam na pasta include/, e as implementações (.cpp) ficam em src/. As pastas design/ e tests/ guardam, respectivamente, os cartões CRC e as user stories, e os testes.
