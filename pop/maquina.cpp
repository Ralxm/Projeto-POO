#include "maquina.h"
#include "user.h"
using namespace std;

Maquina::Maquina(int _id, string _nome, int _prob_ganhar, int _custo, int _premio, int _x, int _y, int _temperatura, User* u, int _dinheiroFeito, int _dinheiroDistribuido, int _jogosJogados) {
	id = _id;
	nome = _nome;
	prob_ganhar = _prob_ganhar;
	premio = _premio;
	custo = _custo;
	x = _x;
	y = _y;
	temperatura_max = _temperatura;
	temperatura_atual = 30;
	state = 1;
	dinheiroFeito = 0;
	dinheiroDistribuido = 0;
	jogosJogados = 0;
	u = NULL;
}

Maquina::~Maquina()
{

}

void Maquina::Set_Estado(int _state) {
	state = _state;
}

int Maquina::Get_Estado() {
	return state;
}

int Maquina::Get_ID() {
	return id;
}

string Maquina::Get_Nome() {
	return nome;
}

int Maquina::Get_X() {
	return x;
}

int Maquina::Get_Y() {
	return y;
}

int Maquina::get_Prob() {
	return prob_ganhar;
}

int Maquina::Get_Temp() {
	return temperatura_atual;
}

int Maquina::Get_TempMax() {
	return temperatura_max;
}

User* Maquina::getUser() {
	return jogador;
}

void Maquina::setUser(User* user) {
	jogador = user;
}

void Maquina::Run() {
	temperatura_atual += 1;
}

void Maquina::RunAvariada() {
	temperatura_atual -= 1;
}

void Maquina::RemoveUser() {
	jogador = NULL;
}

int Maquina::getPremio() {
	return premio;
}

int Maquina::getCusto() {
	return custo;
}

void Maquina::addJogosJogados(int num) {
	jogosJogados++;
}
int Maquina::getJogosJogados() {
	return jogosJogados;
}
void Maquina::addDinheiroFeito(int num) {
	dinheiroFeito += num;
}
int Maquina::getDinheiroFeito() {
	return dinheiroFeito;
}
void Maquina::addDinheiroDistribuido(int num) {
	dinheiroDistribuido += num;
}
int Maquina::getDinheiroDistribuido() {
	return dinheiroDistribuido;
}