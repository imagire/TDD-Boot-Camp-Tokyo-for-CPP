#include "path.h"

void Path::AddReach(const std::string &first, const std::string &second)
{
	reach_.push_back(std::make_pair(first, second));
	reach_.push_back(std::make_pair(second, first));
}

bool Path::IsArrival(const std::string &from, const std::string &to, Root &result) const
{
	// ŒŸõ
	for (Reach::const_iterator it = reach_.begin(); it != reach_.end(); ++it) {
		if (it->first == from) {
			if (it->second == to) {
				Root ret;
				ret.push_back(from);
				ret.push_back(to);
				result = ret;
				return true;
			}
			else if (IsConnected(it->second, to)) {
				Root ret;
				ret.push_back(it->first);
				ret.push_back(it->second);
				ret.push_back(to);
				result = ret;
				return true;
			}
		}
	}
	return false;
}

bool Path::IsConnected(const std::string &from, const std::string &to) const
{
	// Ú‘±
	for (Reach::const_iterator it = reach_.begin(); it != reach_.end(); ++it) {
		if (it->first == from && it->second == to) {
			return true;
		}
	}
}
