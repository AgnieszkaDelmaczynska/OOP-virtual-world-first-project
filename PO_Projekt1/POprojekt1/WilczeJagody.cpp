#include "WilczeJagody.h";
#include "Kolory.h"
#define WILCZE_JAGODY_SILA 99
#define WILCZE_JAGODY_INICJATYWA 0
using namespace std;

WilczeJagody::WilczeJagody(Swiat* swiat, int x, int y, int turaUrodzenia)
	:Roslina(swiat, TypOrganizmu::WILCZE_JAGODY, WILCZE_JAGODY_SILA, WILCZE_JAGODY_INICJATYWA, x, y, turaUrodzenia)
{}

string WilczeJagody::TypOrganizmuToString()
{
	return "WilczeJagody";
}

void WilczeJagody::rysowanie()
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, LIGHTMAGENTA);
	cout << "w";
	SetConsoleTextAttribute(hOut, WHITE);
}

//	Zwierze, ktore zjadlo te rośline, ginie
int WilczeJagody::kolizja(Organizm* organizm, std::list<Organizm*> lista_organizmów)
{
	if (this->TypOrganizmuToString() == organizm->TypOrganizmuToString())	// jagody na jagody
	{
		organizm->setX(organizm->getPoprzedniX());
		organizm->setY(organizm->getPoprzedniY());
		cout << "Rozmnazanie\n";
		//Sleep(1000);
		return (int)Skutek_kolizji::ROZMNAZANIE;
	}
	else	// zwierze na jagody
	{
		cout << organizm->TypOrganizmuToString() << " zjada wilcze jagody\n";
		cout << "Umiera organizm wykonujacy akcje: " << organizm->TypOrganizmuToString() << endl;
		//Sleep(1000);
		return (int)Skutek_kolizji::SMIERC_WYKONUJACEGO_AKCJE;
	}
}