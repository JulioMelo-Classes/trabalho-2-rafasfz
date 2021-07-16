#include "servidor.h"
#include <iostream>
#include <string>

using namespace std;

Servidor::Servidor(int usuarioDonoId, std::string nome) {
  this->usuarioDonoId = usuarioDonoId;
  this->nome = nome;
  this->codigoConvite = "";
}

string Servidor::get_nome() {
  return this->nome;
}

int Servidor::get_dono_id() {
  return this->usuarioDonoId;
}

string Servidor::get_codigo_contive() {
  return this->codigoConvite;
}

void Servidor::set_descricao(std::string descricao) {
  this->descricao = descricao;
}

void Servidor::set_codigoConvite(std::string codigoConvite) {
  this->codigoConvite = codigoConvite;
}

void Servidor::add_participante(int id) {
  this->participantesIDs.push_back(id);
}

bool Servidor::add_participante(int id, std::string codigoConvite) {

  if(codigoConvite == this->codigoConvite || this->codigoConvite == "") {
    this->participantesIDs.push_back(id);
    return true;
  }

  return false;
}

void vizualizar_server(int id, std::string nome) {
  
}