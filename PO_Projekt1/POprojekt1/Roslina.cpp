#include <iostream>
#include <Windows.h>
#include "Roslina.h"
#include "TworzenieOrganizmow.h"
#define LICZBA_PROB 16
using namespace std;

bool Roslina::czy_zwierze()					{ return false; }
int Roslina::getPoprzedniX()				{ return 0; }
int Roslina::getPoprzedniY()				{ return 0; }

Roslina::Roslina(Swiat* swiat, TypOrganizmu typOrganizmu, int sila, int inicjatywa, int x, int y, int turaUrodzenia)
	:Organizm(swiat, typOrganizmu, sila, inicjatywa, x, y, turaUrodzenia)
{}

void Roslina::akcja(std::list<Organizm*>& lista_organizmów)
{
	if (rand() % 100 < 50)
	{
		cout << "Akcja rosliny: " << TypOrganizmuToString() << " x[" << this->getX() << "] y[" << this->getY() << "] sila[" << this->sila << "] inicjatywa[" << this->inicjatywa << "]\n";
		Rozprzestrzenianie(lista_organizmów);
		//Sleep(1000);
	}
}
//										  W	 na	 A
//						    	this	A			W
// organizmu skutek_kolizji = organizm_inny->kolizja(organizm);
int Roslina::kolizja(Organizm* organizm, std::list<Organizm*> lista_organizmów) // wersja nowa, kolizja innego organizmu
{
	if (this->sila <= organizm->getSila())
	{
		cout << "Umiera roslina: " << this->TypOrganizmuToString() << endl;
		//Sleep(1000);
		return (int)Skutek_kolizji::SMIERC_INNEGO;
	}
	else if (this->sila > organizm->getSila())
	{
		cout << "Umiera organizm wykonujacy akcje: " << organizm->TypOrganizmuToString() << endl;
		//Sleep(1000);
		return (int)Skutek_kolizji::SMIERC_WYKONUJACEGO_AKCJE;
	}
}

void Roslina::Rozprzestrzenianie(std::list<Organizm*> lista_organizmów)
{
	cout << "Rozprzestrzenianie rosliny " << TypOrganizmuToString() << " x[" << this->getX() << "] y[" << this->getY() << "] sila[" << this->sila << "] inicjatywa[" << this->inicjatywa << "]\n";
	// losuj niezajęte pole
	int liczba_prob = 0;
	int x = -1, y = -1;
	while (true)
	{
		liczba_prob++;
		if (liczba_prob > LICZBA_PROB)
			break;
		int losowany_ruch = rand() % 4;
		if ((losowany_ruch == (int)Kierunek::GORA) && this->getY() != 0 && (czy_moze_wykonac_ruch(this->getX(), this->getY() - 1, lista_organizmów) == true))
		{
			x = this->getX();
			y = this->getY() - 1;
			break;
		}
		if ((losowany_ruch == (int)Kierunek::DOL) && this->getY() != WORLD_HEIGHT - 1 && (czy_moze_wykonac_ruch(this->getX(), this->getY() + 1, lista_organizmów) == true))
		{
			x = this->getX();
			y = this->getY() + 1;
			break;
		}
		if ((losowany_ruch == (int)Kierunek::LEWO) && this->getX() != 0 && (czy_moze_wykonac_ruch(this->getX() - 1, this->getY(), lista_organizmów) == true))
		{
			x = this->getX() - 1;
			y = this->getY();
			break;
		}
		if ((losowany_ruch == (int)Kierunek::PRAWO) && this->getX() != WORLD_WIDTH - 1 && (czy_moze_wykonac_ruch(this->getX() + 1, this->getY(), lista_organizmów) == true))
		{
			x = this->getX() + 1;
			y = this->getY();
			break;
		}
	}
	//if ((x == this->getX()) && (y == this->getY())) return;
	if (x != -1 && y != -1)
	{
		Organizm* tmpOrganizm = TworzenieOrganizmow::stworz_nowy_organizm(this->swiat, typOrganizmu, x, y);
		cout << "Nowa roslina " << TypOrganizmuToString() << " x[" << tmpOrganizm->getX() << "] y[" << tmpOrganizm->getY() << "]\n";
		swiat->pchnij_organizm_na_liste(tmpOrganizm);
	}
	else return;
}

bool Roslina::czy_moze_wykonac_ruch(int pos_x, int pos_y, std::list <Organizm*> lista_organizmów)
{
	bool czy_moze = true;
	for (Organizm* organizm : lista_organizmów)
	{
		if ((organizm->getX() == pos_x) && (organizm->getY() == pos_y))
		{
			czy_moze = false;
			break;
		}
	}
	return czy_moze;
}