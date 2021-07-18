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

bool Servidor::participa_servidor(int id) {
  for(int idParticipante : this->participantesIDs) {
    if(idParticipante == id) {
      return true;
    }
  } 

  return false;
}

void Servidor::remover_participante(int id) {
  int posicao = 0;
  for(int idParticipante : this->participantesIDs) {
    if(idParticipante == id) {
      break;
    }
    posicao++;
  }

  this->participantesIDs.erase(this->participantesIDs.begin()+posicao);
}

string Servidor::lista_participantes(vector<Usuario> usuarios) {
  vector<string> lista_usuarios;

  for(int id : this->participantesIDs) {
    for(Usuario usuario : usuarios) {
      if(usuario.id == id)
        lista_usuarios.push_back(usuario.nome);
    }
  }

  string usuarios_participantes = lista_usuarios[0];

  for(int i = 1; i < lista_usuarios.size(); i++) {
    usuarios_participantes = usuarios_participantes + "\n" + lista_usuarios[i];
  }

  return usuarios_participantes;
}

string Servidor::lista_canais() {
  string canais = "";

  if(this->canaisTexto.size() == 0)
    return "Nenhum canal nesse servidor";

  for(int i = 0; i < this->canaisTexto.size(); i++) {
    canais = canais + this->canaisTexto[i].get_nome();

    if(i != this->canaisTexto.size() - 1)
      canais = canais + "\n";
  }

  return canais;
}