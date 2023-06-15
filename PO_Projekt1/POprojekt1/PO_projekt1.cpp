#include <iostream>
#include <list>
#include <Windows.h>
#include "Wszystkie_klasy.h"
using namespace std;

int main()
{
    Swiat stworzony_swiat;
    stworzony_swiat.rysuj_swiat();
    while (stworzony_swiat.get_czy_jest_koniec_gry() == false)
    {
        stworzony_swiat.wykonaj_ture();
        stworzony_swiat.rysuj_swiat();
        Sleep(200);
    }
}