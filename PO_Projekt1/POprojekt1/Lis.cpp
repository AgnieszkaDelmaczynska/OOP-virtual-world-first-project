#include "Lis.h";
#include "Kolory.h"
#define LIS_SILA 3
#define LIS_INICJATYWA 7
using namespace std;

Lis::Lis(Swiat* swiat, int x, int y, int turaUrodzenia)
	:Zwierze(swiat, TypOrganizmu::LIS, LIS_SILA, LIS_INICJATYWA, x, y, turaUrodzenia)
{}

string Lis::TypOrganizmuToString()
{
	return "Lis";
}

void Lis::rysowanie()
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, LIGHTRED);
	cout << "L";
	SetConsoleTextAttribute(hOut, WHITE);
}

void Lis::akcja(std::list<Organizm*>& lista_organizmów)
{
	while (true)
	{
		int losowany_ruch = rand() % 4;
		if ((losowany_ruch == (int)Kierunek::GORA) && (this->getY() != 0) && (czy_moze_wykonac_ruch(this->getX(), this->getY() - 1, lista_organizmów) == true))
		{
			this->poprzednie_koordynaty.poprzedni_y = this->koordynaty.pozycja_y;
			this->koordynaty.pozycja_y--; break;		
		}
		else if ((losowany_ruch == (int)Kierunek::DOL) && (this->getY() != WORLD_HEIGHT-1) && (czy_moze_wykonac_ruch(this->getX(), this->getY() + 1, lista_organizmów) == true))
		{
			this->poprzednie_koordynaty.poprzedni_y = this->koordynaty.pozycja_y;
			this->koordynaty.pozycja_y++; break;
		}
		else if ((losowany_ruch == (int)Kierunek::LEWO) && (this->getX() !=0) && (czy_moze_wykonac_ruch(this->getX() - 1, this->getY(), lista_organizmów) == true))
		{
			this->poprzednie_koordynaty.poprzedni_x = this->koordynaty.pozycja_x;
			this->koordynaty.pozycja_x--; break;
		}
		else if ((losowany_ruch == (int)Kierunek::PRAWO) && (this->getX() != WORLD_WIDTH-1) && (czy_moze_wykonac_ruch(this->getX() + 1, this->getY(), lista_organizmów) == true))
		{
			this->poprzednie_koordynaty.poprzedni_x = this->koordynaty.pozycja_x;
			this->koordynaty.pozycja_x++; break;
		}
	}
}

bool Lis::czy_moze_wykonac_ruch(int pos_x, int pos_y, std::list <Organizm*> lista_organizmów)
{
	bool czy_moze = true;
	for (Organizm* organizm : lista_organizmów)
	{
		if ((organizm->getX() == pos_x) && (organizm->getY() == pos_y) && (organizm->getSila() > LIS_SILA))
			czy_moze = false;
	}
	return czy_moze;
}