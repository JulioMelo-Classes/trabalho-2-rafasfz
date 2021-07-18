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
		std::string descricao;
		std::vector<CanalTexto> canaisTexto;
		std::vector<int> participantesIDs;

	public:
		Servidor(int usuarioDonoId, std::string nome);
		std::string get_nome();
		std::string get_codigo_contive();
		int get_dono_id();
		void set_descricao(std::string descricao);
		void set_codigoConvite(std::string codigoConvite);
		void add_participante(int id);
		void remover_participante(int id);
		bool add_participante(int id, std::string codigoConvite);
		bool participa_servidor(int id);

};

#endif
