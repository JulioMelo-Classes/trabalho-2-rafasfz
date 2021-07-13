#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <iostream>

class Usuario{
	private:
		std::string senha;

	public:
		int id;
		std::string nome;
		std::string email;
		Usuario(int id, std::string nome, std::string email, std::string senha);

		std::string get_email();

		bool auth(std::string email, std::string senha);
};

#endif
