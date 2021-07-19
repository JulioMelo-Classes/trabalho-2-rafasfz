#ifndef CANALTEXTO_H
#define CANALTEXTO_H

#include <string>
#include <iostream>
#include <vector>
#include "usuario.h"
#include "mensagem.h"

class CanalTexto{
	private:
		std::string nome;
		std::vector<Mensagem> mensagens;

	public:
		CanalTexto(std::string nome);
		std::string get_nome();
		void add_mensagem(Mensagem msg);
		std::string list_messages(std::vector<Usuario> usuarios);
};

#endif
