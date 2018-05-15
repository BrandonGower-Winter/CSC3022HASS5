#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#define private public //Done for the sole purpose of testing private members and to validate functions
#include "../include/Music.h"

using namespace GWRBRA001;

TEST_CASE( "Music Initialization", "[GWRBRA001::Music]")
{
  SECTION("Default Constructor")
  {
    Music<int> music;
    REQUIRE(music.buffer.size() == 0);
  }
  SECTION("Copy Constructor")
  {
    Music<int> music;

    music.buffer.push_back(1);
    music.buffer.push_back(2);
    music.buffer.push_back(3);

    REQUIRE(music.buffer.size() == 3);
    REQUIRE(music.buffer[0] == 1);
    REQUIRE(music.buffer[1] == 2);
    REQUIRE(music.buffer[2] == 3);

    Music<int> musicCopy(music);

    REQUIRE(musicCopy.buffer.size() == 3);
    REQUIRE(musicCopy.buffer[0] == 1);
    REQUIRE(musicCopy.buffer[1] == 2);
    REQUIRE(musicCopy.buffer[2] == 3);

  }
  SECTION("Move Constructor")
  {
    Music<int> music;

    music.buffer.push_back(1);
    music.buffer.push_back(2);
    music.buffer.push_back(3);

    REQUIRE(music.buffer.size() == 3);
    REQUIRE(music.buffer[0] == 1);
    REQUIRE(music.buffer[1] == 2);
    REQUIRE(music.buffer[2] == 3);

    Music<int> musicMove(std::move(music));

    REQUIRE(musicMove.buffer.size() == 3);
    REQUIRE(music.buffer.size() == 0);
    REQUIRE(musicMove.buffer[0] == 1);
    REQUIRE(musicMove.buffer[1] == 2);
    REQUIRE(musicMove.buffer[2] == 3);
  }
}
TEST_CASE( "Music Operators", "[GWRBRA001::Music]")
{
  SECTION("Copy Assignment")
  {
    Music<int> music;

    music.buffer.push_back(1);
    music.buffer.push_back(2);
    music.buffer.push_back(3);

    REQUIRE(music.buffer.size() == 3);
    REQUIRE(music.buffer[0] == 1);
    REQUIRE(music.buffer[1] == 2);
    REQUIRE(music.buffer[2] == 3);

    Music<int> musicCopy = music;

    REQUIRE(musicCopy.buffer.size() == 3);
    REQUIRE(musicCopy.buffer[0] == 1);
    REQUIRE(musicCopy.buffer[1] == 2);
    REQUIRE(musicCopy.buffer[2] == 3);
  }

  SECTION("Move Assignment")
  {
    Music<int> music;

    music.buffer.push_back(1);
    music.buffer.push_back(2);
    music.buffer.push_back(3);

    REQUIRE(music.buffer.size() == 3);
    REQUIRE(music.buffer[0] == 1);
    REQUIRE(music.buffer[1] == 2);
    REQUIRE(music.buffer[2] == 3);

    Music<int> musicMove = std::move(music);

    REQUIRE(musicMove.buffer.size() == 3);
    REQUIRE(music.buffer.size() == 0);
    REQUIRE(musicMove.buffer[0] == 1);
    REQUIRE(musicMove.buffer[1] == 2);
    REQUIRE(musicMove.buffer[2] == 3);
  }

  SECTION("Concatenation Assignment")
  {
    Music<int> music;

    music.buffer.push_back(1);
    music.buffer.push_back(2);
    music.buffer.push_back(3);

    REQUIRE(music.buffer.size() == 3);
    REQUIRE(music.buffer[0] == 1);
    REQUIRE(music.buffer[1] == 2);
    REQUIRE(music.buffer[2] == 3);

    Music<int> music2 = music;

    REQUIRE(music2.buffer.size() == 3);
    REQUIRE(music2.buffer[0] == 1);
    REQUIRE(music2.buffer[1] == 2);
    REQUIRE(music2.buffer[2] == 3);

    Music<int> musicConcat = music|music2;

    REQUIRE(musicConcat.buffer.size() == 6);
    REQUIRE(musicConcat.buffer[0] == 1);
    REQUIRE(musicConcat.buffer[1] == 2);
    REQUIRE(musicConcat.buffer[2] == 3);
    REQUIRE(musicConcat.buffer[3] == 1);
    REQUIRE(musicConcat.buffer[4] == 2);
    REQUIRE(musicConcat.buffer[5] == 3);

  }
}
