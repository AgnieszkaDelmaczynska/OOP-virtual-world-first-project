#pragma once
#include <iostream>
#include <list>
#include "Swiat.h"
#include "Organizm.h"
using namespace std;
class Swiat;
class Organizm
{
public:
	enum class Kierunek
	{
		GORA,
		DOL,
		LEWO,
		PRAWO,
		BRAK_KIERUNKU
	};
	enum class Skutek_kolizji
	{
		ROZMNAZANIE,
		SMIERC_WYKONUJACEGO_AKCJE,
		SMIERC_INNEGO,
		ODGONIENIE,
		UCIECZKA,
		SMIERC_OBU
	};
	enum class TypOrganizmu
	{
		CZLOWIEK,
		OWCA,
		WILK,
		LIS,
		ZOLW,
		ANTYLOPA,
		TRAWA,
		MLECZ,
		GUARANA,
		WILCZE_JAGODY,
		BARSZCZ_SOSNOWSKIEGO
	};
	TypOrganizmu GetTypOrganizmu();
	void SetTypOrganizmu(TypOrganizmu typOrganizmu);

	virtual void akcja(std::list<Organizm*>& lista_organizmów) = 0;
	virtual int kolizja(Organizm* ogranizm_z_ktorym_kolizja, std::list<Organizm*> lista_organizmów) = 0;
	virtual string TypOrganizmuToString() = 0;
	virtual bool czy_zwierze() = 0;
	virtual void rysowanie() = 0;

	virtual int getX();
	virtual int getY();
	virtual int setX(int a);
	virtual int setY(int a);
	virtual int getSila();
	virtual int getPoprzedniX() = 0;
	virtual int getPoprzedniY() = 0;
	virtual int getInicjatywa();
	virtual int setSila(int a);
	virtual int setInicjatywa(int a);
	virtual void set_tura_urodzenia(int turaurodzenia);
	virtual int get_tura_urodzenia();
	void OrganizmToSring();
	bool do_usuniecia = false;
protected:
	int sila, inicjatywa, turaUrodzenia;
	Swiat* swiat;
	struct Pozycja_t
	{
		int pozycja_x;
		int pozycja_y;
	} koordynaty;
	TypOrganizmu typOrganizmu;
	Organizm(Swiat* swiat, TypOrganizmu typOrganizmu, int sila, int inicjatywa, int x, int y, int turaUrodzenia);
};