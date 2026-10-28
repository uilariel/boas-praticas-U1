# Projeto da Unidade 1 - AgendaFácil 

Uma agenda de uma pequena clínica com a função de marcar atendimentos, remarcar
e listar os atendimentos agendados. 

## Sobre os arquivos 

- 'agenda_base': Contém a implementação de todo o código da agenda 
- 'README.md': Documentação com instruções para compilar e executar e uma breve explicação do programa. 
- 'docs': Pasta da documentação com arquivos gerados pelo doxygen
- 'Doxyfile': Arquivo utilizado pelo doxygen para gerar a documentação 

## Como compilar e executar 

### Requisitos: 

Compilador `g++` com suporte a C++17.

Para compilar, entre na pasta do programa e utilize o seguinte comando no terminal: 

``` bash
g++ -std=c++17 -o programa.exe agenda_base.cpp 
```

Para executar: 

``` bash
./programa.exe 
```

## Documentação 

A documentação foi gerada pelo Doxygen. Para ter acesso, entre na pasta 'docs' e abra o arquivo html 'index' 