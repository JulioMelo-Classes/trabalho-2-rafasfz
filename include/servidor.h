#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <string>
#include <iostream>
#include <vector>

#include "canaltexto.h"
#include "usuario.h"

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
		void add_canal_texto(CanalTexto canal);
		void remover_participante(int id);
		void add_mensagem_canal(int id, std::string nomeCanal, std::string conteudo);
		bool add_participante(int id, std::string codigoConvite);
		bool participa_servidor(int id);
		bool canal_existe(std::string nome);
		std::string lista_participantes(std::vector<Usuario> usuarios);
		std::string lista_canais();

};

#endif
