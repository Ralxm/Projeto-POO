#include "casino.h"
#include <ctime>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <algorithm>
#include <random>
#include "pugixml.hpp"
#include "XMLWriter.h"


using namespace std;
using namespace pugi;

Casino::Casino() {
	
}

Casino::~Casino() {
	cout << "O casino foi destruido";
}

bool Casino::LoadUsers(const string &_ficheiro) 
{
	ifstream file(_ficheiro);
	string line;
	string ID, NOME, CIDADE;
	int IDADE;
	string s;
	if (file.is_open()) {
		while (getline(file, line))
		{
			istringstream is(line);

			getline(is, ID, '\t');
			getline(is, NOME, '\t');
			getline(is, CIDADE, '\t');
			getline(is, s, '\t');
			IDADE = stoi(s);

			int money = 40 + rand() % 100; //QUANTIDADE DE DINHEIRO INICIAL DE CADA JOGADOR ALEATÓRIO DE 40 A 140

			User* user = new User(ID, NOME, CIDADE, IDADE, 0, 0, 0, money, money);

			//user->Show();
			users.push_back(user);
		}
		return 1;
	}
	return 0;
}

bool Casino::LoadMaquinas_Casino(const string& ficheiro) {
	xml_document doc;
	xml_parse_result result = doc.load_file("maquinas.xml");

	xml_node listaMaq = doc.child("DADOS").child("LISTA_MAQ");
	xml_node listaCas = doc.child("DADOS").child("DEFINICOES");

	int id = 500;
	string nome;
	int prob_ganhar;
	int custo;
	int premio;
	int state; //0 = OFF, 1 = ON, 2 = AVARIADA
	int x, y;
	float temperatura;

	nome = listaCas.child_value("NOME");
	max_jogadores = stoi(listaCas.child_value("MAX_JOG"));
	hora_inicio = stoi(listaCas.child_value("HORA_INICIO"));
	hora_fim = stoi(listaCas.child_value("HORA_FIM"));
	dinheiro_casino = 0;

	for (xml_node maquinaNode = listaMaq.child("MAQUINA"); maquinaNode; maquinaNode = maquinaNode.next_sibling("MAQUINA")) { //LOAD DAS MÁQUINAS
		nome = maquinaNode.child_value("NOME");
		prob_ganhar = maquinaNode.child("PROB_G").text().as_int();
		custo = maquinaNode.child("CUSTO").text().as_int();
		premio = maquinaNode.child("PREMIO").text().as_int();
		x = maquinaNode.child("X").text().as_int();
		y = maquinaNode.child("Y").text().as_int();
		temperatura = maquinaNode.child("TEMP_AVISO").text().as_float();

		prob_ganhar += 1;

		Maquina* mq = NULL;
		if (nome == "POKER") {
			mq = new Poker(id++, nome, prob_ganhar, custo, premio, x, y, temperatura, NULL);
		}
		if (nome == "ROLETA") {
			mq = new Roleta(id++, nome, prob_ganhar, custo, premio, x, y, temperatura, NULL);
		}
		if (nome == "SLOTS") {
			mq = new Slots(id++, nome, prob_ganhar, custo, premio, x, y, temperatura, NULL);
		}
		if (nome == "BLACKJACK") {
			mq = new Blackjack(id++, nome, prob_ganhar, custo, premio, x, y, temperatura, NULL);
		}
		AddMaquina(mq);
	}
	return 1;
}

bool Casino::AddUser(User* ut) {
	users.push_back(ut);
	return 0;
}

bool Casino::AddMaquina(Maquina* mq) {
	maquinas.push_back(mq);
	return 0;
}

bool Casino::DesligarMaquina(int id_mq) {
	list<Maquina*>::iterator it;
	for (auto const& it : maquinas) {
		if (it->Get_ID() == id_mq) {
			it->Set_Estado(0);
			return 1;
		}
	}
	return 0;
}

int Casino::Get_Estado(int id_mq) {
	string estado[] = { "Desligada", "Ligada", "Avariada" };
	list<Maquina*>::iterator it;
	for (auto const& it : maquinas) {
		if (it->Get_ID() == id_mq) {
			cout << "ID: " << it->Get_ID() << " Estado: " << estado[it->Get_Estado()] << " Tipo: " << it->Get_Tipo() << endl;
			return 1;
		}
	}
	return 0;
}


