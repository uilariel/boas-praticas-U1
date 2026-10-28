// ==========================================================
// Arquivo: agenda_base.cpp
// Autor: Equipe de estagiarios - 03/02/2024
// Alterado por: Joao - 15/05/2025
// Alterado por: Marina - 09/01/2026
// ==========================================================

#include <iostream>
#include <string>
#include <vector>
using namespace std;
/*
d = data
dur = duração (minutos)
h = Horario
p = pessoa (cliente)
pr = profissional
*/
struct Atendimento {
  string cliente;
  string profissional;
  string data;
  int horario;
  int duração_em_minutos;
  string status;
};

vector<Atendimento> agenda;
/*
 ========================================================================================================
 MODIFICAÇÕES NA FUNÇÃO DE AGENDAR ATENDIMENTO
 => função separada pra validar horario
 => função separada pra validar a duração da conuslta (maior que 0);
 => função unica para verificar se ja tem uma consulta marcada com esse
 profissional nesse mesmo dia e horario
 => função que adciona a consulta na agenda
 */

bool validar_horario(int &horario) { return horario >= 8 && horario <= 17; }

bool validar_duração(int &duração_em_minutos) { return duração_em_minutos > 0; }
bool validar_disponibilidade(string &profissional, string &data, int &horario) {
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

void adcionar_consulta(string cliente, string profissional, string data,
                       int horario, int duração_em_minutos) {

  agenda.push_back(
      {cliente, profissional, data, horario, duração_em_minutos, "MARCADO"});

  cout << "Atendimento marcado para " << cliente << endl;
}

void agendar_atendimento(string cliente, string profissional, string data,
                         int horario, int duração_em_minutos) {

  if (!validar_horario(horario)) {

    cout << "horario invalido" << endl;
    return;
  }

  if (!validar_duração(duração_em_minutos)) {
    cout << "duração inválida" << endl;
    return;
  }

  if (!validar_data(data)){
    cout << "Data inválida. Insira no formato AAAA-MM-DD.\n";
    return;
  }

  if (!validar_disponibilidade(profissional, data, horario)) {
    cout << "Horario Ocupado" << endl;
    return;
  }

  adcionar_consulta(cliente, profissional, data, horario, duração_em_minutos);
}
//=========================================================================================
//  =====================================BLOCO_2===========================================
//=========================================================================================

/*
 FUNCAO DE REMARCAR O ATENDIMENTO: ETAPAS :;:::::
 => CHECA SE EXISTE ALGUM CLIENTE COM ESSE MESMO NOME, DATA E HORARIO.
 => CHECA SE O HORARIO QUE ESTAMOS QUERENDO JA TEM ALGUMA CONSULTA MARCADA NELE
 com esse profissional;
 => REMARCA CASO ESTEJA TUDO CERTO
 */

int extrair_consulta(string cliente, string data, int horario) {

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

bool validar_disponibilidade_de_remarcar(int consulta, int novo_horario,
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

void atualizar_consulta(int consulta, string nova_data, int novo_horario) {
  agenda[consulta].data = nova_data;
  agenda[consulta].horario = novo_horario;
  cout << "Remarcado" << endl;
}

void remarcar_atendimento(string cliente, string data, int horario,
                          string nova_data, int novo_horario) {
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

  atualizar_consulta(consulta, nova_data, novo_horario);
}

// void desmarcar(string p, string d, int h) {
//     ag.erase(...);
// }

// TODO: função de desmarcar consulta (Joao, 2025)
/*
 =============================================================================================
 ===============================BLOCO
 3=======================================================
 =============================================================================================

  FUNCAO DE LISTAR ATENDIMENTOS;

*/
string extrair_mes(string data) {
  string mes;
  mes.push_back(data[5]);
  mes.push_back(data[6]);

  return mes;
}

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
  agendar_atendimento("Ana", "Dr. Silva", "2026-08-20", 9.67, 123);
  return 0;
}
