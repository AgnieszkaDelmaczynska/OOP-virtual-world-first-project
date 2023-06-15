#include <iostream>
#include <Windows.h>
#include "Zwierze.h"
#include "TworzenieOrganizmow.h"
#define LICZBA_PROB 16
using namespace std;

bool Zwierze::czy_zwierze()					{ return true; }
int Zwierze::getPoprzedniX()				{ return this->poprzednie_koordynaty.poprzedni_x; }
int Zwierze::getPoprzedniY()				{ return this->poprzednie_koordynaty.poprzedni_y; }
int Zwierze::setPoprzedniX(int a)			{ return this->poprzednie_koordynaty.poprzedni_x = a; }
int Zwierze::setPoprzedniY(int a)			{ return this->poprzednie_koordynaty.poprzedni_y = a; }

Zwierze::Zwierze(Swiat* swiat, TypOrganizmu typOrganizmu, int sila, int inicjatywa, int x, int y, int turaurodzenia)
	:Organizm(swiat, typOrganizmu, sila, inicjatywa, x, y, turaurodzenia)
{
	this->poprzednie_koordynaty.poprzedni_x = x;
	this->poprzednie_koordynaty.poprzedni_y = y;
}

void Zwierze::akcja(std::list<Organizm*>& lista_organizmów)
{	
	while (true)
	{
		int losowany_ruch = rand() % 4;

		if ((losowany_ruch == (int)Kierunek::GORA) && this->getY() != 0)
		{
			this->poprzednie_koordynaty.poprzedni_y = this->koordynaty.pozycja_y;
			this->koordynaty.pozycja_y--; break;		
		}
		else if ((losowany_ruch == (int)Kierunek::DOL) && this->getY() != WORLD_HEIGHT-1)
		{
			this->poprzednie_koordynaty.poprzedni_y = this->koordynaty.pozycja_y;
			this->koordynaty.pozycja_y++; break;
		}
		else if ((losowany_ruch == (int)Kierunek::LEWO) && this->getX() !=0)
		{
			this->poprzednie_koordynaty.poprzedni_x = this->koordynaty.pozycja_x;
			this->koordynaty.pozycja_x--; break;
		}
		else if ((losowany_ruch == (int)Kierunek::PRAWO) && this->getX() != WORLD_WIDTH-1)
		{
			this->poprzednie_koordynaty.poprzedni_x = this->koordynaty.pozycja_x;
			this->koordynaty.pozycja_x++; break;
		}
	}
}
//										  W	 na	 A
//						    	this	A			W
// organizmu skutek_kolizji = organizm_inny->kolizja(organizm);
int Zwierze::kolizja(Organizm* organizm, std::list<Organizm*> lista_organizmów) // wersja nowa, kolizja innego organizmu
{
	cout << "kolizja: "; organizm->OrganizmToSring(); cout << ", "; this->OrganizmToSring(); cout << endl;
	if (this->TypOrganizmuToString() == organizm->TypOrganizmuToString())
	{
		organizm->setX(organizm->getPoprzedniX());
		organizm->setY(organizm->getPoprzedniY());
		Rozmnazanie(lista_organizmów, this);
		//Sleep(1000);
		return (int)Skutek_kolizji::ROZMNAZANIE;
	}
	else
	{
		if (this->sila <= organizm->getSila())
		{
			cout << "Umiera inny organizm: " << this->TypOrganizmuToString() << endl;
			//Sleep(1000);
			return (int)Skutek_kolizji::SMIERC_INNEGO;
		}
		else if (this->sila > organizm->getSila())
		{
			cout << "Umiera organizm wykonujacy akcje: " << organizm->TypOrganizmuToString() << endl;
			//Sleep(1000);
			return (int)Skutek_kolizji::SMIERC_WYKONUJACEGO_AKCJE;
		}
		else return 0;
	}
}

void Zwierze::Rozmnazanie(std::list<Organizm*> lista_organizmów, Organizm* organizm)
{
	// losuj niezajęte pole
	int liczba_prob = 0;
	int x = -1, y = -1;
	while (true)
	{
		liczba_prob++;
		if (liczba_prob > LICZBA_PROB)
			break;
		int losowany_ruch = rand() % 4;
		if ((losowany_ruch == (int)Kierunek::GORA) && organizm->getY() != 0 && (czy_moze_wykonac_ruch(organizm->getX(), organizm->getY() - 1, lista_organizmów) == true))
		{
			x = organizm->getX();
			y = organizm->getY() - 1;
			break;
		}
		if ((losowany_ruch == (int)Kierunek::DOL) && organizm->getY() != WORLD_HEIGHT - 1 && (czy_moze_wykonac_ruch(organizm->getX(), organizm->getY() + 1, lista_organizmów) == true))
		{
			x = organizm->getX();
			y = organizm->getY() + 1;
			break;
		}
		if ((losowany_ruch == (int)Kierunek::LEWO) && organizm->getX() != 0 && (czy_moze_wykonac_ruch(organizm->getX() - 1, organizm->getY(), lista_organizmów) == true))
		{
			x = organizm->getX() - 1;
			y = organizm->getY();
			break;
		}
		if ((losowany_ruch == (int)Kierunek::PRAWO) && organizm->getX() != WORLD_WIDTH - 1 && (czy_moze_wykonac_ruch(organizm->getX() + 1, organizm->getY(), lista_organizmów) == true))
		{
			x = organizm->getX() + 1;
			y = organizm->getY();
			break;
		}
	}
	if ((x == organizm->getX()) && (y == organizm->getY()))
	{
		czy_moze_sie_rozmnazac = false;
		cout << "DRUGI ORGANIZM SPROBUJE SIE ROZMNOZYC\n";
		return;
	}
	if (x != -1 && y != -1)
	{
		cout << "Rozmnazanie zwierzecia " << TypOrganizmuToString() << " x[" << organizm->getX() << "] y[" << organizm->getY() << "]\n";
		Organizm* tmpOrganizm = TworzenieOrganizmow::stworz_nowy_organizm(this->swiat, typOrganizmu, x, y);
		cout << "Nowe zwierze " << TypOrganizmuToString() << " x[" << tmpOrganizm->getX() << "] y[" << tmpOrganizm->getY() << "]\n";
		swiat->pchnij_organizm_na_liste(tmpOrganizm);
	}
}

bool Zwierze::czy_moze_wykonac_ruch(int pos_x, int pos_y, std::list <Organizm*> lista_organizmów)
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