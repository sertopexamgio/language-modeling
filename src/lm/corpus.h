/// \file corpus.h

/*!************************************************************************************************************
 *
 *	\brief	Corpus contains information of out data.
 *
 *	\class		Corpus
 *	\author		Serxhio, serxhio.rira@gmail.com
 *
 **************************************************************************************************************/

#ifndef CORPUS_H_
#define CORPUS_H_

#include <unordered_map>

#include "lm/ngram.h"
#include "lm/wordmap.h"

class Corpus
{
public:
  /*!************************************************************************************************************
   *
   *	\brief	Constructor method of the class Corpus.
   *
   **************************************************************************************************************/
  Corpus(std::string filepath, std::string vocabulary_path = "");

  /*!************************************************************************************************************
   *
   *	\brief	Destructor method of the class Corpus.
   *
   **************************************************************************************************************/
  virtual ~Corpus(void){};

  size_t words(void);

  size_t sentences(void);

  void exercise1(std::string filepath);

  void exercise2(std::string filepath);

  void exercise3(std::string bigram_path, std::string unigram_path);

  void exercise4(std::string filepath);

  void exercise5(std::string filepath);

  float avgSentenceLength(void);

  void wordFrequencies(std::string filepath);

  void sentenceLengths(std::string filepath);

  void countCounts(std::string filepath);

private:
  WordMap wordmap_;
  float uni_discount_, bi_discount_;
  NGram unigram_, bigram_, trigram_;
  std::unordered_map<size_t, size_t> sentence_lengths_;
  std::string filepath_, vocabulary_path_, vocabulary_;
  size_t n_words_, unknown_words_, n_sentences_, vocab_words_, used_vocab_;

  void analyse_(void);

  float probUni_(std::string w);

  float probBi_(std::string w, std::string v);

  bool isInVocabulary_(std::string word);

  float perplexity_(void);

  void loadVocab_(void);

  float oovRate_(void);
};

#endif /* CORPUS_H_ */