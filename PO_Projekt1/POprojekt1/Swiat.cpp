#pragma once
#include <iostream>
#include <list>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include "Swiat.h"
#include "Wszystkie_klasy.h"
#include "TworzenieOrganizmow.h"
#include "Klawiatura.h"
#include <conio.h>
#include <string>
using namespace std;

int Swiat::get_numer_tury()										{ return numer_tury; }
bool Swiat::get_czy_czlowiek_zyje()								{ return czy_czlowiek_zyje;}
void Swiat::set_czy_czlowiek_zyje(bool czy_czlowiek_zyje)		{ this->czy_czlowiek_zyje = czy_czlowiek_zyje;}
bool Swiat::get_czy_jest_koniec_gry()							{ return czy_jest_koniec_gry;}
void Swiat::set_czy_jest_koniec_gry(bool czy_jest_koniec_gry)	{ this->czy_jest_koniec_gry = czy_jest_koniec_gry;}
void Swiat::pchnij_organizm_na_liste(Organizm* organizm)		{ lista_organizmów.push_back(organizm); }

void Swiat::sort_list(std::list<Organizm*> &lista_organizmów) // po inicjatywie i turze
{
	for (auto itr1 = lista_organizmów.begin(); itr1 != lista_organizmów.end(); itr1++)
	{
		for (auto itr2 = lista_organizmów.begin(); itr2 != lista_organizmów.end(); itr2++)
		{
			if ((*itr2)->getInicjatywa() < (*itr1)->getInicjatywa())
			{
				auto temp = *itr1;
				*itr1 = *itr2;
				*itr2 = temp;
			}
		}
	}
}

void Swiat::wykonaj_ture()
{
	Sleep(2000);
	sort_list(lista_organizmów);
	//for (auto it = lista_organizmów.begin(); it != lista_organizmów.end(); ++it)	// poomcniczo wyświetlenie posortowanej listy
	//{
	//	cout << ' ' << (*it)->TypOrganizmuToString();
	//	cout << ' ' << (*it)->get_tura_urodzenia();
	//}
	obsluga_klawiatury();
	if (czy_jest_koniec_gry == true) return;
	numer_tury++;
	//cout << numer_tury << "		" << get_numer_tury() << endl << endl; Sleep(1000);
	for (Organizm* organizm : this->lista_organizmów)
	{
		//cout << organizm->get_tura_urodzenia() << "		" << this->numer_tury << endl; Sleep(1000);
		if (organizm->get_tura_urodzenia() != this->numer_tury)
		{
			int skutek_kolizji = 0;
			organizm->akcja(lista_organizmów);
			for (Organizm* organizm_inny : this->lista_organizmów)
			{
				if ((organizm->getX() == organizm_inny->getX()) && (organizm->getY() == organizm_inny->getY()) && (organizm != organizm_inny) && (organizm->do_usuniecia == false) && (organizm_inny->do_usuniecia == false))
				{
					skutek_kolizji = organizm_inny->kolizja(organizm, lista_organizmów);		//	kolizja innego organizmu
					if (skutek_kolizji == (int)Organizm::Skutek_kolizji::SMIERC_WYKONUJACEGO_AKCJE)
					{
						kandydat_do_usuniecia(organizm); break;
					}
					else if (skutek_kolizji == (int)Organizm::Skutek_kolizji::SMIERC_INNEGO)
					{
						usun_organizm(organizm_inny); break;
					}
					else if (skutek_kolizji == (int)Organizm::Skutek_kolizji::SMIERC_OBU)
					{
						kandydat_do_usuniecia(organizm);
						usun_organizm(organizm_inny);
						break;
					}
				}
			}
		}
		//this->rysuj_swiat();
		//Sleep(1000);
	}
	cout << "KONIEC TURY " << numer_tury;
	Sleep(2000);
	czyszczenie();
}

void Swiat::czyszczenie()
{
	for (Organizm* organizm : this->lista_organizmów)
	{
		if (organizm->do_usuniecia == true)
		{
			usun_organizm(organizm);
			czyszczenie();
			break;
		}
	}
}

void Swiat::kandydat_do_usuniecia(Organizm* kandydat)
{
	for (auto itr = lista_organizmów.begin(); itr != lista_organizmów.end(); itr++)
		if (*itr == kandydat)
			kandydat->do_usuniecia = true;
}

