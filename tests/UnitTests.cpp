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

  SECTION("Volume Factor Assignment")
  {
    SECTION("MONO Test")
    {
      Music<int> music;

      music.buffer.push_back(6);
      music.buffer.push_back(10);
      music.buffer.push_back(5);

      std::pair<float,float> volume(0.5,0.5);

      Music<int> musicVolume = music*volume;

      REQUIRE(musicVolume.buffer.size() == 3);
      REQUIRE(musicVolume.buffer[0] == 3);
      REQUIRE(musicVolume.buffer[1] == 5);
      REQUIRE(musicVolume.buffer[2] == 2);
    }
    SECTION("STEREO Test")
    {
      Music<std::pair<int,int>> music;

      music.buffer.push_back(std::make_pair(6,6));
      music.buffer.push_back(std::make_pair(10,10));
      music.buffer.push_back(std::make_pair(5,4));

      std::pair<float,float> volume(0.5,0.5);

      Music<std::pair<int,int>> musicVolume = music*volume;

      REQUIRE(musicVolume.buffer.size() == 3);
      REQUIRE(musicVolume.buffer[0].first == 3);
      REQUIRE(musicVolume.buffer[1].first == 5);
      REQUIRE(musicVolume.buffer[2].first == 2);
      REQUIRE(musicVolume.buffer[0].second == 3);
      REQUIRE(musicVolume.buffer[1].second == 5);
      REQUIRE(musicVolume.buffer[2].second == 2);
    }
  }

  SECTION("Addition Assignment")
  {
    SECTION("MONO TEST")
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

      Music<int> added = music + music2;

      REQUIRE(added.buffer.size() == 3);
      REQUIRE(added.buffer[0] == 2);
      REQUIRE(added.buffer[1] == 4);
      REQUIRE(added.buffer[2] == 6);
    }
    SECTION("STEREO TEST")
    {
      Music<std::pair<int,int>> music;

      music.buffer.push_back(std::make_pair(6,6));
      music.buffer.push_back(std::make_pair(10,10));
      music.buffer.push_back(std::make_pair(5,4));

      Music<std::pair<int,int>> music2 = music;

      Music<std::pair<int,int>> added = music + music2;

      REQUIRE(added.buffer.size() == 3);
      REQUIRE(added.buffer[0].first == 12);
      REQUIRE(added.buffer[1].first == 20);
      REQUIRE(added.buffer[2].first == 10);
      REQUIRE(added.buffer[0].second == 12);
      REQUIRE(added.buffer[1].second == 20);
      REQUIRE(added.buffer[2].second == 8);
    }
  }

  SECTION("Concatenation Assignment")
  {
    Music<int> music;

    music.buffer.push_back(1);
    music.buffer.push_back(2);
    music.buffer.push_back(3);
    music.buffer.push_back(4);
    music.buffer.push_back(5);
    music.buffer.push_back(6);

    Music<int> cutMusic = music^std::make_pair(3,5);

    REQUIRE(cutMusic.buffer.size() == 3);
    REQUIRE(cutMusic.buffer[0] == 1);
    REQUIRE(cutMusic.buffer[1] == 2);
    REQUIRE(cutMusic.buffer[2] == 3);

  }

}