list<Maquina*> *Casino::Listar_Tipo(string tipo) {
	list<Maquina*>::iterator it;
	list<Maquina*>* l_final = new list<Maquina*>();
	list<Maquina*> a;
	for (auto const& it : maquinas) {
		if (it->Get_Tipo() == tipo) {
			l_final->push_back(it);
		}
	}
	return l_final;
}

void Casino::Listar_Todas() {
	string estado[] = { "Desligada", "Ligada", "Avariada" };
	list<Maquina*>::iterator it;
	for (auto const& it : maquinas) {
		cout << "\nMAQUINA ID: " << it->Get_ID() << endl;
		cout << "\tNOME:" << it->Get_Nome() << endl;
		cout << "\tESTADO:" << estado[it->Get_Estado()] << endl;
		cout << "\tPOSIÇÂO" << "X: " << it->Get_X() << " Y: " << it->Get_Y() << endl;
		cout << "\tTEMPERATURA: " << it->Get_Temp() << endl; 
	}
}

list<User*> Casino::getUsers() {
	return users;
}

list<Maquina*> Casino::getMaquinas() {
	return maquinas;
}

list<Maquina*> Casino::getMaquinasAvariadas() {
	return maquinas_avariadas;
}

int Casino::getDinheiroCasino() {
	return dinheiro_casino;
}

void Casino::setDinheiroCasino(int _num) {
	dinheiro_casino += _num;
}

//ESPAÇO DESTINO ÀS FUNÇÕES PARA RUN();//ESPAÇO DESTINO ÀS FUNÇÕES PARA RUN();//ESPAÇO DESTINO ÀS FUNÇÕES PARA RUN();//ESPAÇO DESTINO ÀS FUNÇÕES PARA RUN();

User* EscolherPessoaAleatória(list<User*> jogadores) {
	int random = rand() % 10000;
	int j = 0;
	for (const auto& i : jogadores) {
		j++;
		if (j == random) {
			return i;
		}
	}
}

list<User*> Shuffle(list<User*> u) { //DÁ SORT ALEATÓRIO À LISTA DE JOGADORES
	list<User*> final;
	vector<User*> v;
	for (const auto& i : u) {
		v.push_back(i);
	}
	random_shuffle(v.begin(), v.end());
	for (int i = 0; i < v.size(); i++) {
		final.push_back(v[i]);
	}
	
	return final;
}

void Casino::AdicionarPessoasMaquinas(list<User*> &jogadores, list<Maquina*> &maq) {
	for (const auto& i : jogadores) {									//PASSAR POR TODOS OS UTILIZADORES DO CASINO
		if (i->getMaquina() == NULL) {								//VERIFICAR SE O UTILIZADOR NÃO ESTÁ NUMA MÁQUINA
			for (const auto& j : maq) {								//PASSAR POR TODAS AS MÁQUINAS DO CASINO
				if (j->getUser() == NULL && j->Get_Estado() == 1) { //VERIFICAR SE A MÁQUINA NÃO TEM NINGUÉM
					j->setUser(i);									//COLOCAR O UTILIZADOR NA MÁQUINA
					i->setMaquina(j);
					i->frequentouMaquina();
					break;
				}
			}
		}
	}
}

