#ifndef MENSAGEM_H
#define MENSAGEM_H

#include <string>
#include <iostream>

class Mensagem{
	private:
		std::string dataHora;
		int enviadaPor;
		std::string conteudo;

	public:
		Mensagem(int enviadaPor, std::string conteudo);

};

#endif