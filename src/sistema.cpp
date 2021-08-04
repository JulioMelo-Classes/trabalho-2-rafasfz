#include "sistema.h"
#include <iostream>
#include <sstream>
#include <algorithm>

#include "usuario.h"
#include "servidor.h"
#include "canaltexto.h"
#include "mensagem.h"

using namespace std;

/* COMANDOS */
string Sistema::quit() {
  return "Saindo...";
}

string Sistema::create_user (const string email, const string senha, const string nome) {
  Usuario novo_usuario(this->usuarios.size(), nome, email, senha);

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
      if(this->usuario_logado(usuario.id)) {
        return "Você já esta logado";
      }

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
    return "Você não pode alterar o código de convite de um servidor que não foi criado por você";

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

  this->vizualizar_server_canal(id, "", "");

  return "Servidor '" + nome + "' removido";
}

string Sistema::enter_server(int id, const string nome, const string codigo) {
  if(!this->usuario_logado(id))
    return "Não está conectado";

  if(!this->servidor_existe(nome))
    return "Servidor '" + nome + "' não existe";

  Servidor *servidor;
  servidor = this->get_server(nome);

  if(servidor->participa_servidor(id))
    return "Você já participa desse servidor";

  if(this->usuario_dono_servidor(id, nome)) {
    servidor->add_participante(id);
    this->vizualizar_server_canal(id, nome, "");

    return "Entrou no servidor com sucesso";
  }

  if(servidor->add_participante(id, codigo)) {
    this->vizualizar_server_canal(id, nome, "");
    return "Entrou no servidor com sucesso"; 
  }

  if(codigo == "") {
    return "Servidor requer código de convite";
  }

  return "Código de convite errado";
}

string Sistema::leave_server(int id, const string nome) {
  if(!this->usuario_logado(id))
    return "Não está conectado";

  if(!this->servidor_existe(nome))
    return "Servidor '" + nome + "' não existe";

  Servidor *servidor;
  servidor = this->get_server(nome);

  if(!servidor->participa_servidor(id)) {
    return "Você não participa desse servidor";
  }

  servidor->remover_participante(id);

  std::map< int, std::pair<std::string, std::string> >::iterator usuario;
  usuario = this->usuariosLogados.find(id);

  if(usuario->second.first == nome)
    this->vizualizar_server_canal(id, "", "");

  return "Saindo do servidor '" + nome + "'";
}

string Sistema::list_participants(int id) {
  if(!this->usuario_logado(id))
    return "Não está conectado";

  std::map< int, std::pair<std::string, std::string> >::iterator usuario = usuariosLogados.find(id);

  if(usuario->second.first == "")
    return "Você não esta visualizando nenhum servidor";

  Servidor *servidor = this->get_server(usuario->second.first);
  
  string participantes = servidor->lista_participantes(this->usuarios);
  
  return participantes;
}

string Sistema::list_channels(int id) {
  if(!this->usuario_logado(id))
    return "Não está conectado";

  std::map< int, std::pair<std::string, std::string> >::iterator usuario = usuariosLogados.find(id);

  if(usuario->second.first == "")
    return "Você não esta visualizando nenhum servidor";

  Servidor *servidor = this->get_server(usuario->second.first);

  string canais = servidor->lista_canais();

  return canais;
}

string Sistema::create_channel(int id, const string nome) {
  if(!this->usuario_logado(id))
    return "Não está conectado";

  if(nome == "")
    return "Para criar um canal, escolha um nome";

  std::map< int, std::pair<std::string, std::string> >::iterator usuario = usuariosLogados.find(id);

  if(usuario->second.first == "")
    return "Você não esta visualizando nenhum servidor";

  Servidor *servidor = this->get_server(usuario->second.first);

  if(servidor->canal_existe(nome))
    return "Canal de texto ‘" + nome + "’ já existe!";

  CanalTexto novo_canal(nome);  

  servidor->add_canal_texto(novo_canal);

  return "Canal de texto ‘" + nome + "’ criado";
}

string Sistema::enter_channel(int id, const string nome) {
  if(!this->usuario_logado(id))
    return "Não está conectado";

  if(nome == "")
    return "Escreva o nome do canal no comando.";

  std::map< int, std::pair<std::string, std::string> >::iterator usuario = usuariosLogados.find(id);

  if(usuario->second.first == "")
    return "Você não esta visualizando nenhum servidor";

  Servidor *servidor = this->get_server(usuario->second.first);

  if(!servidor->canal_existe(nome))
    return "Canal ‘" + nome + "’ não existe no servidor " + usuario->second.first;

  usuario->second.second = nome;

  return "Entrou no canal ‘" + nome + "’";;
}

string Sistema::leave_channel(int id) {
  if(!this->usuario_logado(id))
    return "Não está conectado";

  std::map< int, std::pair<std::string, std::string> >::iterator usuario = usuariosLogados.find(id);

  if(usuario->second.first == "")
    return "Você não esta visualizando nenhum servidor";

  Servidor *servidor = this->get_server(usuario->second.first);

  usuario->second.first == "";
    
  return "Saindo do canal";
}

string Sistema::send_message(int id, const string mensagem) {
  if(!this->usuario_logado(id))
    return "Não está conectado";

  std::map< int, std::pair<std::string, std::string> >::iterator usuario = usuariosLogados.find(id);

  if(usuario->second.first == "")
    return "Você não esta visualizando nenhum servidor";

  if(usuario->second.second == "")
    return "Você não esta visualizando nenhum canal de texto";

  Servidor *servidor = this->get_server(usuario->second.first);

  servidor->add_mensagem_canal(id, usuario->second.second, mensagem);

  return "Mensagem enviada";
}

string Sistema::list_messages(int id) {
  if(!this->usuario_logado(id))
    return "Não está conectado";

  std::map< int, std::pair<std::string, std::string> >::iterator usuario = usuariosLogados.find(id);

  if(usuario->second.first == "")
    return "Você não esta visualizando nenhum servidor";

  if(usuario->second.second == "")
    return "Você não esta visualizando nenhum canal de texto";

  Servidor *servidor = this->get_server(usuario->second.first);

  return servidor->lista_mensagem_canal(this->usuarios, usuario->second.second);
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

  return nullptr;
}

void Sistema::vizualizar_server_canal(int id, std::string nomeServer, std::string nomeCanal) {
  std::map< int, std::pair<std::string, std::string> >::iterator usuario;

  usuario = this->usuariosLogados.find(id);
  usuario->second.first = nomeServer;
  usuario->second.second = nomeCanal;
}