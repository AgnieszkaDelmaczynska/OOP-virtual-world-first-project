#include "Wilk.h"
#include "Kolory.h"
#define WILK_SILA 9
#define WILK_INICJATYWA 5
using namespace std;

Wilk::Wilk(Swiat* swiat, int x, int y, int turaUrodzenia)
	:Zwierze(swiat, TypOrganizmu::WILK, WILK_SILA, WILK_INICJATYWA, x, y, turaUrodzenia)
{}

string Wilk::TypOrganizmuToString()
{
	return "Wilk";
}

void Wilk::rysowanie()
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, DARKGRAY);
	cout << "W";
	SetConsoleTextAttribute(hOut, WHITE);
}