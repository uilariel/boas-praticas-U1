#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Atendimento {
  string cliente;
  string profissional;
  string data;
  int horario;
  int duração_em_minutos;
  string status;
};

vector<Atendimento> agenda;

bool validar_horario(float &horario) { return horario >= 8 && horario <= 17; }

bool validar_duração(int &duração_em_minutos) {
  return duração_em_minutos % 15 == 0 and duração_em_minutos > 0 and 
         duração_em_minutos <= 120;
}

/**
 * @brief Valida a disponibilidade do profissional
 * 
 * Valida a disponibilidade do profissional por meio de data, horário e nome. Se tiver 
 * algum atendimento marcado para o profissional no mesmo dia e horário, retorna falso.
 * 
 * @param profissional Nome do profissional
 * @param data Data do atendimento (AAAA-MM-DD)
 * @param horario Horário do atendimento 
 * @return true Se o profissional estiver disponível e falso caso contrário. 
 * 
 */

// Só compara o horário de início, e não a sobreposição das durações,
// porque o horário é guardado como hora cheia e isso mantém simples.

bool validar_disponibilidade(string &profissional, string &data, float &horario) {
  bool disponibilidade = true;
  int tamanho = agenda.size();

  for (int cliente = 0; cliente < tamanho; cliente++) {
    if (agenda[cliente].data == data && agenda[cliente].horario == horario &&
        agenda[cliente].profissional == profissional) {
      disponibilidade = false;
      return disponibilidade;
    }
  }

  return disponibilidade;
}

/**
 * @brief Valida a data no formato AAAA-MM-DD
 * 
 * Valida a data por meio das posições dos caracteres e do tamanho da string data. 
 * 
 * @param data Data no formato AAAA-MM-DD
 * @return true Se a data for válida e falsa caso contrário. 
 * 
 */
bool validar_data(string data) {
  if (data.length() != 10)
    return false;

  string ano;
  string mes;
  string dia;

  for (int i = 0; i < data.size(); i++) {
    if ((i == 4 or i == 7) and (data.at(i) != '-'))
      return false;
    if (i <= 3)
      ano.push_back(data.at(i));
    if (i == 5 or i == 6)
      mes.push_back(data.at(i));
    if (i == 8 or i == 9)
      dia.push_back(data.at(i));
  }

  int ano_valor;
  int mes_valor;
  int dia_valor;

  try {
    ano_valor = stoi(ano);
    mes_valor = stoi(mes);
    dia_valor = stoi(dia);

  } catch (...) {
    return false;
  }

  if (ano_valor < 1 or mes_valor <= 0 or dia_valor <= 0)
    return false;
  
  if (mes_valor > 12 or dia_valor > 30)
    return false;

  return true;
}

void adicionar_consulta(string cliente, string profissional, string data,
                       int horario, int duração_em_minutos) {

  agenda.push_back(
      {cliente, profissional, data, horario, duração_em_minutos, "MARCADO"});

  cout << "Atendimento marcado para " << cliente << endl;
}

/**
 * @brief Agenda um atendimento 
 * 
 * Valida o horário, duração, data e disponibilidade do profissional antes de agendar o atendimento.
 * 
 * @param cliente Nome do cliente
 * @param profissional Nome do profissional
 * @param data Data do atendimento (AAAA-MM-DD)
 * @param horario Horário do atendimento 
 * @param duração_em_minutos Duração do atendimento em minutos
 * 
 */
void agendar_atendimento(string cliente, string profissional, string data,
                         float horario, int duração_em_minutos) {

  if (!validar_horario(horario)) {

    cout << "Horário inválido" << endl;
    return;
  }

  if (!validar_duração(duração_em_minutos)) {
    cout << "duração inválida" << endl;
    return;
  }

  if ((horario + ((float)duração_em_minutos / 60)) > 18) {
    cout << "Horário inválido. A consulta deve terminar até as 18h.\n";
    return;
  }

  if (!validar_data(data)){
    cout << "Data inválida. Insira no formato AAAA-MM-DD.\n";
    return;
  }

  if (!validar_disponibilidade(profissional, data, horario)) {
    cout << "Horário ocupado" << endl;
    return;
  }

  adicionar_consulta(cliente, profissional, data, horario, duração_em_minutos);
}

