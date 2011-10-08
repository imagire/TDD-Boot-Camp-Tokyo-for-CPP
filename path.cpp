#include "path.h"

void Path::AddReach(const std::string &first, const std::string &second)
{
	reach_.push_back(std::make_pair(first, second));
	reach_.push_back(std::make_pair(second, first));
}

bool Path::IsArrival(const std::string &from, const std::string &to, Root &result)
{
	// ’¼’Ê
	for (Reach::iterator it = reach_.begin(); it != reach_.end(); ++it) {
		if (it->first == from && it->second == to) {
			Root ret;
			ret.push_back(it->first);
			ret.push_back(it->second);
			result = ret;
			return true;
		}
	}
	// Œo—R1‚Â‚Ìæ‚èŒp‚¬
	for (Reach::iterator it = reach_.begin(); it != reach_.end(); ++it) {
		if (it->first == from) {
			for (Reach::iterator it2 = reach_.begin(); it2 != reach_.end(); ++it2) {
				if (it2->first == it->second && it2->second == to) {
					Root ret;
					ret.push_back(it->first);
					ret.push_back(it->second);
					ret.push_back(it2->second);
					result = ret;
					return true;
				}
			}
		}
	}
	return false;
}