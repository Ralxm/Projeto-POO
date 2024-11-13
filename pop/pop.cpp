#include "casino.h"
#include <time.h>

using namespace std;

int main()
{
	srand(time(NULL));
	Casino c;
	c.LoadUsers("pessoas.txt");
	c.LoadMaquinas_Casino("maquinas.xml");

	c.Run();
}