void Casino::RunTheCasino(list<User*>& jogadores, list<Maquina*>& maq, list<Maquina*>& maq_avariadas, list<User*>& jogadoresFalidos){
	for (auto it = jogadores.begin(); it != jogadores.end(); ) {
		if ((*it)->getMaquina() != NULL) { //SE O JOGADOR TEM MÁQUINA
			if ((*it)->getMaquina()->Get_Temp() == (*it)->getMaquina()->Get_TempMax()) { //SE A TEMPERATURA DA MÁQUINA FOR MÁXIMA
				(*it)->getMaquina()->Set_Estado(0); //DESLIGA A MÁQUINA
				Maquina* m = (*it)->getMaquina();
				m->setUser(NULL); //TIRA O JOGADOR DA MÁQUINA
				(*it)->setMaquina(NULL); //TIRA A MÁQUINA DO UTILIZADOR
				maq_avariadas.push_back(m); //COLOCA A MÁQUINA NA LISTA DE AVARIADAS
				//it = jogadores.erase(it); //APAGA
				maq.remove(m);
			}
			else { //ENTÃO A MÁQUINA ESTÁ BOA
				if ((*it)->getMoney() >= (*it)->getMaquina()->getCusto()) { //SE O UTILIZADOR TEM DINHEIRO PARA JOGAR NA MÁQUINA
					(*it)->getMaquina()->Run(); //MÁQUINA DÁ RUN
					(*it)->getMaquina()->addJogosJogados(1);
					(*it)->removeMoney((*it)->getMaquina()->getCusto());
					setDinheiroCasino((*it)->getMaquina()->getCusto()); //CASINO GANHOU DINHEIRO
					if (rand() % 100 <= (*it)->getMaquina()->get_Prob()) { //CHANCE DO UTILIZADOR GANHAR
						(*it)->Ganhou(); //UTILIZADOR GANHOUR
						(*it)->addMoney((*it)->getMaquina()->getPremio()); //UTILIZADOR RECEBE DINHEIRO
						(*it)->getMaquina()->addDinheiroDistribuido((*it)->getMaquina()->getPremio()); //maquina regista premio distribuido
						setDinheiroCasino(-(*it)->getMaquina()->getPremio());
					}
					else { //SE NÃO GANHOU
						(*it)->getMaquina()->addDinheiroFeito((*it)->getMaquina()->getCusto()); //ESTATISTICA DA MÁQUINA SOBRE DINHEIRO GANHOU
					}
					(*it)->addJogosTotais(); //JOGOS TOTAIS DO UTILIZADOR +=1
					++it;
				}
				else { //SE O UTILIZADOR NÃO TEM DINHEIRO PARA JOGA 
					(*it)->getMaquina()->setUser(NULL); //TIRA O JOGADOR DA MÁQUINA
					(*it)->setMaquina(NULL); //TIRA A MÁQUINA DO UTILIZADOR
					jogadoresFalidos.push_back(*it); //COLOCA O JOGADOR NA LISTA DE JOGADORES FALIDOS
					//it = jogadores.erase(it); //TIRA O JOGADOR DA LISTA
					delete *it;
				}
			}
		}
		else {
			++it;
		}
	}
}

void Casino::FixMaquinasAvariadas(list<Maquina*>& maq, list<Maquina*>& maq_avariadas) {
	for (auto it = maq_avariadas.begin(); it != maq_avariadas.end();) {
		if ((*it)->Get_Temp() > 30) {
			(*it)->RunAvariada(); //DIMINIU A TEMPERATURA DA MÁQUINA EM 1 GRAU
			++it;
		}
		else {
			(*it)->Set_Estado(1);
			maq.push_back(*it);
			it = maq_avariadas.erase(it);
			it++;
		}
	}
}

int Casino::LibertarMemoria(list<User*>& jogadores, list<User*>& jogadoresFalidos) {
	for (auto& i : users) {
		delete i;
	}
	for (auto& i : maquinas) {
		delete i;
	}
	maquinas.clear();
	for (auto& i : maquinas_avariadas) {
		delete i;
	}
	maquinas_avariadas.clear();
	users.clear();
	jogadores.clear();
	jogadoresFalidos.clear();
	return 1;
}

void Casino::Relatorio(string ficheiro) {
	xml_document doc;
	if (!doc.load_file("relatorio.xml")) {
		cout << "Não há ficheiro";
	}
	doc.reset();
	doc.save_file("relatorio.xml");

	XMLWriter XX;
	XX.WriteStartDocument(ficheiro);
	XX.WriteStartElement("MAQUINAS");
	for (auto& i : maquinas) {
		XX.WriteStartElement("MAQUINA");
		XX.WriteElementString("ID", to_string(i->Get_ID()));
		XX.WriteElementString("TIPO", i->Get_Tipo());
		XX.WriteElementString("DINHEIRO_FEITO", to_string(i->getDinheiroFeito()));
		XX.WriteElementString("DINHEIRO_DISTRIBUIDO", to_string(i->getDinheiroDistribuido()));
		XX.WriteElementString("JOGOS_JOGADOS", to_string(i->getJogosJogados()));
		XX.WriteEndElement();
	}
	XX.WriteEndElement();
	XX.WriteEndDocument();
}

