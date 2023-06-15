#include "Guarana.h";
#include "Kolory.h"
#define GUARANA_SILA 0
#define GUARANA_INICJATYWA 0
using namespace std;

Guarana::Guarana(Swiat* swiat, int x, int y, int turaUrodzenia)
	:Roslina(swiat, TypOrganizmu::GUARANA, GUARANA_SILA, GUARANA_INICJATYWA, x, y, turaUrodzenia)
{}

string Guarana::TypOrganizmuToString()
{
	return "Guarana";
}

void Guarana::rysowanie()
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, MAGENTA);
	cout << "g";
	SetConsoleTextAttribute(hOut, WHITE);
}

int Guarana::kolizja(Organizm* organizm, std::list<Organizm*> lista_organizmów)
{
	if (this->TypOrganizmuToString() == organizm->TypOrganizmuToString())
	{
		organizm->setX(organizm->getPoprzedniX());
		organizm->setY(organizm->getPoprzedniY());
		cout << "Rozmnazanie\n";
		Sleep(1000);
		return (int)Skutek_kolizji::ROZMNAZANIE;
	}
	else
	{
		if (this->sila <= organizm->getSila())
		{
			organizm->setSila(organizm->getSila() + 3);
			cout << organizm->TypOrganizmuToString() << " x[" << organizm->getX() << "] y[" << organizm->getY() << "] sila[" << organizm->getSila() - 3<<"] zwieksza sile o 3, teraz jego sila wynosi:       "<< organizm->getSila() << endl;
			cout << "Umiera roslina: " << this->TypOrganizmuToString() << endl;
			Sleep(1000);
			return (int)Skutek_kolizji::SMIERC_INNEGO;
		}
		else if (this->sila > organizm->getSila())
		{
			cout << "Umiera organizm wykonujacy akcje: " << organizm->TypOrganizmuToString() << endl;
			Sleep(1000);
			return (int)Skutek_kolizji::SMIERC_WYKONUJACEGO_AKCJE;
		}
		else return 0;
	}
}