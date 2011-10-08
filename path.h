#pragma once

#include <vector>
#include <map>
#include <string>

class Path {
public:
	typedef std::vector<std::string> Root;

	void AddReach(const std::string &first, const std::string &second);
	bool IsArrival(const std::string &from, const std::string &to, Root &result) const;
private:
	bool IsConnected(const std::string &from, const std::string &to) const;
	typedef std::vector<std::pair<std::string, std::string> > Reach;
	Reach reach_;
}; 