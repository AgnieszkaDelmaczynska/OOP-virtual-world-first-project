#pragma once
#include "Zwierze.h"
class Zolw : public Zwierze
{
public:
	Zolw(Swiat* swiat, int x, int y, int turaUrodzenia);
	string TypOrganizmuToString() override;
	void rysowanie() override;
	int kolizja(Organizm* ogranizm_z_ktorym_kolizja, std::list<Organizm*> lista_organizmów) override;
	void akcja(std::list<Organizm*>& lista_organizmów) override;
};