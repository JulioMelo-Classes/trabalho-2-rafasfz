#include "canaltexto.h"
#include <iostream>
#include <string>

using namespace std;

CanalTexto::CanalTexto(string nome) {
  this->nome = nome;
}

string CanalTexto::get_nome() {
  return this->nome;
}

void CanalTexto::add_mensagem(Mensagem msg) {
  this->mensagens.push_back(msg);
}