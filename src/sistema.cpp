#include "sistema.h"
#include <iostream>
#include <sstream>
#include <algorithm>

#include "usuario.h"

using namespace std;

/* COMANDOS */
string Sistema::quit() {
  return "Saindo...";
}

string Sistema::create_user (const string email, const string senha, const string nome) {
  Usuario novo_usuario(this->usuarios.size() + 1, nome, email, senha);

  for(Usuario usuario : this->usuarios) {
    if(usuario.get_email() == novo_usuario.get_email()) {
      return "Usuário já existe";
    }
  }

  this->usuarios.push_back(novo_usuario);

  return "Usuário criado";
}

string Sistema::login(const string email, const string senha) {

  for(Usuario usuario : this->usuarios) {
    if(usuario.auth(email, senha)) {
      usuariosLogados.insert(pair<int, pair<string, string>>(usuario.id, pair<string, string>("", "")));

      return "Logado como " + email;
    }
  }

  return "Senha ou usuário inválidos!";
}

string Sistema::disconnect(int id) {
  std::map< int, std::pair<std::string, std::string> >::iterator usuario = usuariosLogados.find(id);

  if(usuario != usuariosLogados.end()) {
    usuariosLogados.erase(id);
    string nome;
    for(auto usuarioLogado : this->usuarios) {
      if(usuarioLogado.id == id)
        nome = usuarioLogado.nome;
    }

    return "Desconectado usuário " + nome;
  }

  return "Não está conectado";
}

string Sistema::create_server(int id, const string nome) {
  return "create_server NÃO IMPLEMENTADO";
}

string Sistema::set_server_desc(int id, const string nome, const string descricao) {
  return "set_server_desc NÃO IMPLEMENTADO";
}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {
  return "set_server_invite_code NÃO IMPLEMENTADO";
}

string Sistema::list_servers(int id) {
  return "list_servers NÃO IMPLEMENTADO";
}

string Sistema::remove_server(int id, const string nome) {
  return "remove_server NÃO IMPLEMENTADO";
}

string Sistema::enter_server(int id, const string nome, const string codigo) {
  return "enter_server NÃO IMPLEMENTADO";
}

string Sistema::leave_server(int id, const string nome) {
  return "leave_server NÃO IMPLEMENTADO";
}

string Sistema::list_participants(int id) {
  return "list_participants NÃO IMPLEMENTADO";
}

string Sistema::list_channels(int id) {
  return "list_channels NÃO IMPLEMENTADO";
}

string Sistema::create_channel(int id, const string nome) {
  return "create_channel NÃO IMPLEMENTADO";
}

string Sistema::enter_channel(int id, const string nome) {
  return "enter_channel NÃO IMPLEMENTADO";
}

string Sistema::leave_channel(int id) {
  return "leave_channel NÃO IMPLEMENTADO";
}

string Sistema::send_message(int id, const string mensagem) {
  return "send_message NÃO IMPLEMENTADO";
}

string Sistema::list_messages(int id) {
  return "list_messages NÃO IMPLEMENTADO";
}




/* IMPLEMENTAR MÉTODOS PARA OS COMANDOS RESTANTES */
