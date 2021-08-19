#ifndef MENSAGEM_H
#define MENSAGEM_H

#include <string>
#include <iostream>
#include <vector>
#include <usuario.h>
/*
cp2 ok
*/
// Classe para o modelo de mensagens do concordo
class Mensagem{
	private:
		std::string dataHora; //<! string com a data e hora de quando a mensagem foi enviada
		int enviadaPor; //<! inteiro com o id do usuario que enviou a mensagem
		std::string conteudo;  //<! string com o conteudo da mensagem

	public:
		/*! Construtor para incializar a classe
				@param enviadaPor inteiro com o id do usuario que enviou a mensagem
				@param conteudo string contendo o conteudo da 
		*/
		Mensagem(int enviadaPor, std::string conteudo);

		/*! Recupera a mensagem com a string formatada
				@param usuarios vetor de usuarios para recuperar o nome de o usuario pelo id
				@return string com a mensagem formatada
		*/
		std::string get_message(std::vector<Usuario> usuarios);

};

#endif