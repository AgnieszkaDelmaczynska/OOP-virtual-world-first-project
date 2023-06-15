#include "Mlecz.h";
#include "Kolory.h"
#include "TworzenieOrganizmow.h"
#define MLECZ_SILA 0
#define MLECZ_INICJATYWA 0
#define LICZBA_PROB_ROZMNAZANIA 3
using namespace std;

Mlecz::Mlecz(Swiat* swiat, int x, int y, int turaUrodzenia)
	:Roslina(swiat, TypOrganizmu::MLECZ, MLECZ_SILA, MLECZ_INICJATYWA, x, y, turaUrodzenia)
{}

string Mlecz::TypOrganizmuToString()
{
	return "Mlecz";
}

void Mlecz::rysowanie()
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, YELLOW);
	cout << "m";
	SetConsoleTextAttribute(hOut, WHITE);
}

void Mlecz::akcja(std::list<Organizm*> &lista_organizmów)
{
	cout << "Akcja rosliny: " << TypOrganizmuToString() << " x[" << this->getX() << "] y[" << this->getY() << "] sila[" << this->sila << "] inicjatywa[" << this->inicjatywa << "]\n";
	for (int i = 0; i < LICZBA_PROB_ROZMNAZANIA; i++)
	{
		if (rand() % 2 < 1)
		{
			Rozprzestrzenianie(lista_organizmów); // szansa 50 % to 1
			//Sleep(1000);
		}
	}
}