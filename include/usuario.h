#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <iostream>

class Usuario{
	private:
		int id;
		std::string nome;
		std::string email;
		std::string senha;

	public:
		Usuario(int id, std::string nome, std::string email, std::string senha);

		std::string get_email();
};

#endif
