#include "user.h"
using namespace std;

User::User(string _id, string _nome, string _cidade, int _idade, int jogos_ganhos = 0, int jogos_totais = 0, int maquinas_frequentadas = 0, int _dinheiro_inicial = 40, int _dinheiro_atual = 40) {
	id = _id;
	nome = _nome;
	cidade = _cidade;
	idade = _idade;
	maq = NULL;
	dinheiro_inicial = _dinheiro_inicial;
	dinheiro_atual = _dinheiro_atual;
}

User::~User() {
}

string User::getID() {
	return id;
}

string User::getNome() {
	return nome;
}

string User::getCiddae() {
	return cidade;
}

int User::getIdade() {
	return idade;
}

void User::Show()
{
	cout << "ID: " << id << " NOME: " << nome << " CIDADE: " << cidade << " IDADE: " << idade << endl;
}

Maquina* User::getMaquina() {
	return maq;
}

void User::setMaquina(Maquina* m) {
	maq = m;
}

void User::Ganhou() {
	jogos_ganhos += 1;
}

int User::getGanhos() {
	return jogos_ganhos;
}

int User::getJogosTotais() {
	return jogos_totais;
}

void User::addJogosTotais() {
	jogos_totais++;
}

void User::removeMaquina() {
	maq = NULL;
}

void User::frequentouMaquina() {
	maquinas_frequentadas++;
}

void User::saiMaquina() {
	maquinas_frequentadas--;
}

int User::MaquinasFrequentadas() {
	return maquinas_frequentadas;
}

int User::getStarterMoney() {
	return dinheiro_inicial;
}

int User::getMoney() {
	return dinheiro_atual;
}

void User::addMoney(int money) {
	dinheiro_atual += money;
}

void User::removeMoney(int money) {
	dinheiro_atual -= money;
}

void User::setHora(string _hora_entrada) {
	hora_entrada = _hora_entrada;
}

string User::getHora() {
	return hora_entrada;
}
