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
./concordo < ../data/script_comandos.txt
```

## 🤖 Executando caso testes
<!--embora você não tenha documentado extensivamente, dá para ter alguma ideia dos testes pelo nome dos arquivos, vou considerar 100%-->
```console
./concordo < ../data/script_comandos.txt
./concordo < ../data/erros.txt
./concordo < ../data/criar_canal.txt
./concordo < ../data/entrar_canal.txt
./concordo < ../data/sair_canal.txt
./concordo < ../data/enviar_mensagem.txt
```
