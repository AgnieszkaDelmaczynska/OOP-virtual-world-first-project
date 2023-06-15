#pragma once
#include "Zwierze.h"
class Owca : public Zwierze
{	
public:
	Owca(Swiat* swiat, int x, int y, int turaUrodzenia);
	string TypOrganizmuToString() override;
	void rysowanie() override;
};