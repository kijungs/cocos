#include "base_struct.hpp"





#ifdef _TEST_

TEST_CASE( "Edge", "[BaseStruct]" ) 
{
	Edge test1;
    REQUIRE( test1.src == INVALID_VID );
    REQUIRE( test1.dst == INVALID_VID );

	Edge test2(1, 2);
	REQUIRE(test2.src == 1);
	REQUIRE(test2.dst == 2);
}

TEST_CASE("EdgeParse", "[BaseStruct]")
{
	EdgeParser parser("example_graph.txt");
	Edge edge;
	parser.getEdge(edge);
	REQUIRE(edge.src == 9203210);
	REQUIRE(edge.dst == 9801208);
	parser.getEdge(edge);
	REQUIRE(edge.src == 9203210);
	REQUIRE(edge.dst == 9801209);
	
	int cnt(2);
	while(parser.getEdge(edge))
	{
		cnt++;
	}
	REQUIRE(cnt == 346849);
}

#endif // _TEST_ 
