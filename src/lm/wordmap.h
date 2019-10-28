/// \file wordmap.h

/*!************************************************************************************************************
 *
 *	\brief	WordMap class maps words to frequencies.
 *
 *	\class		WordMap
 *	\author		Serxhio, serxhio.rira@gmail.com
 *
 **************************************************************************************************************/

#ifndef WORDMAP_H_
#define WORDMAP_H_

#include <map>
#include <sstream>

const char delim = ' ';

class WordMap
{
public:
  /*!************************************************************************************************************
   *
   *	\brief	Constructor method of the class WordMap.
   *
   **************************************************************************************************************/
  WordMap(void){};

  /*!************************************************************************************************************
   *
   *	\brief	Destructor method of the class WordMap.
   *
   **************************************************************************************************************/
  virtual ~WordMap(void){};

  std::vector<std::string> keys(void);

  void add(std::string word, size_t n = 1);

  std::string out(void);

  std::string mostFrequentWords(size_t n);
  size_t get(std::string word);

  std::vector<size_t> frequencies(void);

private:
  std::map<std::string, size_t> word_frequencies_;

  std::string &ltrim(std::string &str);

  std::string &rtrim(std::string &str);
};

#endif /* WORDMAP_H_ */