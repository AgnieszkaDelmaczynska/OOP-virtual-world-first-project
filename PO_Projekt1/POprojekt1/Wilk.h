#pragma once
#include "Zwierze.h"
class Wilk : public Zwierze
{
public:
	Wilk(Swiat* swiat, int x, int y, int turaUrodzenia);
	string TypOrganizmuToString() override;
	void rysowanie() override;
};