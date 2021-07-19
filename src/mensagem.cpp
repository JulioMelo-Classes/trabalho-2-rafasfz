#include "mensagem.h"
#include <iostream>
#include <string>
#include <time.h>
#include <sstream>

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

  ss << dataHora->tm_mday;
  ss >> dia;

  ss << (dataHora->tm_mon + 1);
  ss >> mes;

  ss << dataHora->tm_year;
  ss >> ano;

  ss << dataHora->tm_hour;
  ss >> hora;

  ss << dataHora->tm_min;
  ss >> minuto;


  this->dataHora = "<" + dia + "/" + mes + "/" + ano + " - " + hora + ":" + minuto + ">";
}
