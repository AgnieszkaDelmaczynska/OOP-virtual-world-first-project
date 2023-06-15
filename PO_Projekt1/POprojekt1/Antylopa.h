#pragma once
#include "Zwierze.h"
class Antylopa : public Zwierze
{
public:
	Antylopa(Swiat* swiat, int x, int y, int turaUrodzenia);
	string TypOrganizmuToString() override;
	void rysowanie() override;
	int kolizja(Organizm* ogranizm_z_ktorym_kolizja, std::list<Organizm*> lista_organizmów) override;
	void akcja(std::list<Organizm*>& lista_organizmów) override;
	bool czy_moze_wykonac_ruch(int pos_x, int pos_y, std::list <Organizm*> lista_organizmów);
};