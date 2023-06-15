#include <iostream>
#include <Windows.h>
#include "Swiat.h"
#include "Organizm.h"
#include <list>

int Organizm::getX()										{ return this->koordynaty.pozycja_x; }
int Organizm::getY()										{ return this->koordynaty.pozycja_y; }
int Organizm::setX(int a)									{ return this->koordynaty.pozycja_x = a; }
int Organizm::setY(int a)									{ return this->koordynaty.pozycja_y = a; }
int Organizm::getSila()										{ return this->sila; }
int Organizm::getInicjatywa()								{ return this->inicjatywa; }
int Organizm::setInicjatywa(int a)							{ return this->inicjatywa = a; }
int Organizm::setSila(int a)								{ return this->sila = a; }
int Organizm::get_tura_urodzenia()							{ return turaUrodzenia; }
void Organizm::set_tura_urodzenia(int turaUrodzenia)		{ this->turaUrodzenia = turaUrodzenia; }
Organizm::TypOrganizmu Organizm::GetTypOrganizmu()			{ return typOrganizmu; }
void Organizm::SetTypOrganizmu(TypOrganizmu typOrganizmu)	{ this->typOrganizmu = typOrganizmu; }

Organizm::Organizm(Swiat* swiat, TypOrganizmu typOrganizmu, int sila, int inicjatywa, int x, int y, int turaUrodzenia)
{
	this->swiat = swiat;
	this->typOrganizmu = typOrganizmu;
	this->sila = sila;
	this->inicjatywa = inicjatywa;
	this->koordynaty.pozycja_x = x;
	this->koordynaty.pozycja_y = y;
	this->turaUrodzenia = turaUrodzenia;
}

void Organizm::OrganizmToSring()
{
	cout << TypOrganizmuToString() << " x[" << this->getX() << "] y[" << this->getY() << "] sila["<<this->sila<<"] inicjatywa["<< this->inicjatywa<<"]";
	//Sleep(1000);
	return;
}