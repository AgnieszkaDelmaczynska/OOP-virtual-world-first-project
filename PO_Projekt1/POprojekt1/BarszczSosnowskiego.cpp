#include "BarszczSosnowskiego.h";
#include "Kolory.h"
#define BARSZCZ_SOSNOWSKIEGO_SILA 10
#define BARSZCZ_SOSNOWSKIEGO_INICJATYWA 0
using namespace std;

BarszczSosnowskiego::BarszczSosnowskiego(Swiat* swiat, int x, int y, int turaUrodzenia)
	:Roslina(swiat, TypOrganizmu::BARSZCZ_SOSNOWSKIEGO, BARSZCZ_SOSNOWSKIEGO_SILA, BARSZCZ_SOSNOWSKIEGO_INICJATYWA, x, y, turaUrodzenia)
{}

string BarszczSosnowskiego::TypOrganizmuToString()
{
	return "BarszczSosnowskiego";
}

void BarszczSosnowskiego::rysowanie()
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, RED);
	cout << "b";
	SetConsoleTextAttribute(hOut, WHITE);
}

//	Zwierze, ktore zjadlo te rośline, ginie
int BarszczSosnowskiego::kolizja(Organizm* organizm, std::list<Organizm*> lista_organizmów)
{
	if (this->TypOrganizmuToString() == organizm->TypOrganizmuToString())	// barszcz na barszcz
	{
		organizm->setX(organizm->getPoprzedniX());
		organizm->setY(organizm->getPoprzedniY());
		cout << "Rozmnazanie\n";
		//Sleep(1000);
		return (int)Skutek_kolizji::ROZMNAZANIE;
	}
	else// zwierze na barszcz
	{
		cout << organizm->TypOrganizmuToString() << " x[" << this->getX() << "] y[" << this->getY() << "] zjada barszcz sosnowskiego\n";
		//Sleep(1000);
		if (organizm->getSila() < this->getSila())	// zwierze ma mniejszą siłę niż barszcz
		{
			cout << "Umiera: " << organizm->TypOrganizmuToString() << endl;
			return (int)Skutek_kolizji::SMIERC_WYKONUJACEGO_AKCJE;
		}
		else
		{
			cout << "Umieraja: " << organizm->TypOrganizmuToString() << " i barszcz sosnowskiego\n";
			return (int)Skutek_kolizji::SMIERC_OBU;
		}
	}
}

//TODO	Zabija wszystkie zwierzęta w swoim sąsiedztwie
void BarszczSosnowskiego::akcja(std::list<Organizm*>& lista_organizmów)
{
	cout << TypOrganizmuToString() << " x[" << this->getX() << "] y[" << this->getY() << "]\n";
	//Sleep(1000);
	if ((this->getY() != 0) && (czy_moze_wykonac_ruch(this->getX(), this->getY() - 1, lista_organizmów) == true)) // góra
	{
		cout << "	zabije zwierze: z gory\n";
	}
	if ((this->getY() != WORLD_HEIGHT - 1) && (czy_moze_wykonac_ruch(this->getX(), this->getY() + 1, lista_organizmów) == true)) // dół
	{
		cout << "	zabije zwierze: z dolu\n";
	}
	if ((this->getX() != 0) && (czy_moze_wykonac_ruch(this->getX() - 1, this->getY(), lista_organizmów) == true)) // lewo
	{
		cout << "	zabije zwierze: z lewej\n";
	}
	if ((this->getX() != WORLD_WIDTH - 1) && (czy_moze_wykonac_ruch(this->getX() + 1, this->getY(), lista_organizmów) == true)) // prawo
	{
		cout << "	zabije zwierze: z prawej\n";
	}
	//Sleep(1000);
	cout << "Akcja rosliny: " << TypOrganizmuToString() << " x[" << this->getX() << "] y[" << this->getY() << "] sila[" << this->sila << "] inicjatywa[" << this->inicjatywa << "]\n";
	if (rand() % 100 < 100) Rozprzestrzenianie(lista_organizmów);
}

bool BarszczSosnowskiego::czy_moze_wykonac_ruch(int pos_x, int pos_y, std::list <Organizm*> lista_organizmów)
{
	bool czy_moze = false;
	for (Organizm* organizm : lista_organizmów)
	{
		if ((organizm->getX() == pos_x) && (organizm->getY() == pos_y) && (organizm->czy_zwierze()==true))
		{
			organizm->do_usuniecia = true;
			czy_moze = true;
			break;
		}
	}
	return czy_moze;
}