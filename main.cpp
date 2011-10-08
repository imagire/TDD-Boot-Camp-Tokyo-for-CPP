#include <gtest/gtest.h>
#include <map>
#include <vector>
int add(int x, int y)
{
    return x + y;
}

class math {
public:
	math(){}
	~math(){}

	int add(int a, int b){ return a+b; }
};

TEST(AddTest, Test1)
{
    EXPECT_EQ(2, add(1, 1));
}

TEST(AddTest, Test2)
{
    EXPECT_EQ(3, add(1, 2));
}


enum EKI {
	OOMIYA,YOKOHAMA,OOSHIMA,TOKYO,
	MINAMIURAWA,AKABANE,IKEBUKURO,TABATA,
	NISHIKOKUBUNJI,SHINJUKU,OCHANOMIZU,AKIHABARA,
	SHIBUYA,MUSASHIKOSUGI,KAWASAKI,
	EKI_MAX,
};

struct EkiInfo {
	EKI connect;
	int time;
};
struct Path{
	int time;
	std::vector<EKI> path;
};
class RosenInfo {
public:
	std::map<EKI,Path> graph;
	std::map<EKI,std::vector<EkiInfo> > info;
	bool search(EKI,EKI);
	int searchWithTime(EKI,EKI);
	void append(EKI,EKI);
	void append(EKI,EKI,int);
	void route(EKI form);
	void routeInit( EKI start);
	void init();
 };

bool RosenInfo::search(EKI from,EKI to){
	std::map<EKI,std::vector<EkiInfo> >::iterator end = info.end();
	std::vector<EkiInfo>::iterator it = info[from].begin();
	while( it != info[from].end() )
	{
		if (it->connect == to) return true;
		++it;
	}

	return false;
}
int RosenInfo::searchWithTime(EKI from,EKI to){
	std::map<EKI,std::vector<EkiInfo> >::iterator end = info.end();
	std::vector<EkiInfo>::iterator it = info[from].begin();
	while( it != info[from].end() )
	{
		if (it->connect == to) return it->time;
		++it;
	}

	return 0;
}

void RosenInfo::routeInit( EKI start){
	std::map<EKI,Path>::iterator it = graph.begin();
	while( it != graph.end() ){
		Path nil = {65535, new std::vector<EKI>};
		(it->second).path = nil;
		it++;
	}
	graph[start] = 0;
}

void RosenInfo::route(EKI from)
{
	std::map<EKI,std::vector<EkiInfo> >::iterator end = info.end();
	std::vector<EkiInfo>::iterator it = info[from].begin();
	while( it != info[from].end() )
	{
		if (graph[it->connect].time > graph[from].time+it->time) {
			graph[it->connect].time = graph[from].time+it->time;
			graph[it->connect].path.assign = new std::vector(graph[from].path);
			graph[it->connect].path.push_back(from);
			route(it->connect);
		}
		++it;
	}
}

void RosenInfo::append(EKI from, EKI to){
	EkiInfo eki1 = {to, 0};
	EkiInfo eki2 = {from, 0};

	info[from].push_back(eki1);
	info[to].push_back(eki2);
	
}

void RosenInfo::append(EKI from, EKI to, int time){
	EkiInfo eki1 = {to, time};
	EkiInfo eki2 = {from, time};

	info[from].push_back(eki1);
	info[to].push_back(eki2);

	graph[from] = 0;
	graph[to] = 0;
}
void RosenInfo::init(){
	append(YOKOHAMA,MUSASHIKOSUGI,23);
	append(YOKOHAMA,KAWASAKI,14);
	append(MUSASHIKOSUGI,NISHIKOKUBUNJI,50);
	append(MUSASHIKOSUGI,SHIBUYA,21);
	append(MUSASHIKOSUGI,KAWASAKI,19);
	append(KAWASAKI,TOKYO,24);
	append(TOKYO,SHIBUYA,25);
	append(TOKYO,AKIHABARA,6);
	append(TOKYO,OCHANOMIZU,10);
	append(SHIBUYA,SHINJUKU,10);
	append(NISHIKOKUBUNJI,SHINJUKU,32);
	append(SHINJUKU,OCHANOMIZU,16);
	append(OCHANOMIZU,AKIHABARA,8);
	append(AKIHABARA,TABATA,11);
	append(TABATA,IKEBUKURO,12);
	append(IKEBUKURO,SHINJUKU,11);
	append(TABATA,AKABANE,14);
	append(AKABANE,IKEBUKURO,15);
	append(AKABANE,MINAMIURAWA,16);
	append(NISHIKOKUBUNJI,MINAMIURAWA,36);
	append(OOMIYA,MINAMIURAWA,12);
}
TEST(Kadai1, OY) {
	RosenInfo data;
	data.append(OOMIYA,TOKYO);
	data.append(TOKYO,YOKOHAMA);

	EXPECT_EQ( true, data.search(OOMIYA,TOKYO));
	EXPECT_EQ( true, data.search(TOKYO,OOMIYA));
	EXPECT_EQ( true, data.search(TOKYO,YOKOHAMA));
	EXPECT_EQ( false, data.search(OOSHIMA,YOKOHAMA));
	EXPECT_EQ( false, data.search(OOMIYA,YOKOHAMA));
}
TEST(Kadai1,MANYSTATION){
	RosenInfo data;
	data.init();

	EXPECT_EQ( true, data.search(OOMIYA,MINAMIURAWA));
	EXPECT_EQ( true, data.search(MINAMIURAWA,NISHIKOKUBUNJI));
	EXPECT_EQ( true, data.search(NISHIKOKUBUNJI,MUSASHIKOSUGI));
	EXPECT_EQ( true, data.search(MUSASHIKOSUGI,YOKOHAMA));
	EXPECT_EQ( true, data.search(YOKOHAMA,KAWASAKI));
	EXPECT_EQ( true, data.search(KAWASAKI,TOKYO));
	EXPECT_EQ( true, data.search(TOKYO,AKIHABARA));
	EXPECT_EQ( true, data.search(AKIHABARA,TABATA));
	EXPECT_EQ( true, data.search(TABATA,AKABANE));
	EXPECT_EQ( true, data.search(AKABANE,MINAMIURAWA));
	EXPECT_EQ( true, data.search(MINAMIURAWA,OOMIYA));
	
	EXPECT_EQ(false, data.search(OOMIYA,AKABANE));
	EXPECT_EQ(false, data.search(SHINJUKU,TOKYO));
	EXPECT_EQ(false, data.search(YOKOHAMA,SHIBUYA));

	data.routeInit( OOMIYA);
	data.route(OOMIYA);
	EXPECT_EQ(48, data.graph[NISHIKOKUBUNJI]);
	EXPECT_NE(40, data.graph[NISHIKOKUBUNJI]);

	EXPECT_EQ( 12, data.searchWithTime(MINAMIURAWA,OOMIYA));

}
int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();

	return ret;
}
