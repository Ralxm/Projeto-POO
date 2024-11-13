#include <iostream>
using namespace std;

class User;

class Maquina {
	User* jogador;
	int id;
	string nome;
	int prob_ganhar;
	int custo;
	int premio;
	int state; //0 = OFF, 1 = ON, 2 = AVARIADA
	int x, y;
	int temperatura_atual;
	int temperatura_max;

	int dinheiroFeito;
	int dinheiroDistribuido;
	int jogosJogados;
public:
	Maquina(int _id, string _nome = "", int _prob_ganhar = 0, int _custo = 0, int _premio = 0, int _x = 0, int _y = 0, int _temperatura = 0, User* u = NULL, int _dinheiroFeito = 0, int _dinheiroDistribuido = 0, int _jogosJogados = 0);
	~Maquina();
	void Set_Estado(int _state);
	int Get_Estado();
	int Get_ID();
	string Get_Nome();
	int Get_X();
	int Get_Y();
	int Get_Temp();
	int Get_TempMax();
	virtual User* getUser();
	void setUser(User* user);
	int get_Prob();
	void Run();
	void RunAvariada();
	void RemoveUser();
	int getPremio();
	int getCusto();
	virtual string Get_Tipo() { return "MAQUINA"; }

	void addJogosJogados(int num);
	int getJogosJogados();
	void addDinheiroFeito(int num);
	int getDinheiroFeito();
	void addDinheiroDistribuido(int num);
	int getDinheiroDistribuido();

};

class Slots : public Maquina {
public:
	Slots(int _id, string _nome = "", int _prob_ganhar = 0, int _custo = 0, int _premio = 0, int _x = 0, int _y = 0, int _temperatura = 0, User* u = NULL)
		: Maquina(_id, _nome, _prob_ganhar, _custo, _premio, _x, _y, _temperatura, u) {}
	string Get_Tipo() {
		return "CLASSIC SLOTS";
	}
};

class Blackjack : public Maquina {
public:
	Blackjack(int _id, string _nome = "", int _prob_ganhar = 0, int _custo = 0, int _premio = 0, int _x = 0, int _y = 0, int _temperatura = 0, User* u = NULL)
		: Maquina(_id, _nome, _prob_ganhar, _custo, _premio, _x, _y, _temperatura, u) {}
	string Get_Tipo() {
		return "BLACKJACK";
	}
};

class Roleta : public Maquina {
public:
	Roleta(int _id, string _nome = "", int _prob_ganhar = 0, int _custo = 0, int _premio = 0, int _x = 0, int _y = 0, int _temperatura = 0, User* u = NULL)
		: Maquina(_id, _nome, _prob_ganhar, _custo, _premio, _x, _y, _temperatura, u) {}
	string Get_Tipo() {
		return "ROLETA";
	}
};

class Poker : public Maquina {
public:
	Poker(int _id, string _nome = "", int _prob_ganhar = 0, int _custo = 0, int _premio = 0, int _x = 0, int _y = 0, int _temperatura = 0, User* u = NULL)
		: Maquina(_id, _nome, _prob_ganhar, _custo, _premio, _x, _y, _temperatura, u){}
	string Get_Tipo() {
		return "POKER";
	}
};