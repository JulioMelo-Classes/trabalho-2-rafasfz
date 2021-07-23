#ifndef CANALTEXTO_H
#define CANALTEXTO_H

#include <string>
#include <iostream>
#include <vector>
#include "usuario.h"
#include "mensagem.h"

// Classe para o modelo de Canal do concordo
class CanalTexto{
	private:
		std::string nome; //<! string com o nome do canal
		std::vector<Mensagem> mensagens;  //<! vetor de Mensagem que contem todas as mensagens enviadas no canal

	public:
		/*! Construtor para inciar a classe
				@param nome string contendo o nome do canal
		*/
		CanalTexto(std::string nome);

		/*! Get para o atributo nome
				@return sstring contendo o nome do canal
		*/
		std::string get_nome();
		
		/*! Adiciona mensagem no atributo mensagens
				@param msg mensagem que sera adicionada no vetor mensagens
		*/
		void add_mensagem(Mensagem msg);
		
		/*! Lista todas as mensagens em uma string formatada
				@param usuarios vetor de Usuario que sera usado para recuperação do nome nas mensagens
				@return string contendo todas as mensagens do canal formatadas
		*/
		std::string list_messages(std::vector<Usuario> usuarios);
};

#endif
