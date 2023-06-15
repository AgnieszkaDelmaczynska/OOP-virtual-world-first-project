#pragma once
#include "Roslina.h"
class WilczeJagody : public Roslina
{
public:
	WilczeJagody(Swiat* swiat, int x, int y, int turaUrodzenia);
	string TypOrganizmuToString() override;
	void rysowanie() override;
	int kolizja(Organizm* ogranizm_z_ktorym_kolizja, std::list<Organizm*> lista_organizmów) override;
};