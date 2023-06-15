#pragma once
#include "Zwierze.h"
class Lis : public Zwierze
{
public:
	Lis(Swiat* swiat, int x, int y, int turaUrodzenia);
	string TypOrganizmuToString() override;
	void rysowanie() override;
	void akcja(std::list<Organizm*>& lista_organizmów) override;
	bool czy_moze_wykonac_ruch(int pos_x, int pos_y, std::list <Organizm*> lista_organizmów);
};