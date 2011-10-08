#include <iostream>
#include <vector> 
#include <iterator> 
#include <boost/graph/adjacency_list.hpp> 
#include <boost/graph/breadth_first_search.hpp> 
#include <boost/graph/visitors.hpp> 
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/range/algorithm/find_if.hpp>
#include <boost/assign/list_of.hpp>

#include <gtest/gtest.h>

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS,
    boost::no_property, boost::property<boost::edge_weight_t, int> > Graph;
typedef std::pair<int, int>								Edge;
typedef boost::graph_traits<Graph>::vertex_descriptor	Vertex;

struct Station {
    enum enum_t {
        Omiya,
        Yokohama,
        Oshima,
        Tokyo,
		NishiKokubunji,
		N
    };
};

const int vertex_count = Station::N;

Graph	createGraph()
{
    std::vector<Edge> edges = boost::assign::list_of<Edge>
        (Station::Omiya, Station::Tokyo)
		(Station::Tokyo, Station::Yokohama)
		(Station::NishiKokubunji, Station::Yokohama)
		(Station::NishiKokubunji, Station::Omiya)
    ;

    std::vector<int> weights(vertex_count, 1);

    Graph g(edges.begin(), edges.end(), weights.begin(), vertex_count);

	return	g;
}


bool passable(const Graph &g, Station::enum_t from, Station::enum_t to)
{
	std::vector<Vertex> reachable; 
	boost::breadth_first_search(g, from, 
		boost::visitor( 
		  boost::make_bfs_visitor( 
			boost::write_property( 
			  boost::identity_property_map(), 
			  std::back_inserter(reachable), 
			  boost::on_discover_vertex())))); 
 
    return boost::find_if(reachable, [&](const Vertex& v) {
        return v == to;
    }) != reachable.end();
}

TEST(PassTest, Reachable)
{
	Graph	g = createGraph();
    EXPECT_TRUE(passable(g, Station::Omiya, Station::Yokohama));
	EXPECT_TRUE(passable(g, Station::Yokohama, Station::Tokyo));
    EXPECT_TRUE(passable(g, Station::Tokyo, Station::Omiya));

    EXPECT_TRUE(passable(g, Station::Yokohama, Station::NishiKokubunji));
    EXPECT_TRUE(passable(g, Station::Omiya, Station::NishiKokubunji));
    EXPECT_TRUE(passable(g, Station::Tokyo, Station::NishiKokubunji));

}

TEST(PassTest, ReverseReachable)
{
	Graph	g = createGraph();

	EXPECT_TRUE(passable(g, Station::Yokohama, Station::Omiya));
	EXPECT_TRUE(passable(g, Station::Tokyo, Station::Yokohama));
    EXPECT_TRUE(passable(g, Station::Omiya, Station::Tokyo));

    EXPECT_TRUE(passable(g, Station::NishiKokubunji, Station::Yokohama));
    EXPECT_TRUE(passable(g, Station::NishiKokubunji, Station::Omiya));
    EXPECT_TRUE(passable(g, Station::NishiKokubunji, Station::Tokyo));

}

TEST(PassTest, Unreachable)
{
	Graph	g = createGraph();

	EXPECT_FALSE(passable(g, Station::Yokohama, Station::Oshima));
    EXPECT_FALSE(passable(g, Station::Oshima, Station::Omiya));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
