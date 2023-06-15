#pragma once
#include "Roslina.h"
class Mlecz : public Roslina
{
public:
	Mlecz(Swiat* swiat, int x, int y, int turaUrodzenia);
	string TypOrganizmuToString() override;
	void akcja(std::list<Organizm*>& lista_organizm�w) override;
	void rysowanie() override;
};