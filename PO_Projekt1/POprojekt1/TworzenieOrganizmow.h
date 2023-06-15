#pragma once
#include "Wszystkie_klasy.h"
#include "Organizm.h"

class TworzenieOrganizmow
{
public:
	static Organizm* stworz_nowy_organizm(Swiat* swiat, Organizm::TypOrganizmu typOrganizmu, int x, int y);
};