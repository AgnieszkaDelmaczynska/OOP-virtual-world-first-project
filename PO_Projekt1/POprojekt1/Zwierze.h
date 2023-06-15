#pragma once
#include "Organizm.h"
class Zwierze : public Organizm
{
public:
	void akcja(std::list<Organizm*>& lista_organizmów) override;
	int kolizja(Organizm* ogranizm_z_ktorym_kolizja, std::list<Organizm*> lista_organizmów) override;
	bool czy_zwierze() override;
	virtual void rysowanie() = 0;
	virtual int getPoprzedniX();
	virtual int getPoprzedniY();
	virtual int setPoprzedniX( int a);
	virtual int setPoprzedniY( int a);
	void Rozmnazanie(std::list<Organizm*> lista_organizmów, Organizm* organizm);
protected:
	struct Pozycja_poprzednia_t
	{
		int poprzedni_x;
		int poprzedni_y;
	}poprzednie_koordynaty;
	bool czy_moze_sie_rozmnazac = true;
	Zwierze(Swiat* swiat, TypOrganizmu typOrganizmu, int sila, int inicjatywa, int x, int y, int turaUrodzenia);
	bool czy_moze_wykonac_ruch(int pos_x, int pos_y, std::list <Organizm*> lista_organizmów);
};