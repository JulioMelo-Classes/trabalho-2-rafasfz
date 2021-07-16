#include "sistema.h"
#include <iostream>
#include <sstream>
#include <algorithm>

#include "usuario.h"
#include "servidor.h"

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

  if(!this->usuario_logado(id)) {
    return "Não está conectado";
  }

  usuariosLogados.erase(id);
  string nome;
  for(auto usuarioLogado : this->usuarios) {
    if(usuarioLogado.id == id)
      nome = usuarioLogado.nome;
  }

  return "Desconectado usuário " + nome;
}

string Sistema::create_server(int id, const string nome) {

  if(!this->usuario_logado(id)) {
    return "Não está conectado";
  }

  for(Servidor servidor : this->servidores) {
    if(servidor.get_nome() == nome) {
      return "Servidor com esse nome já existe";
    }
  }
    
  Servidor novoServidor(id, nome);
  this->servidores.push_back(novoServidor);

  return "Servidor criado";

}

string Sistema::set_server_desc(int id, const string nome, const string descricao) {

  if(!this->usuario_logado(id))
    return "Não está conectado";

  if(!this->servidor_existe(nome))
    return "Servidor '" + nome + "' não existe";

  if(!this->usuario_dono_servidor(id, nome))
    return "Você não pode alterar a descrição de um servidor que não foi criado por você";

  for(int i = 0; i < this->servidores.size(); i++) {
    if(this->servidores[i].get_nome() == nome) {
      this->servidores[i].set_descricao(descricao);
      return "Descrição do servidor ‘" + this->servidores[i].get_nome() + "’ modificada!";
    }
  }

  return "Algum erro ocorreu";
}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {
  if(!this->usuario_logado(id))
    return "Não está conectado";

  if(!this->servidor_existe(nome))
    return "Servidor '" + nome + "' não existe";

  if(!this->usuario_dono_servidor(id, nome))
    return "Você não pode alterar a descrição de um servidor que não foi criado por você";

  for(int i = 0; i < this->servidores.size(); i++) {
    if(this->servidores[i].get_nome() == nome) {
      this->servidores[i].set_codigoConvite(codigo);

      if(codigo == "") {
        return "Código do servidor '" + this->servidores[i].get_nome() + "' removido!";
      } else {
        return "Código do servidor '" + this->servidores[i].get_nome() + "' modificado!";
      }
    }
  }

  return "Algum erro ocorreu";

}

string Sistema::list_servers(int id) {
  if(this->servidores.size() == 0) {
    return "";
  }

  string servidores_lista = this->servidores[0].get_nome();

  for(int i = 1; i < this->servidores.size(); i++)
    servidores_lista = servidores_lista + "\n" + this->servidores[i].get_nome();

  return servidores_lista;
}

string Sistema::remove_server(int id, const string nome) {
  if(!this->usuario_logado(id))
    return "Não está conectado";

  if(!this->servidor_existe(nome))
    return "Servidor '" + nome + "' não existe";

  if(!this->usuario_dono_servidor(id, nome))
    return "Você não pode alterar a descrição de um servidor que não foi criado por você";

  int posicao = 0;
  int posicao_atual = 0;
  for(Servidor servidor : this->servidores) {
    if(servidor.get_nome() == nome) {
      posicao = posicao_atual;
    }
    posicao_atual++;
  }


  this->servidores.erase(this->servidores.begin()+posicao);

  for(auto usuarioLogado : this->usuariosLogados) {
    if(usuarioLogado.second.first == nome) {
      usuarioLogado.second.first = "";
      usuarioLogado.second.second = "";
    }
  }

  return "Servidor '" + nome + "' removido";
}

string Sistema::enter_server(int id, const string nome, const string codigo) {
  if(!this->usuario_logado(id))
    return "Não está conectado";

  if(!this->servidor_existe(nome))
    return "Servidor '" + nome + "' não existe";

  Servidor *servidor;
  servidor = this->get_server(nome);

  if(this->usuario_dono_servidor(id, nome)) {
    servidor->add_participante(id);
    this->vizualizar_server(id, nome);

    return "Entrou no servidor com sucesso";
  }

  if(servidor->add_participante(id, codigo)) {
    this->vizualizar_server(id, nome);
    return "Entrou no servidor com sucesso"; 
  }

  if(codigo == "") {
    return "Servidor requer código de convite";
  }

  return "Código de convite errado";
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


bool Sistema::usuario_logado(int id) {
  std::map< int, std::pair<std::string, std::string> >::iterator usuario = usuariosLogados.find(id);

  if(usuario != usuariosLogados.end()) {
    return true;
  }

  return false;
}


bool Sistema::servidor_existe(std::string nome) {
  for(Servidor servidor : this->servidores) {
    if(servidor.get_nome() == nome) {
      return true;
    }
  }
  return false;
}

bool Sistema::usuario_dono_servidor(int id, std::string nome) {
  for(Servidor servidor : this->servidores) {
    if(servidor.get_nome() == nome) {
      if(servidor.get_dono_id() == id)
        return true;
      else
        return false;
    }    
  }
  return false;
}

Servidor* Sistema::get_server(std::string nome) {
  for(int i = 0; i < this->servidores.size(); i++) {
    if(this->servidores[i].get_nome() == nome) {
      return &this->servidores[i];
    }
  }

  return &this->servidores[0];
}

void Sistema::vizualizar_server(int id, std::string nome) {
  std::map< int, std::pair<std::string, std::string> >::iterator usuario;

  usuario = this->usuariosLogados.find(id);
  usuario->second.first = nome;
  usuario->second.second = "";
}