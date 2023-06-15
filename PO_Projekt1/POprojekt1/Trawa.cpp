#include "Trawa.h";
#include "Kolory.h"
#define TRAWA_SILA 0
#define TRAWA_INICJATYWA 0
using namespace std;

Trawa::Trawa(Swiat* swiat, int x, int y, int turaUrodzenia)
	:Roslina(swiat, TypOrganizmu::TRAWA, TRAWA_SILA, TRAWA_INICJATYWA, x, y, turaUrodzenia)
{}

string Trawa::TypOrganizmuToString()
{
	return "Trawa";
}

void Trawa::rysowanie()
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, LIGHTCYAN);
	cout << "t";
	SetConsoleTextAttribute(hOut, WHITE);
}