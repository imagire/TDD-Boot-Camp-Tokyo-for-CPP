#ifndef Train
#define Train

#include <vector>
using namespace std;

enum TRAIN_STATION
{
	OMIYA = 0,
	YOKOHAMA,
	TOKYO,
	OSHIMA,
	MINAMI_URAWA,
	AKABANE,
	TABATA,
	IKEBUKURO,
	NISHI_KOKUBUNNJI,
	SHINJYUKU,
	OTYANOMIZU,
	AKIHABARA,
	SHIBUYA,
	MUSASIKOSUGI,
	KAWASAKI,
	MAX
};

bool cango(TRAIN_STATION start, TRAIN_STATION end);

#include <vector>

class Station {
    private:
        vector<Station*> myTo;
    public:
        TRAIN_STATION myName;
        Station(TRAIN_STATION name):myName(name) {}
        void addStation(Station *to);
        bool canGo(Station &to, vector<Station> &stopped);
};

#endif
