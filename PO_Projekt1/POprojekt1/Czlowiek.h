#pragma once
#include "Zwierze.h"
class Czlowiek : public Zwierze
{
public:
	Czlowiek(Swiat* swiat, int x, int y, int turaUrodzenia);
	string TypOrganizmuToString() override;
	void akcja(std::list<Organizm*>& lista_organizmów) override;
	void rysowanie() override;
	class Umiejetnosc
	{
	public:
		Umiejetnosc();
		bool get_czy_umiejetnosc_aktywna();
		void set_czy_umiejetnosc_aktywna(bool czy_aktywna);
		bool get_czy_mozna_aktywowac();
		void set_czy_mozna_aktywowac(bool czy_mozna_aktywowac);
		int get_czas_trwania_umiejetnosci();
		void set_czas_trwania(int czasTrwania);
		int get_czas_aktywacji();
		void set_czas_aktywacji(int dostepny_czas_aktywacji);
		void uaktualnij();
		void aktywuj_umiejetnosc();
		void dezaktywuj_umiejetnosc();
	protected:
		bool czy_aktywna;
		bool czy_mozna_aktywowac;
		int czas_trwania;
		int dostepny_czas_aktywacji;
	};
	Kierunek get_kierunek_ruchu();
	void set_kierunek_ruchu(Kierunek kierunekRuchu);
	Umiejetnosc* get_umiejetnosc();
protected:
	Kierunek kierunek_ruchu;
	Umiejetnosc* umiejetnosc;
	void szybkosc_antylopy();
	void przestaw_koordynaty();
};