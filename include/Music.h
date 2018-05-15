#ifndef _MUSIC
#define _MUSIC
#include <vector>
#include <utility>
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
  template <typename T>
  class Music
  {
    public:
      Music();
      ~Music();

      Music(const Music& copy);
      Music(Music && move);

      Music<T> & operator=(const Music & copy);
      Music<T> & operator=(const Music && move);

      Music<T> operator|(const Music & rhs);
      /*
      Music operator*(const std::pair<float,float> & frequency);

      Music operator+(const Music & rhs);

      Music operator^(const std::pair<int,int> & cut);
      */
    private:
      std::vector<T> buffer;
  };

  template<typename T>
  Music<T>::Music()
  {}
  template<typename T>
  Music<T>::~Music()
  {
    buffer.clear();
  }
  template<typename T>
  Music<T>::Music(const Music& copy)
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
  Music<T>::Music(Music && move)
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
  /*
  template<typename T>
  Music Music<T>::operator*(const std::pair<float,float> & frequency);
  template<typename T>
  Music Music<T>::operator+(const Music<T> & rhs);
  template<typename T>
  Music Music<T>::operator^(const std::pair<int,int> & cut);
*/
/*
  template<typename T>
  class Modifyer
  {
    virtual T applyModification(T & modifyer) = 0;
    virtual T applyAddition(T & lhs, T & rhs) = 0;
  };

  class ModifyerMono : Modifyer<float>
  {
    virtual float & applyModification(float & modifyer);
    virtual int & applyAddition(float & lhs, float & rhs);
  };
/*
  class ModifyerStereo : frequencyModifyer<std::pair<float,float>>
  {
    virtual std::pair<float,float> applyModification(std::pair<float,float> modifyer);
    virtual std::pair<int,int> applyAddition(std::pair<float,float> lhs,std::pair<float,float> rhs);
  };
*/

}
#endif
