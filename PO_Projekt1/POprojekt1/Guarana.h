#pragma once
#include "Roslina.h"
class Guarana : public Roslina
{
public:
	Guarana(Swiat* swiat, int x, int y, int turaUrodzenia);
	string TypOrganizmuToString() override;
	void rysowanie() override;
	int kolizja(Organizm* ogranizm_z_ktorym_kolizja, std::list<Organizm*> lista_organizmów) override;
};