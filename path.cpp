#include "path.h"
#include <algorithm>

void Path::AddReach(const std::string &first, const std::string &second)
{
	reach_.push_back(std::make_pair(first, second));
	reach_.push_back(std::make_pair(second, first));
}

bool Path::IsArrival(const std::string &from, const std::string &to, Root &result) const
{
	// ŒŸõ
	Root stations;
	stations.push_back(from);
	if(IsConnected(from, to, result, stations)){
		return true;
	}
	return false;
}

bool Path::IsConnected(const std::string &from, const std::string &to, Root &result, Root stations) const
{
	for (Reach::const_iterator it = reach_.begin(); it != reach_.end(); ++it) {
		if (it->first == from) {
			if(std::find(stations.begin(), stations.end(), it->second) == stations.end()){
				stations.push_back(it->second);
				if (it->second == to) {
					result = stations;
					return true;
				}
				else if (IsConnected(it->second, to, result, stations)) {
					return true;
				}
			}
		}
	}

	return false;
}