/**
 * @brief Extrai a consulta da agenda
 * 
 * Extrai a consulta da agenda por meio do nome do cliente, data e horário. 
 * 
 * @param cliente Nome do cliente
 * @param data Data do atendimento (AAAA-MM-DD)
 * @param horario Horário do atendimento 
 * @return int Índice da consulta na agenda ou -1 caso não seja encontrada.
 */
int extrair_consulta(string cliente, string data, float horario) {

  int consulta = -1;

  for (int i = 0; i < agenda.size(); i++) {
    if (agenda[i].cliente == cliente && agenda[i].data == data &&
        agenda[i].horario == horario) {
      consulta = i;
      return consulta;
    }
  }

  return consulta;
}

/**
 * @brief Valida a disponibilidade para remarcar um atendimento
 * 
 * Verifica se o profissional está disponível para remarcar o atendimento em uma nova data e horário.
 * 
 * @param consulta Índice da consulta na agenda
 * @param novo_horario Novo horário para o atendimento
 * @param nova_data Nova data para o atendimento
 * @return true Se o profissional estiver disponível e falso caso contrário.
 */
bool validar_disponibilidade_de_remarcar(int consulta, float novo_horario,
                                         string nova_data) {
  string profissional = agenda[consulta].profissional;
  string data = agenda[consulta].data;
  int horario = agenda[consulta].horario;

  for (int i = 0; i < agenda.size(); i++) {
    if (data == nova_data && horario == novo_horario &&
        agenda[i].profissional == profissional) {
      return false;
    }
  }

  return true;
}

void atualizar_consulta(int consulta, string nova_data, float novo_horario) {
  agenda[consulta].data = nova_data;
  agenda[consulta].horario = novo_horario;
  cout << "Remarcado" << endl;
}

/**
 * @brief Remarca um atendimento
 * 
 * Verifica a disponibilidade do profissional antes de remarcar a consulta, por meio 
 * da função validar_disponibilidade_de_remarcar. 
 * 
 * @param cliente Nome do cliente
 * @param data Data do atendimento (AAAA-MM-DD)
 * @param horario Horário do atendimento 
 * @param nova_data Nova data do atendimento 
 * @param novo_horario Novo horário do atendimento 
 * 
 */
void remarcar_atendimento(string cliente, string data, float horario,
                          string nova_data, float novo_horario) {
  // remarca o atendimento
  int consulta = extrair_consulta(cliente, data, horario);

  if (consulta == -1) {
    cout << "Os dados do agendamento inserido nao foram encontrados no sistema"
         << endl;
    return;
  }

  if (!validar_disponibilidade_de_remarcar(consulta, novo_horario, nova_data)) {
    cout << "O horario desejado nao está disponivel! " << endl;
    return;
  }

  if (!validar_data(nova_data)) {
    cout << "Nova data é inválida, não foi possível remarcar. Insira no formato AAAA-MM-DD.\n";
    return;
  }

  if (!validar_horario(novo_horario)) {
    cout << "Novo horário é inválido, não foi possível remarcar.\n";
    return;
  }

  if ((novo_horario + ((float)agenda[consulta].duração_em_minutos / 60)) > 18) {
    cout << "Novo horário é inválido. A consulta deve terminar até as 18h.\n";
    return;
  }  

  atualizar_consulta(consulta, nova_data, novo_horario);
}


string extrair_mes(string data) {
  string mes;
  mes.push_back(data[5]);
  mes.push_back(data[6]);

  return mes;
}

/**
 * @brief Lista os atendimentos de um determinado mês
 * 
 * Descobre os atendimentos do mês, por meio da função extrair_mes e os lista. 
 * 
 * @param mes Mês no formato MM
 */
void listar_atendimentos_mes(string mes) {
  bool tem_atendimento = false;

  for (int i = 0; i < agenda.size(); i++) {
    string mes_atual = extrair_mes(agenda[i].data);
    if (mes_atual == mes) {
      tem_atendimento = true;

      cout << agenda[i].data << " " << agenda[i].horario << " " << agenda[i].cliente 
           << " " << agenda[i].profissional << " " << agenda[i].status << endl;
    }
  }

  if (tem_atendimento == false)
    cout << "Sem atendimentos marcados para o mês indicado.\n";
}

int main() {
  agendar_atendimento("Ana", "Dr. Silva", "2026-08-20", 9.5, 120);
  return 0;
}
