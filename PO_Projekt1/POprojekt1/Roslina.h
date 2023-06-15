#pragma once
#include "Organizm.h"
class Roslina : public Organizm
{
public:
	void akcja(std::list<Organizm*>& lista_organizmów) override;
	int kolizja(Organizm* ogranizm_z_ktorym_kolizja, std::list<Organizm*> lista_organizmów) override;
	bool czy_zwierze() override;
	virtual int getPoprzedniX();
	virtual int getPoprzedniY();
	void rysowanie() = 0;
protected:
	Roslina(Swiat* swiat, TypOrganizmu typOrganizmu, int sila, int inicjatywa, int x, int y, int turaUrodzenia);
	void Rozprzestrzenianie(std::list<Organizm*> lista_organizmów);
	bool czy_moze_wykonac_ruch(int pos_x, int pos_y, std::list <Organizm*> lista_organizmów);
};