void Casino::RelatorioSemiHorario(int current_time, list<User*> &jogadores, string final) {
	if (current_time % 1800 == 0) { 
		for (const auto& i : jogadores) {
			//setDinheiroCasino(i->getStarterMoney() - i->getMoney());
		}
		cout << "ESTATÍSTICA DO CASINO : " << final << endl;
		cout << "\tMAQUINAS LIGADAS: " << maquinas.size() << endl;
		cout << "\tMAQUINAS DESLIGADAS : " << maquinas_avariadas.size() << endl;
		cout << "\tUTILIZADORES NO CASINO: " << jogadores.size() << endl;
		cout << "\tDINHEIRO FATURADO: " << getDinheiroCasino() << endl;
		cout << "\n";
	}
}

void Casino::RelatorioFinalJogadores(list<User*>& jogadores, list<User*>& jogadoresFalidos, list<User*> &vencedor, int &pessoasQueJogaram, int &pessoasQueGanharam) {
	
	for (const auto& i : jogadores) { //Faz print de todos os jogadores
		if (i->getJogosTotais() != 0) {
			pessoasQueJogaram++;
			cout << "USER: " << i->getNome() << " ID: " << i->getID() << endl;
			cout << "HORA DE ENTRADA: " << i->getHora() << endl;
			cout << "\tJOGOS TOTAIS: " << i->getJogosTotais() << endl;
			cout << "\tJOGOS GANHOS: " << i->getGanhos() << endl;
			cout << "\tMAQUINAS FREQUENTADAS: " << i->MaquinasFrequentadas() << endl;
			cout << "\tDINHEIRO INICIAL: " << i->getStarterMoney() << endl;
			cout << "\tDINHEIRO FINAL: " << i->getMoney() << endl;
			cout << "\n";
			if (i->getStarterMoney() < i->getMoney()) {
				vencedor.push_back(i);
				pessoasQueGanharam++;
			}
		}
	}

	cout << "\n\n\n -------------------JOGADORES FALIDOS-------------------------- \n\n\n";
	for (const auto& i : jogadoresFalidos) { //Faz print de todos os jogadores que faliram
		if (i->getJogosTotais() != 0) {
			pessoasQueJogaram++;
			cout << "USER: " << i->getNome() << " ID: " << i->getID() << endl;
			cout << "HORA DE ENTRADA: " << i->getHora() << endl;
			cout << "\tJOGOS TOTAIS: " << i->getJogosTotais() << endl;
			cout << "\tJOGOS GANHOS: " << i->getGanhos() << endl;
			cout << "\tMAQUINAS FREQUENTADAS: " << i->MaquinasFrequentadas() << endl;
			cout << "\tDINHEIRO INICIAL: " << i->getStarterMoney() << endl;
			cout << "\tDINHEIRO FINAL: " << i->getMoney() << endl;
			cout << "\n";
			if (i->getStarterMoney() < i->getMoney()) {
				vencedor.push_back(i);
				pessoasQueGanharam++;
			}
		}
	}
}

void Casino::RelatorioFinalCasino(list<User*> &jogadoresFalidos, int &pessoasQueJogaram, int &pessoasQueGanharam) {
	cout << "-------------------------------------------FINAL-------------------------------------------" << endl;
	cout << "\t\t\t\tJogaram " << pessoasQueJogaram << " pessoas" << endl;
	cout << "\t\t\t\tGanharam " << pessoasQueGanharam << " pessoas" << endl;
	cout << "\t\t\t\tO Casino faturou " << getDinheiroCasino() << " euros" << endl;
	cout << "\n";
	cout << "\t\t\t\tJogadores que faliram: " << jogadoresFalidos.size() << endl;
	cout << "-------------------------------------------FINAL-------------------------------------------" << endl;
}

