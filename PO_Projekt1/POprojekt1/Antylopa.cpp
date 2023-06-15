#include "Antylopa.h"
#include "Kolory.h"
#define ANTYLOPA_SILA 4
#define ANTYLOPA_INICJATYWA 4
using namespace std;

Antylopa::Antylopa(Swiat* swiat, int x, int y, int turaUrodzenia)
	:Zwierze(swiat, TypOrganizmu::ANTYLOPA, ANTYLOPA_SILA, ANTYLOPA_INICJATYWA, x, y, turaUrodzenia)
{}

string Antylopa::TypOrganizmuToString()
{
	return "Antylopa";
}

void Antylopa::rysowanie()
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, LIGHTBLUE);
	cout << "A";
	SetConsoleTextAttribute(hOut, WHITE);
}

void Antylopa::akcja(std::list<Organizm*>& lista_organizmów)
{
	while (true)
	{
		int losowany_ruch = rand() % 4;
		if ((losowany_ruch == (int)Kierunek::GORA) && (this->getY() != 1) && (this->getY() != 0))
		{
			cout << TypOrganizmuToString() << " x[" << this->getX() << "] y[" << this->getY() << "]"; //Sleep(1000);
			cout << " ROBI RUCH GORA 2\n";
			this->setPoprzedniY(this->getY());
			this->setY(this->getY() - 2); //Sleep(1000);
			break;
		}
		else if ((losowany_ruch == (int)Kierunek::GORA) && (this->getY() != 0))
		{
			cout << TypOrganizmuToString() << " x[" << this->getX() << "] y[" << this->getY() << "]"; //Sleep(1000);
			cout << " ROBI RUCH GORA 1\n";
			this->setPoprzedniY(this->getY());
			this->setY(this->getY() - 1); //Sleep(1000);
			break;
		}
		else if ((losowany_ruch == (int)Kierunek::DOL) && (this->getY() != WORLD_HEIGHT - 1) && (this->getY() != WORLD_HEIGHT - 2))
		{
			cout << TypOrganizmuToString() << " x[" << this->getX() << "] y[" << this->getY() << "]"; //Sleep(1000);
			cout << " ROBI RUCH DOL 2\n";
			this->setPoprzedniY(this->getY());
			this->setY(this->getY() + 2); //Sleep(1000);
			break;
		}
		else if ((losowany_ruch == (int)Kierunek::DOL) && (this->getY() != WORLD_HEIGHT - 1))
		{
			cout << TypOrganizmuToString() << " x[" << this->getX() << "] y[" << this->getY() << "]"; //Sleep(1000);
			cout << " ROBI RUCH DOL 1\n";
			this->setPoprzedniY(this->getY());
			this->setY(this->getY() + 1); //Sleep(1000);
			break;
		}
		else if ((losowany_ruch == (int)Kierunek::LEWO) && (this->getX() != 0) && (this->getX() != 1))
		{
			cout << TypOrganizmuToString() << " x[" << this->getX() << "] y[" << this->getY() << "]"; //Sleep(1000);
			cout << " ROBI RUCH LEWO 2\n";
			this->setPoprzedniX(this->getX());
			this->setX(this->getX() - 2); //Sleep(1000);
			break;
		}
		else if ((losowany_ruch == (int)Kierunek::LEWO) && (this->getX() != 0))
		{
			cout << TypOrganizmuToString() << " x[" << this->getX() << "] y[" << this->getY() << "]"; //Sleep(1000);
			cout << " ROBI RUCH LEWO 1\n";
			this->setPoprzedniX(this->getX());
			this->setX(this->getX() - 1); //Sleep(1000);
			break;
		}
		else if ((losowany_ruch == (int)Kierunek::PRAWO) && (this->getX() != WORLD_WIDTH - 1) && (this->getX() != WORLD_WIDTH - 2))
		{
			cout << TypOrganizmuToString() << " x[" << this->getX() << "] y[" << this->getY() << "]"; //Sleep(1000);
			cout << " ROBI RUCH PRAWO 2\n";
			this->setPoprzedniX(this->getX());
			this->setX(this->getX() + 2); //Sleep(1000);
			break;
		}
		else if ((losowany_ruch == (int)Kierunek::PRAWO) && (this->getX() != WORLD_WIDTH - 1))
		{
			cout << TypOrganizmuToString() << " x[" << this->getX() << "] y[" << this->getY() << "]"; //Sleep(1000);
			cout << " ROBI RUCH PRAWO 1\n";
			this->setPoprzedniX(this->getX());
			this->setX(this->getX() + 1); //Sleep(1000);
			break;
		}
	}
}
//										  W	 na	 A
//						    	this	A			W
// organizmu skutek_kolizji = organizm_inny->kolizja(organizm);
int Antylopa::kolizja(Organizm* ogranizm, std::list<Organizm*> lista_organizmów)
{
	int szansa_na_ucieczke = rand() % 2;  // szansa na ucieczkę 50%
	if (szansa_na_ucieczke == 1)		  // może uciec, szuka miejsca
	{
		cout << "SZANSA NA UCIECZKE ANTYLOPY\n";
		if ((this->getY() != 0) && (czy_moze_wykonac_ruch(this->getX(), this->getY() - 1, lista_organizmów) == true)) //w górę
		{
			cout << TypOrganizmuToString() << " x[" << this->getX() << "] y[" << this->getY() << "]";
			cout << " Antylopa uniknela kolizji, idzie w gore\n"; //Sleep(1000);
			this->poprzednie_koordynaty.poprzedni_y = this->koordynaty.pozycja_y;
			this->koordynaty.pozycja_y--; //Sleep(1000);
			return (int)Skutek_kolizji::UCIECZKA;
		}
		else if ((this->getY() != WORLD_HEIGHT - 1) && (czy_moze_wykonac_ruch(this->getX(), this->getY() + 1, lista_organizmów) == true)) // w dół
		{
			cout << TypOrganizmuToString() << " x[" << this->getX() << "] y[" << this->getY() << "]";
			cout << " Antylopa uniknela kolizji, idzie w dol\n"; //Sleep(1000);
			this->poprzednie_koordynaty.poprzedni_y = this->koordynaty.pozycja_y;
			this->koordynaty.pozycja_y++; //Sleep(1000);
			return (int)Skutek_kolizji::UCIECZKA;
		}
		else if ((this->getX() != 0) && (czy_moze_wykonac_ruch(this->getX() - 1, this->getY(), lista_organizmów) == true)) // w lewo
		{
			cout << TypOrganizmuToString() << " x[" << this->getX() << "] y[" << this->getY() << "]";
			cout << " Antylopa uniknela kolizji, idzie w lewo\n"; //Sleep(1000);
			this->poprzednie_koordynaty.poprzedni_x = this->koordynaty.pozycja_x;
			this->koordynaty.pozycja_x--; //Sleep(1000);
			return (int)Skutek_kolizji::UCIECZKA;
		}
		else if ((this->getX() != WORLD_WIDTH - 1) && (czy_moze_wykonac_ruch(this->getX() + 1, this->getY(), lista_organizmów) == true)) // w prawo
		{
			cout << TypOrganizmuToString() << " x[" << this->getX() << "] y[" << this->getY() << "]";
			cout << " Antylopa uniknela kolizji, idzie w prawo\n"; //Sleep(1000);
			this->poprzednie_koordynaty.poprzedni_x = this->koordynaty.pozycja_x;
			this->koordynaty.pozycja_x++; //Sleep(1000);
			return (int)Skutek_kolizji::UCIECZKA;
		}
		else
		{
			cout << TypOrganizmuToString() << " x[" << this->getX() << "] y[" << this->getY() << "]";
			cout << " Antylopie nie udalo sie uniknac kolizji, nastapi kolizja\n";
			//Sleep(1000);
		}
	}
	else cout << "BRAK SZANSY NA UCIECZKE ANTYLOPY\n";
	cout << "kolizja: "; ogranizm->OrganizmToSring(); cout << ", "; this->OrganizmToSring(); cout << endl;
	if (this->TypOrganizmuToString() == ogranizm->TypOrganizmuToString())
	{
		ogranizm->setX(ogranizm->getPoprzedniX());
		ogranizm->setY(ogranizm->getPoprzedniY());
		cout << "Rozmnazanie\n";
		//Sleep(1000);
		return (int)Skutek_kolizji::ROZMNAZANIE;
	}
	else
	{
		if (this->sila <= ogranizm->getSila())
		{
			cout << "Umiera inny ogranizm: " << this->TypOrganizmuToString() << endl;
			//Sleep(1000);
			return (int)Skutek_kolizji::SMIERC_INNEGO;
		}
		else if (this->sila > ogranizm->getSila())
		{
			cout << "Umiera ogranizm wykonujacy akcje: " << ogranizm->TypOrganizmuToString() << endl;
			Sleep(2000);
			return (int)Skutek_kolizji::SMIERC_WYKONUJACEGO_AKCJE;
		}
	}
}

bool Antylopa::czy_moze_wykonac_ruch(int pos_x, int pos_y, std::list <Organizm*> lista_organizmów)
{
	bool czy_moze = true;
	for (Organizm* organizm : lista_organizmów)
	{
		if ((organizm->getX() == pos_x) && (organizm->getY() == pos_y))
			czy_moze = false;
	}
	return czy_moze;
}