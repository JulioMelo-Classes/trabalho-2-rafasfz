#include "mensagem.h"
#include <iostream>
#include <string>
#include <time.h>
#include <sstream>
#include <vector>
#include <usuario.h>

using namespace std;

Mensagem::Mensagem(int enviadaPor, string conteudo) {
  this->enviadaPor = enviadaPor;
  this->conteudo = conteudo;

  struct tm *dataHora;

  time_t segundos;
  time(&segundos);

  dataHora = localtime(&segundos);

  string dia, mes, ano, hora, minuto;

  stringstream ss;

  dia = dataHora->tm_mday < 10 ? "0" + to_string(dataHora->tm_mday) : to_string(dataHora->tm_mday);
  
  mes = (dataHora->tm_mon + 1) < 10 ? "0" + to_string(dataHora->tm_mon + 1) : to_string(dataHora->tm_mon + 1);

  ano = to_string(dataHora->tm_year + 1900);

  hora = dataHora->tm_hour < 10 ? "0" + to_string(dataHora->tm_hour) : to_string(dataHora->tm_hour);

  minuto = dataHora->tm_min < 10 ? "0" + to_string(dataHora->tm_min) : to_string(dataHora->tm_min);

  this->dataHora = "<" + dia + "/" + mes + "/" + ano + " - " + hora + ":" + minuto + ">";
}

std::string Mensagem::get_message(std::vector<Usuario> usuarios) {
  string nome_usuario;

  for(Usuario user : usuarios) {
    if(user.id == this->enviadaPor) {
      nome_usuario = user.nome;
      break;
    }
  }

  string full_message = nome_usuario + this->dataHora + ": " + this->conteudo;

  return full_message;
}
