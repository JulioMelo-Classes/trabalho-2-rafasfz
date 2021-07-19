#ifndef MENSAGEM_H
#define MENSAGEM_H

#include <string>
#include <iostream>
#include <vector>
#include <usuario.h>

class Mensagem{
	private:
		std::string dataHora;
		int enviadaPor;
		std::string conteudo;

	public:
		Mensagem(int enviadaPor, std::string conteudo);
		std::string get_message(std::vector<Usuario> usuarios);

};

#endif