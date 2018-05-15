#ifndef _MUSIC
#define _MUSIC
#include <vector>
#include <utility>
#include <cstdint>
namespace GWRBRA001
{
  enum MusicOperation
  {
    ADD,
    CUT,
    RANGEADD,
    CONCATENATE,
    VOLUME,
    REVERSE,
    RMS,
    NORMALIZE,
    FADEIN,
    FADEOUT,
    NONE
  };
  enum BitCount
  {
    EIGHT_BIT,
    SIXTEEN_BIT
  };
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  template <typename T>
  class Music
  {
    public:
      Music();
      ~Music();
      Music(int bitCount) : bitCount(bitCount) {}
      Music(const Music<T> & copy);
      Music(Music<T> && move);

      Music<T> & operator=(const Music<T> & copy);
      Music<T> & operator=(const Music<T> && move);

      Music<T> operator|(const Music<T> & rhs);

      Music<T> operator*(const std::pair<float,float> & frequency);

      Music<T> operator+(const Music<T> & rhs);

      Music<T> operator^(const std::pair<int,int> & cut);

    private:
      std::vector<T> buffer;
      int bitCount;
  };

  template<typename T>
  Music<T>::Music() : bitCount(EIGHT_BIT)
  {}
  template<typename T>
  Music<T>::~Music()
  {
    buffer.clear();
  }
  template<typename T>
  Music<T>::Music(const Music<T> & copy) : bitCount(copy.bitCount)
  {
    if(buffer.size() != 0)
    {
      buffer.clear();
    }
    for(T element : copy.buffer)
    {
      T elementCopy = element; //Makes copy
      buffer.push_back(elementCopy);
    }
  }
  template<typename T>
  Music<T>::Music(Music<T> && move) : bitCount(move.bitCount)
  {
    if(buffer.size() != 0)
    {
      buffer.clear();
    }
    for(T element : move.buffer)
    {
      buffer.push_back(element);
    }
    move.buffer.clear();
  }
  template<typename T>
  Music<T> & Music<T>::operator=(const Music<T> & copy)
  {
    bitCount = copy.bitCount;
    if(buffer.size() != 0)
    {
      buffer.clear();
    }
    for(T element : copy.buffer)
    {
      T elementCopy = element; //Makes Copy
      buffer.push_back(elementCopy);
    }
    return *this;
  }
  template<typename T>
  Music<T> & Music<T>::operator=(const Music<T> && move)
  {
     bitCount = move.bitCount;
    if(buffer.size() != 0)
    {
      buffer.clear();
    }
    for(T element : move.buffer)
    {
      buffer.push_back(element);
    }
    move.buffer.clear();
    return *this;
  }
  template<typename T>
  Music<T> Music<T>::operator|(const Music<T> & rhs) //CONCATENATE
  {
    Music newClip;
    //First Clip
    for(T element : buffer)
    {
      newClip.buffer.push_back(element);
    }
    //Second Clip
    for(T element : rhs.buffer)
    {
      newClip.buffer.push_back(element);
    }
    return newClip;
  }

  //MONO Implementation
  template<>
  Music<int> Music<int>::operator*(const std::pair<float,float> & frequency)
  {
    Music<int> newClip = *this;
    for(int i = 0; i < newClip.buffer.size(); ++i)
    {
      newClip.buffer[i] = (int)((float)newClip.buffer[i] * std::get<0>(frequency));
    }
    return newClip;
  }

  //STERIO Implementation
  template<>
  Music<std::pair<int,int>> Music<std::pair<int,int>>::operator*(const std::pair<float,float> & frequency)
  {
    Music<std::pair<int,int>> newClip = *this;
    for(int i = 0; i < newClip.buffer.size(); ++i)
    {
      newClip.buffer[i].first = (int)((float)newClip.buffer[i].first * std::get<0>(frequency));
      newClip.buffer[i].second = (int)((float)newClip.buffer[i].second * std::get<1>(frequency));
    }
    return newClip;
  }

  //MONO Implementation
  template<>
  Music<int> Music<int>::operator+(const Music<int> & rhs)
  {
    Music<int> newClip = *this;
    for(int i = 0; i < newClip.buffer.size(); ++i)
    {
      newClip.buffer[i] = newClip.buffer[i] + rhs.buffer[i];
      switch(bitCount)
      {
        case EIGHT_BIT:
          if(newClip.buffer[i] > INT8_MAX)
          {
            newClip.buffer[i] = INT8_MAX;
          }
          break;
        case SIXTEEN_BIT:
          if(newClip.buffer[i] > INT16_MAX)
          {
            newClip.buffer[i] = INT16_MAX;
          }
          break;
      }
    }
    return newClip;
  }
  //STEREO Implementation
  template<>
  Music<std::pair<int,int>> Music<std::pair<int,int>>::operator+(const Music<std::pair<int,int>> & rhs)
  {
    Music<std::pair<int,int>> newClip = *this;
    for(int i = 0; i < newClip.buffer.size(); ++i)
    {
      newClip.buffer[i].first = newClip.buffer[i].first + rhs.buffer[i].first;
      newClip.buffer[i].second = newClip.buffer[i].second + rhs.buffer[i].second;
      switch(bitCount)
      {
        case EIGHT_BIT:
          if(newClip.buffer[i].first > INT8_MAX)
          {
            newClip.buffer[i].first = INT8_MAX;
          }
          else if(newClip.buffer[i].second > INT8_MAX)
          {
            newClip.buffer[i].second = INT8_MAX;
          }
          break;
        case SIXTEEN_BIT:
          if(newClip.buffer[i].first > INT16_MAX)
          {
            newClip.buffer[i].first = INT16_MAX;
          }
          else if(newClip.buffer[i].second > INT16_MAX)
          {
            newClip.buffer[i].second = INT16_MAX;
          }
          break;
      }
    }
    return newClip;
  }

  template<typename T>
  Music<T> Music<T>::operator^(const std::pair<int,int> & cut)
  {
    Music<T> newClip;
    for(int i = 0; i < buffer.size(); ++i)
    {
      if(i >= cut.first && i <= cut.second)
      {
        continue;
      }
      else
      {
        newClip.buffer.push_back(buffer[i]);
      }
    }
    return newClip;
  }

}
#endif
