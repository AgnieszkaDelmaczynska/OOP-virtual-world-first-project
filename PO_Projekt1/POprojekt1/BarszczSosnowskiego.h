#pragma once
#include "Roslina.h"
class BarszczSosnowskiego : public Roslina
{
public:
	BarszczSosnowskiego(Swiat* swiat, int x, int y, int turaUrodzenia);
	string TypOrganizmuToString() override;
	void rysowanie() override;
	int kolizja(Organizm* organizm, std::list<Organizm*> lista_organizmów) override;
	void akcja(std::list<Organizm*>& lista_organizmów) override;
	bool czy_moze_wykonac_ruch(int pos_x, int pos_y, std::list <Organizm*> lista_organizmów);
};