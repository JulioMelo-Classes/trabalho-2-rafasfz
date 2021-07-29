#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <string>
#include <iostream>
#include <vector>

#include "canaltexto.h"
#include "usuario.h"
/*
CP1 classe servidor ok
*/
// Classe para o modelo de Servidor do concordo
class Servidor{
	private:
		int usuarioDonoId;  //<! inteiro com o id do dono do servidor
		std::string nome; //<! string com o nome do servidor
		std::string codigoConvite; //<! string com o código de convite do servidor
		std::string descricao; //<! string com a descrição do servidor
		std::vector<CanalTexto> canaisTexto; //<! vetor de CanalTexto com os canais do servidor
		std::vector<int> participantesIDs; //<! vetor de inteiro com os ids dos participantes do servidor

	public:
		/*! Construtor para inciar a classe
				@param usuarioDonoId inteiro contedo o id do usuario dono do servidor
				@param nome string contendo o nome do servidor
		*/
		Servidor(int usuarioDonoId, std::string nome);

		/*! Get para o nome do servidor
				@return string contendo o nome do servidor 
		*/
		std::string get_nome();

		/*! Get para o codigo convite
				@return string contendo o codigo de convite do servidor
		*/
		std::string get_codigo_contive();

		/*! Get para o id do usuario dono servidor
				@return um inteiro com o id do dono do servidor
		*/
		int get_dono_id();

		/*! Set para a descrição do servidor
				@param descricao string contendo a nova descrição do servidor
		*/
		void set_descricao(std::string descricao);

		/*! Set para o código de convite
				@param descricao string contendo o novo código de convite do servidor
		*/
		void set_codigoConvite(std::string codigoConvite);

		/*! Método para adicionar um participante no servidor
				@param id inteiro com o id do novo participante do servidor
		*/
		void add_participante(int id);

		/*! Método para adicionar um canal no servidor
				@param canal CanalTexto contendo o novo canal que será adicionado no servidor
		*/
		void add_canal_texto(CanalTexto canal);

		/*! Método para remover um participante do servidor
				@param id inteiro com o id do usuario que sera removido
		*/
		void remover_participante(int id);

		/*! Método para adicionar uma mensagem em um canal no servidor
				@param id inteiro com o id do usuario que esta enviando a mensagem
				@param nomeCanal string contendo o nome do canal que sera enviada a mensagem
				@param conteudo string contendo o conteudo da mensagem que sera enviada
		*/
		void add_mensagem_canal(int id, std::string nomeCanal, std::string conteudo);

		/*! Método para adicionar um paticipante no servidor
				@param id inteiro com o id do usuario que entrará no servidor
				@param codigoConvite string contendo o novo codigo de convite do servidor
				@return true caso o codigo do convite seja o mesmo e o usuario consiga entra no servidor false caso o contrario
		*/
		bool add_participante(int id, std::string codigoConvite);

		/*! Método para verificar se um usuario participa do servidor
				@param id inteiro com o id do usuario que entrará no servidor
				@return true caso participe do servidor, false caso o contrario
		*/
		bool participa_servidor(int id);

		/*! Método para verificar se um canal existe
				@param nome string com o nome do suposto canal
				@return true caso o canal exista, false caso o contrario
		*/
		bool canal_existe(std::string nome);

		/*! Método para listar os participantes do servidor
				@param usuarios vetor de Usuario com os usuarios do Concordo
				@return string com a lista de todos os participantes do servidor
		*/
		std::string lista_participantes(std::vector<Usuario> usuarios);

		/*! Método para listar os canais do servidor
				@return string com a lista de todos os canais do servidor
		*/
		std::string lista_canais();

		/*! Método para listar as mensagens de um canal do servidor
				@param usuarios vetor de Usuario com os usuarios do Concordo
				@param nomeCanal string contendo o nome do canal que sera visto as mensagens
				@return string com a lista de mensagens formatadas do canal
		*/
		std::string lista_mensagem_canal(std::vector<Usuario> usuarios, std::string nomeCanal);

};

#endif
