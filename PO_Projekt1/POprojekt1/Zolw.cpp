#include "Zolw.h"
#include "Kolory.h"
#define ZOLW_SILA 2
#define ZOLW_INICJATYWA 1
using namespace std;

Zolw::Zolw(Swiat* swiat, int x, int y, int turaUrodzenia)
	:Zwierze(swiat, TypOrganizmu::ZOLW, ZOLW_SILA, ZOLW_INICJATYWA, x, y, turaUrodzenia)
{}

string Zolw::TypOrganizmuToString()
{
	return "Zolw";
}

void Zolw::rysowanie()
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, LIGHTGREEN);
	cout << "Z";
	SetConsoleTextAttribute(hOut, WHITE);
}

void Zolw::akcja(std::list<Organizm*>& lista_organizmów)
{
	int szansa_na_ruch_zolwia = rand() % 4;
	if (szansa_na_ruch_zolwia == 1)			// dowolna liczba z zakersu 0-3, ja przyjmuję sobie 1, wtedy szansa na wykonanie ruchu wynosi 25%
	{
		while (true)
		{
			int losowany_ruch = rand() % 4;
			if ((losowany_ruch == (int)Kierunek::GORA) && this->getY() != 0)
			{
				this->setPoprzedniY(this->getY());
				this->setY(this->getY() - 1);	break;
			}
			else if ((losowany_ruch == (int)Kierunek::DOL) && this->getY() != WORLD_HEIGHT - 1)
			{
				this->setPoprzedniY(this->getY());
				this->setY(this->getY() + 1);	break;
			}
			else if ((losowany_ruch == (int)Kierunek::LEWO) && this->getX() != 0)
			{
				this->setPoprzedniX(this->getX());
				this->setX(this->getX() - 1);	break;
			}
			else if ((losowany_ruch == (int)Kierunek::PRAWO) && this->getX() != WORLD_WIDTH - 1)
			{
				this->setPoprzedniX(this->getX());
				this->setX(this->getX() + 1);	break;
			}
		}
	}
}
																			//									kolizja W na Z
																			// wersja nowa, kolizja innego		Z				W
int Zolw::kolizja(Organizm* organizm, std::list<Organizm*> lista_organizmów)// organizmu skutek_kolizji = organizm_inny->kolizja(organizm);
{
	cout << "kolizja: "; organizm->OrganizmToSring(); cout << ", "; this->OrganizmToSring(); cout << endl;
	if (this->TypOrganizmuToString() == organizm->TypOrganizmuToString())
	{
		organizm->setX(organizm->getPoprzedniX());
		organizm->setY(organizm->getPoprzedniY());
		cout << "Rozmnazanie\n";
		//Sleep(1000);
		return (int)Skutek_kolizji::ROZMNAZANIE;
	}
	else
	{
		if (this->sila < organizm->getSila())
		{
			if (organizm->getSila() < 5)
			{
				organizm->setX(organizm->getPoprzedniX());
				organizm->setY(organizm->getPoprzedniY());
				cout << "Zolw odgonil atakujacego\n";
				//Sleep(1000);
				return (int)Skutek_kolizji::ODGONIENIE;
			}
			else
			{
				cout << "Umiera zolw\n";
				//Sleep(1000);
				return (int)Skutek_kolizji::SMIERC_INNEGO;
			}
		}
		else if (this->sila >= organizm->getSila())
		{
			cout << "Umiera organizm atakujacy zolwia: " << organizm->TypOrganizmuToString() << endl;
			//Sleep(1000);
			return (int)Skutek_kolizji::SMIERC_WYKONUJACEGO_AKCJE;
		}
	}
}