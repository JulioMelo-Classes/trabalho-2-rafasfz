# Projeto 2: Concordo
## Clone do Discord, para humanos mais civilizados.

Concordo é um sistema similar ao Discord, mas que funciona somente em modo texto em sem recursos de rede. A ideia é simular o "backend" do serviço de forma simplificada.


## 🖥️ Compilando o projeto

```console
git clone https://github.com/JulioMelo-Classes/trabalho-2-rafasfz.git
cd build
cmake ..
cmake --build .
```

## 🤖 Executando o projeto
Você pode rodar o sistema e em logo depois digitar os comandos seguidos de ENTER
```console
./concordo
```

Ou pode criar um arquivo de texto com uma lista de comandos (um por linha) e executar o sistema redirecionando esse arquivo como entrada padrão:
```console
./concordo < script_comandos.txt
```
