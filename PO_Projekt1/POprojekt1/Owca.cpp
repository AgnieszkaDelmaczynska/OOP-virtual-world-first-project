#include "Owca.h";
#include "Kolory.h"
#define OWCA_SILA 4
#define OWCA_INICJATYWA 4
using namespace std;

Owca::Owca(Swiat* swiat, int x, int y, int turaurodzenia)
	:Zwierze(swiat, TypOrganizmu::OWCA, OWCA_SILA, OWCA_INICJATYWA, x, y, turaUrodzenia)
{}
string Owca::TypOrganizmuToString()
{
	return "Owca";
}
void Owca::rysowanie()
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, BROWN);
	cout << "O";
	SetConsoleTextAttribute(hOut, WHITE);
}