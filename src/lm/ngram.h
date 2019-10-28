/// \file ngram.h

/*!************************************************************************************************************
 *
 *	\brief	NGram class describes an ngram.
 *
 *	\class		ngram
 *	\author		Serxhio, serxhio.rira@gmail.com
 *
 **************************************************************************************************************/

#ifndef NGRAM_H_
#define NGRAM_H_

#include <vector>

#include "lm/wordmap.h"

class NGram : public WordMap
{
public:
  /*!************************************************************************************************************
   *
   *	\brief	Constructor method of the class NGram.
   *
   **************************************************************************************************************/
  NGram(uint n = 3);

  /*!************************************************************************************************************
   *
   *	\brief	Destructor method of the class NGram.
   *
   **************************************************************************************************************/
  virtual ~NGram(void){};

  void add(std::string word);

  void analyse(std::string &sentence);

  std::string mostFrequent(size_t n);

  std::string out(void);

  std::vector<size_t> countOfCounts(void);

  NGram getNMinusOne(void);

  float discount(void);

  size_t frequencyOf(std::string word);

  float nO(std::string word);

private:
  uint n_;
  WordMap ngrams_;
  std::string start_ = "<s>";
  std::string end_ = "</s>";
  std::map<size_t, size_t> countcounts_;
  std::vector<std::string> curr_ngram_;

  std::string ignore_(std::string word, uint n = 1);

  void pad_(std::string &sentence);
};

#endif /* NGRAM_H_ */