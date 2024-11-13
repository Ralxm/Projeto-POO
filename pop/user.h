#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <sstream>
using namespace std;

class Maquina;

class User {
	Maquina* maq;
	string id;
	string nome;
	string cidade;
	int idade;
	int jogos_totais;
	int jogos_ganhos;
	int dinheiro_inicial;
	int dinheiro_atual;
	int maquinas_frequentadas;
	string hora_entrada;
public:
	User();
	~User();
	User(string _id, string _nome, string _cidade, int _idade, int jogos_ganhos, int jogos_totais, int maquinas_frequentadas, int dinheiro_inicial, int dinheiro_atual);
	string getID();
	string getNome();
	string getCiddae();
	int getIdade();
	void Show();
	Maquina* getMaquina();
	void setMaquina(Maquina* m);
	void Ganhou();
	int getGanhos();
	int getJogosTotais();
	void addJogosTotais();
	void removeMaquina();
	void frequentouMaquina();
	void saiMaquina();
	int MaquinasFrequentadas();
	int getStarterMoney();
	int getMoney();
	void addMoney(int money);
	void removeMoney(int money);
	void setHora(string _hora_entrada);
	string getHora();
};


class Restaurante {
private:
	int id;
	string nome;
	string morada;
	string codigoPostal;
	string horaAbertura; //dateTime
	string horaFecho; //dateTime
public:
	Restaurante();
	int getID();
	string getNome();
	string getMorada();
	string getCodigoPostal();
	string getHoraAbertura();
	string getHoraFecho();
};

class Menu {
private:
	int id;
	string nome;
	float preço;
public:
	Menu(int _id, string _nome, float _preço);
	int getID();
	string getNome();
	float getPreço;
};

class Pedido {
private:
	int id;
	string moradaEntrega;
	string dataPedido; //dateTime
public:
	Pedido(int _id, string _morada, string _dataPedido);
	int getID();
	string getMoradaEntrega();
	string dataPedido();
};

class Cliente {
private:
	int id;
	string nome;
	string morada;
	int telemóvel;
	string email;
public:
	Cliente(int _id, string _nome, string _morada, int _telemovel, string _email);
	int getID();
	string getNome();
	string getMorada();
	int getTelemovel();
	string getEmail();
};

class Pagamento { //Parte integral do pedido
private:
	int id;
	string dataPagamente; //dateTime
	float totalPreço;
public:
	Pagamento();
	int getID();
	string getDataPagamento();
	float getValor();
};

class Estado { //Parte integral do pedido
private:
	string estadoAtual;
	string dataUltimaAtualização; //dateTime
public:
	Estado();
	string getEstado();
	string getDataAtualização();
};

class PagamentoMBWay : public Pagamento {
private:
	int idPagamento;
	int telemovel;
public:
	PagamentoMBWay();
	int getIdPagamento();
	int getTelemovel();
};

class PagamentoCartão : public Pagamento {
private:
	int idPagamento;
	int numCartão;
	int mesValidade;
	int anoValidade;
	int cvc;
public:
	PagamentoCartão();
	int getIdPagamento();
	int getNumCartao();
	int getMesValidade();
	int getAnoValidade();
	int getCVC();
};

class PagamentoPayPal : public Pagamento {
private:
	int idPagamento;
public:
	PagamentoPayPal();
	int getIdPagamento();
};

class Entregador {
private:
	int idEntregador;
	string matricula;
	float rating;
	string nome;
	string dataNascimento; //dateTime
public:
	Entregador();
	int getID();
	string getMatricula();
	float getRating();
	string getNome();
	string getNascimento();
};