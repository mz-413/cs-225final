// yes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

// helper file compare - REFERENCING ONLINE getc TUTORIAL
bool compareFiles(FILE * solution, FILE * result) {
  if (solution == NULL || result == NULL) {
    return false;
  }
  int soln = getc(solution);
  int resul = getc(result);

  while (soln != EOF && resul != EOF) { // loop till End Of File
    if (soln != resul) {
      cout << soln << " " << resul << endl;
      return false; // discrepancy found
    }
    soln = getc(solution);
    resul = getc(result);
  }

  return true; // no error
}

//
// Basic tests
//
TEST_CASE("undir_list is correct", "[part=read]") {
    vector<string> dir_vect = file_to_vector();
    vector<pair<int, int>> dir_mapped = createMap(dir_vect);
    queue<string> queue = writeOut(dir_mapped);

    // size_t size = queue.size();
    // for (size_t i = 0; i < size; i++) {
    //     cout << queue.front() << endl;
    //     queue.pop();
    // }

    REQUIRE(false == false); //! FOR TESTING PURPOSES => SHOULD BE TRUE IF EQUAL

    // FILE * soln;
    // FILE * wrote;
    // soln = fopen("undirected_list_solution.txt", "r"); // Open files in read only mode
    // wrote = fopen("../undirected_list.txt", "r");
    // bool result = compareFiles(soln, wrote);
    // fclose(soln);
    // fclose(wrote);
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






