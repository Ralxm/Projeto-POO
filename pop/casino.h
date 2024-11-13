#include <list>
#include <string>
#include "user.h"
#include "maquina.h"
using namespace std;

class Casino {
	string nome;
	int max_jogadores;
	int hora_inicio = 18;
	int hora_fim = 27;
	int dinheiro_casino = 0;
	list<User*> users;
	list<Maquina*> maquinas;
	list<Maquina*> maquinas_avariadas;

	void AdicionarPessoasMaquinas(list<User*>& users, list<Maquina*>& maq);
	void RunTheCasino(list<User*>& users, list<Maquina*>& maq, list<Maquina*>& maq_avariadas, list<User*>& jogadoresFalidos);
	void FixMaquinasAvariadas(list<Maquina*>& maq, list<Maquina*>& maq_avariadas);
	int getDinheiroCasino();
	void setDinheiroCasino(int _num);
	void Relatorio(string ficheiro);
	int LibertarMemoria(list<User*>& jogadoress, list<User*>& jogadoresFalidos);
public:
	Casino();
	~Casino();
	bool LoadUsers(const string& ficheiro);
	bool LoadMaquinas_Casino(const string& ficheiro);
	bool AddUser(User* ut);
	bool AddMaquina(Maquina* mq);
	bool DesligarMaquina(int id_mq);
	int Get_Estado(int id_mq);
	list<Maquina*> *Listar_Tipo(string tipo);
	void Listar_Todas();
	list<User*> getUsers();
	list<Maquina*> getMaquinas();
	list<Maquina*> getMaquinasAvariadas();

	void RelatorioSemiHorario(int time, list<User*> &jogadores, string final);
	void RelatorioFinalJogadores(list<User*>& jogadores, list<User*>& jogadoresFalidos, list<User*>& vencedor, int& pessoasQueJogaram, int& pessoasQueGanharam);
	void RelatorioFinalCasino(list<User*>& jogadoresFalidos, int& pessoasQueJogaram, int& pessoasQueGanharam);
	void RelatorioVencedores(list<User*> &vencedor);

	void Run();
};