void Swiat::usun_organizm(Organizm* usuwany_organizm)
{
	for (auto itr = lista_organizmów.begin(); itr != lista_organizmów.end(); itr++)
		if (*itr == usuwany_organizm)
		{
			if (usuwany_organizm->GetTypOrganizmu() == Organizm::TypOrganizmu::CZLOWIEK)
			{
				czy_czlowiek_zyje = false;
				czlowiek = nullptr;
			}
			lista_organizmów.erase(itr);
			usuwany_organizm->~Organizm();
			return;
		}
}

void Swiat::rysuj_swiat()
{
	system("CLS");
	cout << "Agnieszka Delmaczynska 184592\n";
	cout << "                                   ^\n";
	cout << "Kierowanie czlowiekiem: strzalki <   >\n";
	cout << "                                   v\n";
	cout << "X - Wyjscie | Enter - kolejna tura | U - wlacz specjalna umiejetnosc\n\n";
	cout << "Numer tury: " << get_numer_tury() << endl;
	//.......................... 01234567890123456789
	cout << "   ";
	for(int i=0; i<2; i++)
	for (int x = 0; x <10; x++)
		cout << x;
	//..........................
	cout << endl;
	//.......................... 0-19 w pionie
	int temp = -2;
	for (int y = 0; y < WORLD_HEIGHT + 2; y++)
	{	
		temp++;
		if (temp == -1 || temp == WORLD_HEIGHT) cout << "  ";
		else if (temp > -1 && temp < 10) cout << " " << temp;
		else cout << temp;
		for (int x = 0; x < WORLD_WIDTH + 2; x++)
	//.......................... rysowanie zagrody, organizmów i pustych miejsc
		{	
			bool printed = false;
			if (x == 0 && y == 0)									{	cout << char(201); /* ╔ */	printed = true;}
			else if (x == WORLD_WIDTH + 1 && y == 0)				{	cout << char(187); /* ╗ */	printed = true;}
			else if (x == 0 && y == WORLD_HEIGHT + 1)				{	cout << char(200); /* ╚ */	printed = true;}
			else if (x == WORLD_WIDTH + 1 && y == WORLD_HEIGHT + 1)	{	cout << char(188); /* ╝ */	printed = true;}
			else if (x == 0 || x == WORLD_WIDTH + 1)				{	cout << char(186); /* ║	*/  printed = true;}
			else if (y == 0 || y == WORLD_HEIGHT + 1)				{	cout << char(205); /* ═ */	printed = true;}
			else 
				for (Organizm* organizm : this->lista_organizmów)
				{
					if (organizm->getX() == x-1 && organizm->getY() == y-1)
					{
						organizm->rysowanie();
						printed = true;
					}
				}
			if (printed == false) cout << " ";
		}
		cout << endl;	
	}
	int liczba_organizmow = 0;
	for (Organizm* organizm : this->lista_organizmów)	// zliczenie wszystkich organizmów, pętla po całej liście
	{
		liczba_organizmow++;
		//cout << "Organizm: " << liczba_organizmow << " (" << organizm->getX() << "," << organizm->getY() << ")	" << organizm->TypOrganizmuToString() << endl;
	}
	cout << "\nLiczba organizmow: " << liczba_organizmow << " \n";
}

