#include "Train.h"
#include <iterator>
#include <algorithm>
using namespace std;

bool cango(TRAIN_STATION start, TRAIN_STATION end)
{

	if(start == OMIYA)
	{
		if((end == YOKOHAMA) || (end == TOKYO))
		{
			return true;
		}
	}

	if(start == TOKYO)
	{
		if((end == OMIYA)||(end == YOKOHAMA))
		{
			return true;
		}
	}


	if(start == YOKOHAMA)
	{
		if((end == OMIYA)||(end == TOKYO))
		{
			return true;
		}
	}

	return false;
}

void Station::addStation(Station *to) {
    myTo.push_back(to);
}

bool Station::canGo(Station &to, vector<Station> &stopped){
    if (myName == to.myName) {
        return true;
    }
    
    for (vector<Station>::iterator it = stopped.begin(); it != stopped.end(); it++) {
        if (myName == it->myName) {
            return false;
        }
    }
    
    bool retVal = false;
    for (vector<Station*>::iterator it = myTo.begin(); it != myTo.end(); it++) {
        vector<Station> copy_stopped(stopped);
        copy_stopped.push_back(myName);
        retVal = (*it)->canGo(to, copy_stopped);
        
        if (retVal == true) {
            stopped.clear();
            copy(copy_stopped.begin(), copy_stopped.end(), back_inserter( stopped ) );
            break;
        }
    }
    
    return retVal;
}

