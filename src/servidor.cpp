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

int Servidor::get_dono_id() {
  return this->usuarioDonoId;
}

void Servidor::set_descricao(std::string descricao) {
  this->descricao = descricao;
}

void Servidor::set_codigoConvite(std::string codigoConvite) {
  this->codigoConvite = codigoConvite;
}