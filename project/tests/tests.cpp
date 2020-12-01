// yes

#include "../readFile.hpp"
#include "../catch/catch.hpp"

using namespace std;

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//////////////////////// Start of Tests ////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

// SAMPLE TEST_CASE:
// TEST_CASE("test_get_anagrams", "[weight=15]")
// {
//     AnagramDict d(words);
//     const set< string > canon = { "dog", "god" };
//     vector< string > result = d.get_anagrams("dog");
//     set<string> resultSet(result.begin(), result.end());
//     REQUIRE(canon == resultSet);
//     REQUIRE(d.get_anagrams("z").empty());
// }

//
// Basic tests
//

TEST_CASE("undir_list is correct", "[part=read]") {
    vector<string> dir_vect = file_to_vector();
    vector<pair<int, int>> dir_mapped = createMapDirected(dir_vect);
    vector<pair<int, int>> undir_mapped = createMapUndirected(dir_mapped);
    writeOut(undir_mapped);
    REQUIRE("../undirected_list.txt" == "undirected_list_solution.txt");
}

/**
TEST_CASE("Produces an output directed_list.txt file", "[weight=2]") {
  const std::string fileName = "tests/out_existanceTest.png";

  // Delete if tests/out_existanceTest exists... if so, delete it.
  if (fileExists(fileName)) { remove( fileName.c_str() ); }

  // Run program
  sketchify("tests/in_01.png", fileName);

  // Check for file existance
  REQUIRE( fileExists(fileName) == true );
  remove( fileName.c_str() );
}
*/