void Casino::RelatorioVencedores(list<User*>& vencedor) {
	for (const auto& i : vencedor) { //Faz print no ecrã de todas as pessoas que ganharam dinheiro no casino
		cout << "USER: " << i->getNome() << " ID: " << i->getID() << endl;
		cout << "HORA DE ENTRADA: " << i->getHora() << endl;
		cout << "\tJOGOS TOTAIS: " << i->getJogosTotais() << endl;
		cout << "\tJOGOS GANHOS: " << i->getGanhos() << endl;
		cout << "\tMAQUINAS FREQUENTADAS: " << i->MaquinasFrequentadas() << endl;
		cout << "\tDINHEIRO INICIAL: " << i->getStarterMoney() << endl;
		cout << "\tDINHEIRO FINAL: " << i->getMoney() << endl;
		cout << "\n";
	}
}

//ESPAÇO DESTINO ÀS FUNÇÕES PARA RUN();//ESPAÇO DESTINO ÀS FUNÇÕES PARA RUN();//ESPAÇO DESTINO ÀS FUNÇÕES PARA RUN();//ESPAÇO DESTINO ÀS FUNÇÕES PARA RUN();

void Casino::Run() {
	int x = 0;
	int pessoasQueJogaram = 0;
	int pessoasQueGanharam = 0;

	list<User*> jogadores;
	list<User*> jogadoresFalidos;
	list<User*> vencedor;

	time_t hora_abertura = 18 * 3600;
	time_t hora_fim = 27 * 3600;
	time_t current_time = hora_abertura;
	string final;

	while (current_time < hora_fim) { //ENQUANTO O CASINO ESTIVER ABERTO
		if (jogadores.size() < 1000) { //ENQUANTO HOUVER ESPAÇO PARA NOVOS JOGADORES
			User* u = EscolherPessoaAleatória(users); //JOGADOR ALEATÓRIO
			int horas = floor(current_time / 3600);
			string hora = to_string(horas);
			string minutos = to_string((current_time / 60) - (horas * 60));
			if (minutos.length() == 1) {
				minutos = '0' + minutos;
			}
			if (horas >= 24) {
				horas -= 24;
				hora = to_string(horas);
			}
			if (hora.length() == 1) {
				hora = '0' + hora;
			}

			final = hora + ":" + minutos;
			u->setHora(final);
			jogadores.push_back(u); //ESCOLHER PESSOA ALEATÓRIA PARA O CASINO
		}

		jogadores = Shuffle(jogadores); //SHUFFLE DOS JOGADORES PARA GARANTIR A ALEATORIEDADE DOS JOGADORES A ENTRAR NAS MÁQUINAS

		AdicionarPessoasMaquinas(jogadores, maquinas); //COLOCA JOGADORES NAS MÁQUINAS
		RunTheCasino(jogadores, maquinas, maquinas_avariadas, jogadoresFalidos); //FAZ O RUN DO CASINO
		FixMaquinasAvariadas(maquinas, maquinas_avariadas); //CONSERTO DAS MÁQUINAS AVARIADAS


		RelatorioSemiHorario(current_time, jogadores, final);
		current_time += 60;
	}

	RelatorioSemiHorario(current_time, jogadores, final); //RELATÓRIO DE 30 EM 30 MINUTOS COM INFORMAÇÕES ATUALIZADAS DO CASINO
	RelatorioFinalJogadores(jogadores, jogadoresFalidos, vencedor, pessoasQueJogaram, pessoasQueGanharam); //RELATORIO COM TODOS OS JOGADORES QUE JOGARAM NO CASINO

	cout << "\n\n\n";

	RelatorioFinalCasino(jogadoresFalidos, pessoasQueJogaram, pessoasQueGanharam); //RELATORIO COM ESTATISTICAS DO CASINO

	RelatorioVencedores(vencedor); //RELATORIO COM OS JOGADORES QUE GANHARAM DINHEIRO NO CAISNO

	Relatorio("relatorio.xml"); //Escreve o relatório de todas as máquinas
	LibertarMemoria(jogadores, jogadoresFalidos); //Liberta a memória
	
}
