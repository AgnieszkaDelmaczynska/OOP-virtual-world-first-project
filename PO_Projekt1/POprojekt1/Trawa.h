#pragma once
#include "Roslina.h"
class Trawa : public Roslina
{
public:
	Trawa(Swiat* swiat, int x, int y, int turaUrodzenia);
	string TypOrganizmuToString() override;
	void rysowanie() override;
};