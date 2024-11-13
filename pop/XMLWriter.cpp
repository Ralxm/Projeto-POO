#include "XMLWriter.h"

XMLWriter::XMLWriter()
{
    //cout << "Passei em <" << __FUNCTION__ << ">" << endl;
}

XMLWriter::~XMLWriter()
{
    //cout << "Passei em <" << __FUNCTION__ << ">" << endl;
}

string XMLWriter::Tabulacoes(int N)
{
    string s = "";
    for (int i = 0; i < N; i++)
        s += "\t";
    return s;
}
void XMLWriter::WriteStartDocument(string ficheiro)
{
    //cout << "Passei em <" << __FUNCTION__ << ">" << endl;
    NOME_FICHEIRO = ficheiro;
}
void XMLWriter::WriteEndDocument()
{
    //cout << "Passei em <" << __FUNCTION__ << ">" << endl;
}
void XMLWriter::WriteElementString(string el, string valor)
{
    //cout << "Passei em <" << __FUNCTION__ << ">" << endl;
    ofstream F(NOME_FICHEIRO, ios::app);
    F << Tabulacoes(TAGS.size()) << "\t<" << el <<">" << valor << "</" << el << ">" << endl;
    F.close();
}
void XMLWriter::WriteStartElement(string el)
{
    //cout << "Passei em <" << __FUNCTION__ << ">" << endl;
    TAGS.push_front(el);
    ofstream F(NOME_FICHEIRO, ios::app);
    F << Tabulacoes(TAGS.size()) << "<" << el <<">" << endl;
    F.close();
}
void XMLWriter::WriteEndElement()
{
    //cout << "Passei em <" << __FUNCTION__ << ">" << endl;
    //cout << "TAM = " << TAGS.size() << endl;
    string el = TAGS.front();
    TAGS.pop_front();
    //cout << "TAM = " << TAGS.size() << endl;
    ofstream F(NOME_FICHEIRO, ios::app);
    F << Tabulacoes(TAGS.size()) << "\t</" << el <<">" << endl;
    F.close();
}
