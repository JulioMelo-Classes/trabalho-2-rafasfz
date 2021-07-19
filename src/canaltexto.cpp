#include "canaltexto.h"
#include <iostream>
#include <string>
#include <vector>
#include "usuario.h"

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

std::string CanalTexto::list_messages(std::vector<Usuario> usuarios) {

  if(this->mensagens.size() == 0) {
    return "Sem mensagens para exibir";
  }

  string allmessages = "";

  for(int i = 0; i < this->mensagens.size(); i++) {
    allmessages = allmessages + this->mensagens[i].get_message(usuarios);
    if(i != this->mensagens.size() - 1)
      allmessages = allmessages + "\n";
  }

  return allmessages;

}