#include "TworzenieOrganizmow.h"

Organizm* TworzenieOrganizmow::stworz_nowy_organizm(Swiat* swiat, Organizm::TypOrganizmu typOrganizmu, int x, int y)
{
	switch (typOrganizmu) 
	{
		case Organizm::TypOrganizmu::CZLOWIEK:				return	new Czlowiek(swiat, x, y, swiat->get_numer_tury());
		case Organizm::TypOrganizmu::OWCA:					return	new Owca(swiat, x, y, swiat->get_numer_tury());
		case Organizm::TypOrganizmu::WILK:					return	new Wilk(swiat, x, y, swiat->get_numer_tury());
		case Organizm::TypOrganizmu::LIS:					return	new Lis(swiat, x, y, swiat->get_numer_tury());
		case Organizm::TypOrganizmu::ZOLW:					return	new Zolw(swiat, x, y, swiat->get_numer_tury());
		case Organizm::TypOrganizmu::ANTYLOPA:				return	new Antylopa(swiat, x, y, swiat->get_numer_tury());
		case Organizm::TypOrganizmu::TRAWA:					return  new Trawa(swiat, x, y, swiat->get_numer_tury());
		case Organizm::TypOrganizmu::MLECZ:					return  new Mlecz(swiat, x, y, swiat->get_numer_tury());
		case Organizm::TypOrganizmu::GUARANA:				return  new Guarana(swiat, x, y, swiat->get_numer_tury());
		case Organizm::TypOrganizmu::WILCZE_JAGODY:			return  new WilczeJagody(swiat, x, y, swiat->get_numer_tury());
		case Organizm::TypOrganizmu::BARSZCZ_SOSNOWSKIEGO:	return  new BarszczSosnowskiego(swiat, x, y, swiat->get_numer_tury());
		default: return nullptr;
	}
}