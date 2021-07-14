#include "servidor.h"
#include <iostream>
#include <string>

using namespace std;

Servidor::Servidor(int usuarioDonoId, std::string nome) {
  this->usuarioDonoId = usuarioDonoId;
  this->nome = nome;
}

string Servidor::get_nome() {
  return this->nome;
}