#include "usuario.h"
#include <iostream>
#include <string>

using namespace std;

Usuario::Usuario(int id, std::string nome, std::string email, std::string senha) {
  this->nome = nome;
  this->email = email;
  this->senha = senha;
  this->id = id;

}

string Usuario::get_email() {
  return this->email;
}