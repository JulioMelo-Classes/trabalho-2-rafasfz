#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <iostream>

/*
CP1 classe usuário ok
*/
// Classe para o modelo de usuarios do concordo
class Usuario{
	private:
		std::string senha;  //<! uma string com a senha do usuario

	public:
		int id; //<! um inteiro com id do usuario
		std::string nome; //<! uma string com nome do usuario
		std::string email; //<! uma string com o email do usuario

		/*! Construtor para incializar a classe
				@param id inteiro com o id do usuario
				@param nome string com o nome do usuario
				@param email string email do usuario
				@param senha string senha do usuario
		*/
		Usuario(int id, std::string nome, std::string email, std::string senha);

		/*! Get para o atributo email
				@return retorna uma string com o email do usuario
		*/
		std::string get_email();

		/*! Método para autenticar se o email e a senha do usuário estão corretas
				@param email string com o suposto email do usuario
				@param senha string com a suposta senha do usuario
				@return um booleano contedo true caso o email e a senha do usuario estejam corretas e false caso o contrario
		*/
		bool auth(std::string email, std::string senha);
};

#endif
