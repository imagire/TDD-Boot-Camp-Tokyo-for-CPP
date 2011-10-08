#include "Train.h"

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
