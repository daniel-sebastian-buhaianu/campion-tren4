#include <fstream>
#define NUMARUL_MAXIM_DE_TRENURI 100
#define NUMARUL_DE_LINII 2
using namespace std;
struct Interval
{
    int timpSosire, timpPlecare;
};
struct Linie
{
    int nrTrenuri;
    Interval tren[NUMARUL_MAXIM_DE_TRENURI];
};
bool vadTrenulCareSoseste(int, int, Linie*);
bool toateLiniileSuntLibere(int, Linie*);
void actualizeazaLinia(Linie &, int, int);
int main()
{
    Linie L[NUMARUL_DE_LINII];
    for (int i = 0; i < NUMARUL_DE_LINII; i++)
    {
        L[i].nrTrenuri = 0;
    }
    ifstream citeste("tren4.in");
    int nrTrenuri;
    citeste >> nrTrenuri;
    int timpPlecareUltimulTren = 0;
    int nrTrenuriVazute = 0;
    int durataMaximaFaraTrenuri = 0;
    int nrMaximTrenuriPeAceeasiLinie = 0;
    while (nrTrenuri > 0)
    {
        int nrLinie,
            oraSosire,
            minutSosire,
            minuteDeStationare;
        citeste >> nrLinie;
        nrLinie--; // retin liniile de la indicele 0
        citeste >> oraSosire >> minutSosire;
        citeste >> minuteDeStationare;
        int timpSosireInMinute = oraSosire*60
            + minutSosire;
        int timpPlecareInMinute = timpSosireInMinute
            + minuteDeStationare;
        if (vadTrenulCareSoseste(
                    timpSosireInMinute,
                    timpPlecareInMinute,
                    L))
        {
            nrTrenuriVazute++;
        }
        if (toateLiniileSuntLibere(timpSosireInMinute, L)
                && timpPlecareUltimulTren != 0)
        {
            int minuteFaraTrenuri = timpSosireInMinute
                - timpPlecareUltimulTren
                - 1;
            if (minuteFaraTrenuri
                    > durataMaximaFaraTrenuri)
            {
                durataMaximaFaraTrenuri = minuteFaraTrenuri;
            }
        }
        if (timpPlecareInMinute > timpPlecareUltimulTren)
        {
            timpPlecareUltimulTren = timpPlecareInMinute;
        }
        actualizeazaLinia(
                L[nrLinie],
                timpSosireInMinute,
                timpPlecareInMinute);
        if (L[nrLinie].nrTrenuri
                > nrMaximTrenuriPeAceeasiLinie)
        {
            nrMaximTrenuriPeAceeasiLinie = L[nrLinie].nrTrenuri;
        }
        nrTrenuri--;
    }
    citeste.close();
    ofstream scrie("tren4.out");
    scrie << nrMaximTrenuriPeAceeasiLinie << ' ';
    scrie << nrTrenuriVazute << ' ';
    scrie << durataMaximaFaraTrenuri;
    scrie.close();
    return 0;

}
bool esteLiniaLiberaLaTimpulSosirii(
        Linie L,
        int timpSosire
        )
{
    int nrTrenuri = L.nrTrenuri;
    if (nrTrenuri == 0)
    {
        return 1;
    }
    return L.tren[nrTrenuri-1].timpPlecare < timpSosire;
}
bool toateLiniileSuntLibere(
        int timpSosire,
        Linie L[]
        )
{
    for (int i = 0; i < NUMARUL_DE_LINII; i++)
    {
        if (!esteLiniaLiberaLaTimpulSosirii(
                    L[i],
                    timpSosire)
           )
        {
            return 0;
        }
    } 
    return 1;
}
bool devineLiniaLiberaPanaLaTimpulPlecarii(Linie L,
        int timpPlecare)
{
    int nrTrenuri = L.nrTrenuri;
    if (nrTrenuri == 0)
    {
        return 1;
    }
    return L.tren[nrTrenuri-1].timpPlecare < timpPlecare;
}
bool vadTrenulCareSoseste(int timpSosire, int timpPlecare,
        Linie L[])
{
    if (esteLiniaLiberaLaTimpulSosirii(L[0],
                timpSosire))
    {
        return 1;
    }
    if (devineLiniaLiberaPanaLaTimpulPlecarii(L[0],
                timpPlecare))
    {
        return 1;
    }
    return 0;
}
void actualizeazaLinia(Linie & L, int timpSosireInMinute,
        int timpPlecareInMinute)
{
    int nrTrenuri = L.nrTrenuri;
    L.tren[nrTrenuri].timpSosire = timpSosireInMinute;
    L.tren[nrTrenuri].timpPlecare = timpPlecareInMinute;
    L.nrTrenuri++;
}