void Swiat::obsluga_klawiatury()
{
	while (true)
	{
		cout << endl << "Nacisnij klawisz\n";
		int wcisniety_klawisz;
		wcisniety_klawisz = _getch();
		if (wcisniety_klawisz == STRZALKI)	// sterowanie czlowiekiem
		{
			if (czy_czlowiek_zyje)
			{
				wcisniety_klawisz = _getch();
				switch (wcisniety_klawisz)
				{
				case UP:
					if (czlowiek->getY() != 0)					{ czlowiek->set_kierunek_ruchu(Organizm::Kierunek::GORA); return; }
					else										{ cout << "Czlowiek nie moze wyjsc z zagrody\n"; continue; }
				case DOWN:
					if (czlowiek->getY() != WORLD_HEIGHT - 1)	{ czlowiek->set_kierunek_ruchu(Organizm::Kierunek::DOL); return; }
					else										{ cout << "Czlowiek nie moze wyjsc z zagrody\n"; continue; }
				case LEFT:
					if (czlowiek->getX() != 0)					{ czlowiek->set_kierunek_ruchu(Organizm::Kierunek::LEWO); return; }
					else										{ cout << "Czlowiek nie moze wyjsc z zagrody\n"; continue; }
				case RIGHT:
					if (czlowiek->getX() != WORLD_WIDTH - 1)	{ czlowiek->set_kierunek_ruchu(Organizm::Kierunek::PRAWO); return; }
					else										{ cout << "Czlowiek nie moze wyjsc z zagrody\n"; continue; }						
				}
			}
			else
			{
				cout << "KONIEC GRY. Czlowiek umarl\n";
				Sleep(4000);
				czy_jest_koniec_gry = true;
				break;
			}
		}
		if ((czy_czlowiek_zyje == true) && (wcisniety_klawisz == UMIEJETNOSC))	// aktywacja umiejetnosci
		{
			Czlowiek::Umiejetnosc* tmpUmiejetnosc = czlowiek->get_umiejetnosc();
			if (tmpUmiejetnosc->get_czy_mozna_aktywowac())
			{
				tmpUmiejetnosc->aktywuj_umiejetnosc();
				cout << "Umiejetnosc 'Szybkosc antylopy' aktywowana.(Jej pozostaly czas trwania wynosi " << tmpUmiejetnosc->get_czas_trwania_umiejetnosci() <<" tur)\n";
				break;
			}
			else if (tmpUmiejetnosc->get_czy_umiejetnosc_aktywna())
			{
				cout << "Umiejetnosc byla juz aktywna (Jej pozostaly czas trwania wynosi "<< tmpUmiejetnosc->get_czas_trwania_umiejetnosci() << " tur)\n";
				continue;
			}
			else
			{
				cout << "Umiejetnosc mozna wlaczyc tylko po " << tmpUmiejetnosc->get_czas_aktywacji() << " turach\n";
				continue;
			}
		}
		if (wcisniety_klawisz == ENTER)
		{
			if (czy_czlowiek_zyje == true)	break;	// przejscie do  kolejnej tury
			else
			{
				cout << "KONIEC GRY. Czlowiek umarl\n";
				Sleep(5000);
				czy_jest_koniec_gry = true;
				break;
			}
		}
		if (wcisniety_klawisz == EXIT)			// wyjscie z gry
		{
			cout << "Koniec gry\n";
			Sleep(3000);
			czy_jest_koniec_gry = true;
			break;
		}
		else
		{
			cout << "Nieoznaczony symbol, wybierz inny klawisz\n";
			continue;
		}
	}
}

