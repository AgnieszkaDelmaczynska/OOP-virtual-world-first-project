#include "Czlowiek.h";
#include "Kolory.h"
#define CZLOWIEK_SILA 5
#define CZLOWIEK_INICJATYWA 4
#define CZAS_TRWANIA_UMIEJETNOSCI 5
#define COOLDOWN_UMIEJETNOSCI 10

using namespace std;

Czlowiek::Czlowiek(Swiat* swiat, int x, int y, int turaUrodzenia)
	:Zwierze(swiat, TypOrganizmu::CZLOWIEK, CZLOWIEK_SILA, CZLOWIEK_INICJATYWA, x, y, turaUrodzenia)
{
	kierunek_ruchu = Kierunek::BRAK_KIERUNKU;
	umiejetnosc = new Umiejetnosc();
}
string Czlowiek::TypOrganizmuToString()
{
	return "Czlowiek";
}
void Czlowiek::rysowanie()
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, WHITE);
	cout << (char)254;// "C";
	SetConsoleTextAttribute(hOut, WHITE);
}
Organizm::Kierunek Czlowiek::get_kierunek_ruchu()
{
	return kierunek_ruchu;
}

void Czlowiek::set_kierunek_ruchu(Kierunek kierunek_ruchu)
{
	this->kierunek_ruchu = kierunek_ruchu;
}
void Czlowiek::akcja(std::list<Organizm*>& lista_organizmów)
{
	if (umiejetnosc->get_czy_umiejetnosc_aktywna())
	{
		cout << " 'Szybkosc antylopy' jest aktywna(Pozostaly czas trwania: " << umiejetnosc->get_czas_trwania_umiejetnosci() << " tur)\n";
		//Sleep(1000);
		szybkosc_antylopy();
	}
	przestaw_koordynaty();
	kierunek_ruchu = Kierunek::BRAK_KIERUNKU;
	umiejetnosc->uaktualnij();
}
void Czlowiek::przestaw_koordynaty()
{
	if ((kierunek_ruchu == Kierunek::GORA) && (this->getY() != 0))
		this->setY(this->getY() - 1);
	else if ((kierunek_ruchu == Kierunek::DOL) && (this->getY() != WORLD_HEIGHT - 1))
		this->setY(this->getY() + 1);
	else if ((kierunek_ruchu == Kierunek::LEWO) && (this->getX() != 0))
		this->setX(this->getX() - 1);
	else if ((kierunek_ruchu == Kierunek::PRAWO) && (this->getX() != WORLD_WIDTH - 1))
		this->setX(this->getX() + 1);
	else
		cout << "Czlowiek nie moze wyjsc z zagrody\n";
}
void Czlowiek::szybkosc_antylopy()
{
	if (umiejetnosc->get_czas_trwania_umiejetnosci() >= 3)
		przestaw_koordynaty();
	else
	{
		int losuj = rand() % 2;
		if (losuj == 1) // szansa, że wylosuje 1 to 50%
			przestaw_koordynaty();
	}
}
Czlowiek::Umiejetnosc* Czlowiek::get_umiejetnosc()
{
	return umiejetnosc;
}
Czlowiek::Umiejetnosc::Umiejetnosc()
{
	czy_aktywna = false;
	czy_mozna_aktywowac = true;
	czas_trwania = 0;
	dostepny_czas_aktywacji = 0;
}

bool Czlowiek::Umiejetnosc::get_czy_umiejetnosc_aktywna()						{return czy_aktywna;}
void Czlowiek::Umiejetnosc::set_czy_umiejetnosc_aktywna(bool czy_aktywna)		{this->czy_aktywna = czy_aktywna;}

bool Czlowiek::Umiejetnosc::get_czy_mozna_aktywowac()							{return czy_mozna_aktywowac;}
void Czlowiek::Umiejetnosc::set_czy_mozna_aktywowac(bool czy_mozna_aktywowac)	{this->czy_mozna_aktywowac = czy_mozna_aktywowac;}

int Czlowiek::Umiejetnosc::get_czas_trwania_umiejetnosci()						{return czas_trwania;}
void Czlowiek::Umiejetnosc::set_czas_trwania(int czas_trwania)					{this->czas_trwania = czas_trwania;}

int Czlowiek::Umiejetnosc::get_czas_aktywacji()									{return dostepny_czas_aktywacji;}
void Czlowiek::Umiejetnosc::set_czas_aktywacji(int dostepny_czas_aktywacji)		{this->dostepny_czas_aktywacji = dostepny_czas_aktywacji;}

void Czlowiek::Umiejetnosc::uaktualnij()
{
	if (dostepny_czas_aktywacji > 0) dostepny_czas_aktywacji--;
	if (czas_trwania > 0) czas_trwania--;
	if (czas_trwania == 0) dezaktywuj_umiejetnosc();
	if (dostepny_czas_aktywacji == 0) czy_mozna_aktywowac = true;
}

void Czlowiek::Umiejetnosc::aktywuj_umiejetnosc()
{
	if (dostepny_czas_aktywacji == 0)
	{
		czy_aktywna = true;
		czy_mozna_aktywowac = false;
		dostepny_czas_aktywacji = COOLDOWN_UMIEJETNOSCI;
		czas_trwania = CZAS_TRWANIA_UMIEJETNOSCI;
	}
	else if (dostepny_czas_aktywacji > 0)
	{
		cout << "Umiejetnosc 'Szybkosc antylopy' bedzie mozna wlaczyc po " << dostepny_czas_aktywacji << " turach\n";
		Sleep(3000);
	}
}

void Czlowiek::Umiejetnosc::dezaktywuj_umiejetnosc()						
{
	czy_aktywna = false;
}