Sistema de Acompanhamento Estudantil

Um sistema feito por alunos de computação da UFMG para alunos de computação da UFMG que busca centralizar as principais informações que um estudante pode precisar no 
contexto acadêmico. 

Trabalho prático da disciplina de Programação e Desenvolvimento de Software 2 (PDS2), UFMG, 2026/2. Grupo 42.
Integrantes:
1 - Bernardo Koji Fuzikawa Bicalho Cotta 
2 - Bernardo Luiz Magri Mendes
3 - Lucas da Silva Venturini
4 - Pedro Calijorne Soares Dias Alves
5 - Samuel Coelho Facco

Sobre:
	Durante a graduação, as informações acadêmicas de um estudante ficam espalhadas  em vários locais: as notas são lançadas em um local diferente a cada disciplina,
algumas na aba notas do moodle, outras no sigaUFMG, por emai-l, etc; a assiduidade nem sempre é recorrentemente atualizada e os planos de ensino não podem ser
acessados de maneira unificada. Toda essa descentralização de informações dos sistemas afastam o acesso à informações relevantes do dia a dia acadêmico do 
estudante.
	Nesse contexto, surge o nosso programa: uma plataforma centralizadora que permite o estudante lançar todas essas informações que consideramos 
relevantes na rotina acadêmica. Ele permite o estudante visualizar, em um só lugar, o percentual de horas do curso que já foram integralizadas no total, além de
separá-las por tipo de integralização(obrigatórias, formação livre e optativas), o NSG parcial do semestre atual, o NSG médio(média aritmética dos NSGs), o NSG 
"global"(parâmetro que explicita o rendimento total do aluno no curso até então,  o cálculo considera que todos os semestres são um só), nota total obtida
nas disciplinas em curso, o número de faltas e o número máximo de faltas permitidas em uma disciplina, conceito obtido na atividade e na disciplina(parcial), média 
parcial de uma disciplina e data das atividades avaliativas. 
	O sistema foi construído em C++11 seguindo as boas práticas de POO, Programação Orientada a Objetos, e coloca em prática a maioria dos conceitos vistos 
em sala de aula, como: encapsulamento, herança, composição, biblioteca STL, polimorfismo, programação defensiva, tratamento de exceção, etc. Além disso, ele roda no 
próprio terminal. Em relação aos diretórios, a disposição ficou assim: src/: contém os arquivos de código-fonte (.cpp) onde estão implementadas as lógicas das classes, 
include/: guarda os arquivos de cabeçalho (.hpp) com as declarações das classes e interfaces do sistema, tests/: armazena os arquivos de testes unitários automatizados
desenvolvidos com a biblioteca doctest, build/: diretório gerado na compilação para armazenar arquivos objeto (.o) e mapeamento de dependências (.d), third_party/: 
contém bibliotecas externas auxiliares, como o arquivo doctest.h, docs/: reservado para a documentação técnica em HTML gerada pelo Doxygen, design/: armazena arquivos 
de modelagem e diagramas de classe da arquitetura, matriculas/: diretório utilizado para a persistência de dados, guardando os arquivos .txt com as informações salvas 
de cada estudante, raiz do projeto: contém os arquivos de configuração geral, como o Makefile (automação), Doxyfile (configuração de documentação), .gitignore e o README.md.

Compilação e execução:
	O projeto utiliza um Makefile automatizado que gerencia a compilação separada de objetos e rastreia dependências. Os testes também podem ser compilados por
meio do makefile. Além disso, utilizamos o gcov para verificar a cobertura dos nossos testes e incluimos essa estrutura no makefile.