Swiat::Swiat()
{
	srand(time(NULL));
	czy_czlowiek_zyje = true;
	czy_jest_koniec_gry = false;

	Czlowiek* czlowiek_temp = new Czlowiek(this, 17, 3, this->get_numer_tury());
	czlowiek = czlowiek_temp;

	Owca* new_owca = new Owca(this, 0, 12, this->get_numer_tury());
	Owca* new_owca1 = new Owca(this, 1, 7, this->get_numer_tury());
	Owca* new_owca2 = new Owca(this, 2, 2, this->get_numer_tury());
	Owca* new_owca3 = new Owca(this, 4, 2, this->get_numer_tury());
	Owca* new_owca4 = new Owca(this, 5, 8, this->get_numer_tury());
	Owca* new_owca5 = new Owca(this, 6, 7, this->get_numer_tury());
	Owca* new_owca6 = new Owca(this, 7, 15, this->get_numer_tury());
	Owca* new_owca7 = new Owca(this, 7, 17, this->get_numer_tury());
	Owca* new_owca8 = new Owca(this, 8, 12, this->get_numer_tury());
	Owca* new_owca9 = new Owca(this, 11, 0, this->get_numer_tury());
	Owca* new_owca10 = new Owca(this, 13, 3, this->get_numer_tury());
	Owca* new_owca11 = new Owca(this, 15, 11, this->get_numer_tury());
	Owca* new_owca12 = new Owca(this, 15, 16, this->get_numer_tury());
	Owca* new_owca13 = new Owca(this, 18, 0, this->get_numer_tury());
	Owca* new_owca14 = new Owca(this, 19, 19, this->get_numer_tury());

	Wilk* new_wilk = new Wilk(this, 1, 1, this->get_numer_tury());
	Wilk* new_wilk1 = new Wilk(this, 1, 4, this->get_numer_tury());
	Wilk* new_wilk2 = new Wilk(this, 3, 3, this->get_numer_tury());
	Wilk* new_wilk3 = new Wilk(this, 3, 8, this->get_numer_tury());
	Wilk* new_wilk4 = new Wilk(this, 4, 4, this->get_numer_tury());
	Wilk* new_wilk5 = new Wilk(this, 4, 7, this->get_numer_tury());
	Wilk* new_wilk6 = new Wilk(this, 6, 6, this->get_numer_tury());
	Wilk* new_wilk7 = new Wilk(this, 8, 8, this->get_numer_tury());
	Wilk* new_wilk8 = new Wilk(this, 10, 13, this->get_numer_tury());
	Wilk* new_wilk9 = new Wilk(this, 11, 11, this->get_numer_tury());
	Wilk* new_wilk10 = new Wilk(this, 12, 12, this->get_numer_tury());
	Wilk* new_wilk11 = new Wilk(this, 14, 0, this->get_numer_tury());
	Wilk* new_wilk12 = new Wilk(this, 14, 11, this->get_numer_tury());
	Wilk* new_wilk13 = new Wilk(this, 15, 15, this->get_numer_tury());
	Wilk* new_wilk14 = new Wilk(this, 18, 18, this->get_numer_tury());

	Lis* new_lis = new Lis(this, 1, 6, this->get_numer_tury());
	Lis* new_lis1 = new Lis(this, 1, 8, this->get_numer_tury());
	Lis* new_lis2 = new Lis(this, 1, 11, this->get_numer_tury());
	Lis* new_lis3 = new Lis(this, 2, 4, this->get_numer_tury());
	Lis* new_lis4 = new Lis(this, 3, 7, this->get_numer_tury());
	Lis* new_lis5 = new Lis(this, 4, 1, this->get_numer_tury());
	Lis* new_lis6 = new Lis(this, 5, 9, this->get_numer_tury());
	Lis* new_lis7 = new Lis(this, 7, 7, this->get_numer_tury());
	Lis* new_lis8 = new Lis(this, 8, 1, this->get_numer_tury());
	Lis* new_lis9 = new Lis(this, 8, 5, this->get_numer_tury());
	Lis* new_lis10 = new Lis(this, 10, 7, this->get_numer_tury());
	Lis* new_lis11 = new Lis(this, 13, 1, this->get_numer_tury());
	Lis* new_lis12 = new Lis(this, 13, 13, this->get_numer_tury());
	Lis* new_lis13 = new Lis(this, 14, 10, this->get_numer_tury());
	Lis* new_lis14 = new Lis(this, 17, 11, this->get_numer_tury());

	Zolw* new_zolw = new Zolw(this, 1, 13, this->get_numer_tury());
	Zolw* new_zolw1 = new Zolw(this, 1, 18, this->get_numer_tury());
	Zolw* new_zolw2 = new Zolw(this, 4, 9, this->get_numer_tury());
	Zolw* new_zolw3 = new Zolw(this, 5, 5, this->get_numer_tury());
	Zolw* new_zolw4 = new Zolw(this, 5, 10, this->get_numer_tury());
	Zolw* new_zolw5 = new Zolw(this, 6, 1, this->get_numer_tury());
	Zolw* new_zolw6 = new Zolw(this, 7, 10, this->get_numer_tury());
	Zolw* new_zolw7 = new Zolw(this, 9, 3, this->get_numer_tury());
	Zolw* new_zolw8 = new Zolw(this, 9, 14, this->get_numer_tury());
	Zolw* new_zolw9 = new Zolw(this, 10, 14, this->get_numer_tury());
	Zolw* new_zolw10 = new Zolw(this, 11, 1, this->get_numer_tury());
	Zolw* new_zolw11 = new Zolw(this, 11, 17, this->get_numer_tury());
	Zolw* new_zolw12 = new Zolw(this, 12, 1, this->get_numer_tury());
	Zolw* new_zolw13 = new Zolw(this, 16, 0, this->get_numer_tury());
	Zolw* new_zolw14 = new Zolw(this, 19, 15, this->get_numer_tury());

	Antylopa* new_antylopa = new Antylopa(this, 3, 18, this->get_numer_tury());
	Antylopa* new_antylopa1 = new Antylopa(this, 4, 6, this->get_numer_tury());
	Antylopa* new_antylopa2 = new Antylopa(this, 4, 12, this->get_numer_tury());
	Antylopa* new_antylopa3 = new Antylopa(this, 7, 16, this->get_numer_tury());
	Antylopa* new_antylopa4 = new Antylopa(this, 9, 5, this->get_numer_tury());
	Antylopa* new_antylopa5 = new Antylopa(this, 11, 14, this->get_numer_tury());
	Antylopa* new_antylopa6 = new Antylopa(this, 12, 3, this->get_numer_tury());
	Antylopa* new_antylopa7 = new Antylopa(this, 13, 15, this->get_numer_tury());
	Antylopa* new_antylopa8 = new Antylopa(this, 14, 7, this->get_numer_tury());
	Antylopa* new_antylopa9 = new Antylopa(this, 15, 10, this->get_numer_tury());
	Antylopa* new_antylopa10 = new Antylopa(this, 15, 19, this->get_numer_tury());
	Antylopa* new_antylopa11 = new Antylopa(this, 18, 6, this->get_numer_tury());
	Antylopa* new_antylopa12 = new Antylopa(this, 18, 15, this->get_numer_tury());
	Antylopa* new_antylopa13 = new Antylopa(this, 19, 12, this->get_numer_tury());
	Antylopa* new_antylopa14 = new Antylopa(this, 19, 13, this->get_numer_tury());

	Trawa* new_trawa = new Trawa(this, 3, 16, this->get_numer_tury());
	Trawa* new_trawa1 = new Trawa(this, 4, 17, this->get_numer_tury());
	Trawa* new_trawa2 = new Trawa(this, 5, 3, this->get_numer_tury());
	Trawa* new_trawa3 = new Trawa(this, 5, 14, this->get_numer_tury());
	Trawa* new_trawa4 = new Trawa(this, 6, 19, this->get_numer_tury());
	Trawa* new_trawa5 = new Trawa(this, 7, 0, this->get_numer_tury());
	Trawa* new_trawa6 = new Trawa(this, 8, 6, this->get_numer_tury());
	Trawa* new_trawa7 = new Trawa(this, 8, 19, this->get_numer_tury());
	Trawa* new_trawa8 = new Trawa(this, 8, 11, this->get_numer_tury());
	Trawa* new_trawa9 = new Trawa(this, 10, 12, this->get_numer_tury());
	Trawa* new_trawa10 = new Trawa(this, 10, 19, this->get_numer_tury());
	Trawa* new_trawa11 = new Trawa(this, 11, 5, this->get_numer_tury());
	Trawa* new_trawa12 = new Trawa(this, 15, 5, this->get_numer_tury());
	Trawa* new_trawa13 = new Trawa(this, 18, 2, this->get_numer_tury());
	Trawa* new_trawa14 = new Trawa(this, 19, 3, this->get_numer_tury());

	Mlecz* new_mlecz = new Mlecz(this, 2, 0, this->get_numer_tury());
	Mlecz* new_mlecz1 = new Mlecz(this, 2, 15, this->get_numer_tury());
	Mlecz* new_mlecz2 = new Mlecz(this, 3, 10, this->get_numer_tury());
	Mlecz* new_mlecz3 = new Mlecz(this, 6, 13, this->get_numer_tury());
	Mlecz* new_mlecz4 = new Mlecz(this, 8, 9, this->get_numer_tury());
	Mlecz* new_mlecz5 = new Mlecz(this, 9, 4, this->get_numer_tury());
	Mlecz* new_mlecz6 = new Mlecz(this, 9, 6, this->get_numer_tury());
	Mlecz* new_mlecz7 = new Mlecz(this, 12, 4, this->get_numer_tury());
	Mlecz* new_mlecz8 = new Mlecz(this, 12, 8, this->get_numer_tury());
	Mlecz* new_mlecz9 = new Mlecz(this, 12, 16, this->get_numer_tury());
	Mlecz* new_mlecz10 = new Mlecz(this, 12, 18, this->get_numer_tury());
	Mlecz* new_mlecz11 = new Mlecz(this, 13, 9, this->get_numer_tury());
	Mlecz* new_mlecz12 = new Mlecz(this, 14, 9, this->get_numer_tury());
	Mlecz* new_mlecz13 = new Mlecz(this, 15, 2, this->get_numer_tury());
	Mlecz* new_mlecz14 = new Mlecz(this, 16, 17, this->get_numer_tury());

	Guarana* new_guarana = new Guarana(this, 1, 16, this->get_numer_tury());
	Guarana* new_guarana1 = new Guarana(this, 2, 9, this->get_numer_tury());
	Guarana* new_guarana2 = new Guarana(this, 3, 0, this->get_numer_tury());
	Guarana* new_guarana3 = new Guarana(this, 3, 14, this->get_numer_tury());
	Guarana* new_guarana4 = new Guarana(this, 3, 19, this->get_numer_tury());
	Guarana* new_guarana5 = new Guarana(this, 4, 19, this->get_numer_tury());
	Guarana* new_guarana6 = new Guarana(this, 7, 3, this->get_numer_tury());
	Guarana* new_guarana7 = new Guarana(this, 8, 10, this->get_numer_tury());
	Guarana* new_guarana8 = new Guarana(this, 10, 2, this->get_numer_tury());
	Guarana* new_guarana9 = new Guarana(this, 11, 10, this->get_numer_tury());
	Guarana* new_guarana10 = new Guarana(this, 12, 6, this->get_numer_tury());
	Guarana* new_guarana11 = new Guarana(this, 14, 6, this->get_numer_tury());
	Guarana* new_guarana12 = new Guarana(this, 16, 9, this->get_numer_tury());
	Guarana* new_guarana13 = new Guarana(this, 19, 9, this->get_numer_tury());
	Guarana* new_guarana14 = new Guarana(this, 19, 16, this->get_numer_tury());

	WilczeJagody* new_wilcze_jagody = new WilczeJagody(this, 0, 3, this->get_numer_tury());
	WilczeJagody* new_wilcze_jagody1 = new WilczeJagody(this, 0, 10, this->get_numer_tury());
	WilczeJagody* new_wilcze_jagody2 = new WilczeJagody(this, 0, 15, this->get_numer_tury());
	WilczeJagody* new_wilcze_jagody3 = new WilczeJagody(this, 0, 17, this->get_numer_tury());
	WilczeJagody* new_wilcze_jagody4 = new WilczeJagody(this, 5, 0, this->get_numer_tury());
	WilczeJagody* new_wilcze_jagody5 = new WilczeJagody(this, 5, 11, this->get_numer_tury());
	WilczeJagody* new_wilcze_jagody6 = new WilczeJagody(this, 7, 13, this->get_numer_tury());
	WilczeJagody* new_wilcze_jagody7 = new WilczeJagody(this, 9, 18, this->get_numer_tury());
	WilczeJagody* new_wilcze_jagody8 = new WilczeJagody(this, 10, 9, this->get_numer_tury());
	WilczeJagody* new_wilcze_jagody9 = new WilczeJagody(this, 11, 15, this->get_numer_tury());
	WilczeJagody* new_wilcze_jagody10 = new WilczeJagody(this, 11, 18, this->get_numer_tury());
	WilczeJagody* new_wilcze_jagody11 = new WilczeJagody(this, 12, 13, this->get_numer_tury());
	WilczeJagody* new_wilcze_jagody12 = new WilczeJagody(this, 16, 12, this->get_numer_tury());
	WilczeJagody* new_wilcze_jagody13 = new WilczeJagody(this, 17, 18, this->get_numer_tury());
	WilczeJagody* new_wilcze_jagody14 = new WilczeJagody(this, 18, 17, this->get_numer_tury());

	BarszczSosnowskiego* new_barszcz_sosnowskiego = new BarszczSosnowskiego(this, 0, 0, this->get_numer_tury());
	BarszczSosnowskiego* new_barszcz_sosnowskiego1 = new BarszczSosnowskiego(this, 2, 1, this->get_numer_tury());
	BarszczSosnowskiego* new_barszcz_sosnowskiego2 = new BarszczSosnowskiego(this, 4, 5, this->get_numer_tury());
	BarszczSosnowskiego* new_barszcz_sosnowskiego3 = new BarszczSosnowskiego(this, 4, 8, this->get_numer_tury());
	BarszczSosnowskiego* new_barszcz_sosnowskiego4 = new BarszczSosnowskiego(this, 4, 13, this->get_numer_tury());
	BarszczSosnowskiego* new_barszcz_sosnowskiego5 = new BarszczSosnowskiego(this, 4, 18, this->get_numer_tury());
	BarszczSosnowskiego* new_barszcz_sosnowskiego6 = new BarszczSosnowskiego(this, 6, 16, this->get_numer_tury());
	BarszczSosnowskiego* new_barszcz_sosnowskiego7 = new BarszczSosnowskiego(this, 10, 18, this->get_numer_tury());
	BarszczSosnowskiego* new_barszcz_sosnowskiego8 = new BarszczSosnowskiego(this, 12, 17, this->get_numer_tury());
	BarszczSosnowskiego* new_barszcz_sosnowskiego9 = new BarszczSosnowskiego(this, 13, 8, this->get_numer_tury());
	BarszczSosnowskiego* new_barszcz_sosnowskiego10 = new BarszczSosnowskiego(this, 14, 18, this->get_numer_tury());
	BarszczSosnowskiego* new_barszcz_sosnowskiego11 = new BarszczSosnowskiego(this, 14, 19, this->get_numer_tury());
	BarszczSosnowskiego* new_barszcz_sosnowskiego12 = new BarszczSosnowskiego(this, 15, 13, this->get_numer_tury());
	BarszczSosnowskiego* new_barszcz_sosnowskiego14 = new BarszczSosnowskiego(this, 19, 1, this->get_numer_tury());
	BarszczSosnowskiego* new_barszcz_sosnowskiego13 = new BarszczSosnowskiego(this, 19, 8, this->get_numer_tury());

	lista_organizmów.push_back(czlowiek);

	//lista_organizmów.push_back(new_trawa);
	//lista_organizmów.push_back(new_trawa1);
	//lista_organizmów.push_back(new_trawa2);
	//lista_organizmów.push_back(new_trawa3);
	lista_organizmów.push_back(new_trawa4);
	lista_organizmów.push_back(new_trawa5);
	lista_organizmów.push_back(new_trawa6);
	lista_organizmów.push_back(new_trawa7);
	lista_organizmów.push_back(new_trawa8);
	lista_organizmów.push_back(new_trawa9);
	lista_organizmów.push_back(new_trawa10);
	lista_organizmów.push_back(new_trawa11);
	lista_organizmów.push_back(new_trawa12);
	lista_organizmów.push_back(new_trawa13);
	lista_organizmów.push_back(new_trawa14);

	lista_organizmów.push_back(new_mlecz);
	lista_organizmów.push_back(new_mlecz1);
	lista_organizmów.push_back(new_mlecz2);
	lista_organizmów.push_back(new_mlecz3);
	lista_organizmów.push_back(new_mlecz4);
	lista_organizmów.push_back(new_mlecz5);
	lista_organizmów.push_back(new_mlecz6);
	lista_organizmów.push_back(new_mlecz7);
	lista_organizmów.push_back(new_mlecz8);
	lista_organizmów.push_back(new_mlecz9);
	lista_organizmów.push_back(new_mlecz10);
	//lista_organizmów.push_back(new_mlecz11);
	//lista_organizmów.push_back(new_mlecz12);
	//lista_organizmów.push_back(new_mlecz13);
	//lista_organizmów.push_back(new_mlecz14);

	//lista_organizmów.push_back(new_guarana);
	//lista_organizmów.push_back(new_guarana1);
	//lista_organizmów.push_back(new_guarana2);
	//lista_organizmów.push_back(new_guarana3);
	lista_organizmów.push_back(new_guarana4);
	lista_organizmów.push_back(new_guarana5);
	lista_organizmów.push_back(new_guarana6);
	lista_organizmów.push_back(new_guarana7);
	lista_organizmów.push_back(new_guarana8);
	lista_organizmów.push_back(new_guarana9);
	lista_organizmów.push_back(new_guarana10);
	lista_organizmów.push_back(new_guarana11);
	lista_organizmów.push_back(new_guarana12);
	lista_organizmów.push_back(new_guarana13);
	lista_organizmów.push_back(new_guarana14);

	lista_organizmów.push_back(new_wilcze_jagody);
	lista_organizmów.push_back(new_wilcze_jagody1);
	lista_organizmów.push_back(new_wilcze_jagody2);
	lista_organizmów.push_back(new_wilcze_jagody3);
	lista_organizmów.push_back(new_wilcze_jagody4);
	lista_organizmów.push_back(new_wilcze_jagody5);
	lista_organizmów.push_back(new_wilcze_jagody6);
	lista_organizmów.push_back(new_wilcze_jagody7);
	lista_organizmów.push_back(new_wilcze_jagody8);
	lista_organizmów.push_back(new_wilcze_jagody9);
	lista_organizmów.push_back(new_wilcze_jagody10);
	//lista_organizmów.push_back(new_wilcze_jagody11);
	//lista_organizmów.push_back(new_wilcze_jagody12);
	//lista_organizmów.push_back(new_wilcze_jagody13);
	//lista_organizmów.push_back(new_wilcze_jagody14);

	//lista_organizmów.push_back(new_barszcz_sosnowskiego);
	//lista_organizmów.push_back(new_barszcz_sosnowskiego1);
	//lista_organizmów.push_back(new_barszcz_sosnowskiego2);
	//lista_organizmów.push_back(new_barszcz_sosnowskiego3);
	lista_organizmów.push_back(new_barszcz_sosnowskiego4);
	lista_organizmów.push_back(new_barszcz_sosnowskiego5);
	lista_organizmów.push_back(new_barszcz_sosnowskiego6);
	lista_organizmów.push_back(new_barszcz_sosnowskiego7);
	lista_organizmów.push_back(new_barszcz_sosnowskiego8);
	lista_organizmów.push_back(new_barszcz_sosnowskiego9);
	lista_organizmów.push_back(new_barszcz_sosnowskiego10);
	lista_organizmów.push_back(new_barszcz_sosnowskiego11);
	lista_organizmów.push_back(new_barszcz_sosnowskiego12);
	lista_organizmów.push_back(new_barszcz_sosnowskiego13);
	lista_organizmów.push_back(new_barszcz_sosnowskiego14);

	lista_organizmów.push_back(new_owca);
	lista_organizmów.push_back(new_owca1);
	lista_organizmów.push_back(new_owca2);
	lista_organizmów.push_back(new_owca3);
	lista_organizmów.push_back(new_owca4);
	lista_organizmów.push_back(new_owca5);
	lista_organizmów.push_back(new_owca6);
	lista_organizmów.push_back(new_owca7);
	lista_organizmów.push_back(new_owca8);
	lista_organizmów.push_back(new_owca9);
	lista_organizmów.push_back(new_owca10);
	//lista_organizmów.push_back(new_owca11);
	//lista_organizmów.push_back(new_owca12);
	//lista_organizmów.push_back(new_owca13);
	//lista_organizmów.push_back(new_owca14);

	//lista_organizmów.push_back(new_wilk);
	//lista_organizmów.push_back(new_wilk1);
	//lista_organizmów.push_back(new_wilk2);
	//lista_organizmów.push_back(new_wilk3);
	lista_organizmów.push_back(new_wilk4);
	lista_organizmów.push_back(new_wilk5);
	lista_organizmów.push_back(new_wilk6);
	lista_organizmów.push_back(new_wilk7);
	lista_organizmów.push_back(new_wilk8);
	lista_organizmów.push_back(new_wilk9);
	lista_organizmów.push_back(new_wilk10);
	lista_organizmów.push_back(new_wilk11);
	lista_organizmów.push_back(new_wilk12);
	lista_organizmów.push_back(new_wilk13);
	lista_organizmów.push_back(new_wilk14);

	lista_organizmów.push_back(new_lis);
	lista_organizmów.push_back(new_lis1);
	lista_organizmów.push_back(new_lis2);
	lista_organizmów.push_back(new_lis3);
	lista_organizmów.push_back(new_lis4);
	lista_organizmów.push_back(new_lis5);
	lista_organizmów.push_back(new_lis6);
	lista_organizmów.push_back(new_lis7);
	lista_organizmów.push_back(new_lis8);
	lista_organizmów.push_back(new_lis9);
	lista_organizmów.push_back(new_lis10);
	//lista_organizmów.push_back(new_lis11);
	//lista_organizmów.push_back(new_lis12);
	//lista_organizmów.push_back(new_lis13);
	//lista_organizmów.push_back(new_lis14);

	//lista_organizmów.push_back(new_zolw);
	//lista_organizmów.push_back(new_zolw1);
	//lista_organizmów.push_back(new_zolw2);
	//lista_organizmów.push_back(new_zolw3);
	lista_organizmów.push_back(new_zolw4);
	lista_organizmów.push_back(new_zolw5);
	lista_organizmów.push_back(new_zolw6);
	lista_organizmów.push_back(new_zolw7);
	lista_organizmów.push_back(new_zolw8);
	lista_organizmów.push_back(new_zolw9);
	lista_organizmów.push_back(new_zolw10);
	lista_organizmów.push_back(new_zolw11);
	lista_organizmów.push_back(new_zolw12);
	lista_organizmów.push_back(new_zolw13);
	lista_organizmów.push_back(new_zolw14);

	lista_organizmów.push_back(new_antylopa);
	lista_organizmów.push_back(new_antylopa1);
	lista_organizmów.push_back(new_antylopa2);
	lista_organizmów.push_back(new_antylopa3);
	lista_organizmów.push_back(new_antylopa4);
	lista_organizmów.push_back(new_antylopa5);
	lista_organizmów.push_back(new_antylopa6);
	lista_organizmów.push_back(new_antylopa7);
	lista_organizmów.push_back(new_antylopa8);
	lista_organizmów.push_back(new_antylopa9);
	lista_organizmów.push_back(new_antylopa10);
	//lista_organizmów.push_back(new_antylopa11);
	//lista_organizmów.push_back(new_antylopa12);
	//lista_organizmów.push_back(new_antylopa13);
	//lista_organizmów.push_back(new_antylopa14);

	Sleep(1000);
}