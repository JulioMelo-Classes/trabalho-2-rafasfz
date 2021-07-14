#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <string>
#include <iostream>
#include <vector>

#include "canaltexto.h"

class Servidor{
	private:
		int usuarioDonoId;
		std::string nome;
		std::string codigoConvite;
		std::vector<CanalTexto> canaisTexto;
		std::vector<int> participantesIDs;

	public:
		Servidor(int usuarioDonoId, std::string nome);
		std::string get_nome();

};

#endif
