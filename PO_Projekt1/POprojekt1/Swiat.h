#pragma once
#include <list>
#include "Organizm.h"
#define WORLD_HEIGHT 20
#define WORLD_WIDTH 20
class Organizm;
class Czlowiek;
class Swiat
{
public:
	Swiat();
	void wykonaj_ture();
	int get_numer_tury();
	void rysuj_swiat();
	void usun_organizm(Organizm* usuwany_organizm);
	void kandydat_do_usuniecia(Organizm* kandydat);
	void czyszczenie();
	bool get_czy_czlowiek_zyje();
	void set_czy_czlowiek_zyje(bool czyCzlowiekZyje);
	bool get_czy_jest_koniec_gry();
	void set_czy_jest_koniec_gry(bool czyJestKoniecGry);
	void sort_list(std::list<Organizm*> &lista_organizmów);
	void pchnij_organizm_na_liste(Organizm* organizm);
protected:
	int world_height = WORLD_HEIGHT;
	int world_width = WORLD_WIDTH;
	std::list <Organizm*> lista_organizmów;
	int numer_tury = 0;
	Czlowiek* czlowiek;
	void obsluga_klawiatury();
	bool czy_czlowiek_zyje;
	bool czy_jest_koniec_gry;
};