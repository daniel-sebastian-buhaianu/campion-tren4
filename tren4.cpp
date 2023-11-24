#include <fstream>
#include <cstring>
#define ORE_PE_ZI 24
#define MINUTE_PE_ORA 60
#define MINUTE_PE_ZI ORE_PE_ZI*MINUTE_PE_ORA
#define NUMAR_MAXIM_DE_TRENURI 100
using namespace std;
int main()
{
	int trenVizibilLaMinutul[MINUTE_PE_ZI],
	    nrTrenuri,
	    nrTren,
	    timpInceperePerioadaStudiu = 0,
	    timpIncheierePerioadaStudiu = 0,
	    minut,
	    nrTrenuriLiniaUnu = 0,
	    nrTrenuriLiniaDoi = 0;
	bool aFostVizibilTrenul[NUMAR_MAXIM_DE_TRENURI+1];
	// initializez vectorii cu 0
	memset(trenVizibilLaMinutul, 0, sizeof(trenVizibilLaMinutul));
	memset(aFostVizibilTrenul, 0, sizeof(aFostVizibilTrenul));
	// declar fisier citire
	ifstream citeste("tren4.in");
	citeste >> nrTrenuri;
	for (nrTren = 1; nrTren <= nrTrenuri; nrTren++)
	{
		int nrLinie,
		    oraSosire,
		    minutSosire,
		    timpStationareInMinute;
		citeste >> nrLinie
			>> oraSosire
			>> minutSosire
			>> timpStationareInMinute;
		int timpSosireInMinute = oraSosire*MINUTE_PE_ORA
		                         + minutSosire;
		int timpPlecareInMinute = timpSosireInMinute
		                          + timpStationareInMinute;
		if (nrTren == 1)
		{
			timpInceperePerioadaStudiu = timpSosireInMinute;
			timpIncheierePerioadaStudiu = timpPlecareInMinute;
		}
		if (timpIncheierePerioadaStudiu < timpPlecareInMinute)
		{
			timpIncheierePerioadaStudiu = timpPlecareInMinute;
		}
		for (minut = timpSosireInMinute;
		     minut <= timpPlecareInMinute; minut++)
		{
			if (nrLinie == 1
			    || trenVizibilLaMinutul[minut] == 0)
			{
				trenVizibilLaMinutul[minut] = nrTren;
			}
		}
		if (nrLinie == 1)
		{
			nrTrenuriLiniaUnu++;
		}
		else
		{
			nrTrenuriLiniaDoi++;
		}
	}
	citeste.close();
	int nrMaximTrenuriCareAuStationatPeAceeasiLinie =
		nrTrenuriLiniaUnu > nrTrenuriLiniaDoi
		? nrTrenuriLiniaUnu : nrTrenuriLiniaDoi;
	int minuteFaraTren = 0;
	int nrMaximMinuteFaraTren = 0;
	for (minut = timpInceperePerioadaStudiu;
	     minut <= timpIncheierePerioadaStudiu; minut++)
	{
		nrTren = trenVizibilLaMinutul[minut];
		if (nrTren > 0)
		{
			aFostVizibilTrenul[nrTren] = 1;
			if (minuteFaraTren > nrMaximMinuteFaraTren)
			{
				nrMaximMinuteFaraTren = minuteFaraTren;
			}
			minuteFaraTren = 0;
		}
		else
		{
			minuteFaraTren++;
		}
	}
	int nrTrenuriVizibile = 0;
	for (nrTren = 1; nrTren <= nrTrenuri; nrTren++)
	{
		if (aFostVizibilTrenul[nrTren])
		{
			nrTrenuriVizibile++;
		}
	}
	// declar fisier scriere
	ofstream scrie("tren4.out");
	scrie << nrMaximTrenuriCareAuStationatPeAceeasiLinie << ' ';
	scrie << nrTrenuriVizibile << ' ';
	scrie << nrMaximMinuteFaraTren;
	scrie.close();
	return 0;
}
