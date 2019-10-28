/*-************************************************************************************************************
 *
 *	\brief	Corpus contains information of out data.
 *
 **************************************************************************************************************/
#include <fstream>

#include "lm/ngram.h"
#include "corpus.h"

using namespace std;

Corpus::Corpus(string filepath, string vocabulary_path)
    : filepath_(filepath), vocabulary_path_(vocabulary_path), n_words_(0),
      unknown_words_(0), n_sentences_(0), used_vocab_(0)
{
  loadVocab_();

  analyse_();
}

size_t Corpus::words(void) { return n_words_; }

size_t Corpus::sentences(void) { return n_sentences_; }

float Corpus::avgSentenceLength(void)
{
  float sum = 0.0;
  for (auto sentence : sentence_lengths_)
  {
    sum += sentence.second;
  }
  return sum / sentences();
}

void Corpus::wordFrequencies(string filepath)
{
  ofstream file(filepath);

  file << wordmap_.out();

  file.close();
}

void Corpus::sentenceLengths(string filepath)
{
  ofstream file(filepath);

  for (auto sentence : sentence_lengths_)
  {
    file << sentence.first << " " << sentence.second << "\n";
  }

  file.close();
}

void Corpus::countCounts(string filepath)
{
  ofstream file(filepath);

  vector<size_t> vec = trigram_.countOfCounts();
  for (size_t i = 0; i < vec.size(); ++i)
  {
    file << i + 1 << " " << vec[i] << endl;
  }

  file.close();
}

void Corpus::exercise1(string filepath)
{
  ofstream file(filepath, ios_base::app);

  file << "***** Exercise 1 *****" << endl;
  file << "1a) Tokens: " << words() << endl;
  file << "1b) Sentences: " << sentences() << endl;
  file << "1c) Average sentence length: " << avgSentenceLength() << endl;
}

void Corpus::exercise2(string filepath)
{
  ofstream file(filepath, ios_base::app);

  file << "***** Exercise 2 *****" << endl;
  file << "2a) 10 most frequent words: " << endl
       << wordmap_.mostFrequentWords(10) << endl;
  file << "2b) 10 most frequent trigrams: " << endl
       << trigram_.mostFrequent(10) << endl;
  file << "2d) OOV Rate: " << oovRate_() << endl;
}

void Corpus::exercise3(string bigram_path, string unigram_path)
{
  ofstream bigram_file(bigram_path);
  // Create bigram from trigram
  NGram bigram = trigram_.getNMinusOne();
  bigram_file << bigram.out();

  ofstream unigram_file(unigram_path);
  // Create unigram from bigram
  NGram unigram = bigram.getNMinusOne();
  unigram_file << unigram.out();
}

void Corpus::exercise4(string filepath)
{
  ofstream file(filepath, ios_base::app);

  file << "***** Exercise 4 *****" << endl;
  file << "Bigram discount: " << bi_discount_ << std::endl;
  file << "Unigram discount: " << uni_discount_ << std::endl;
}

void Corpus::exercise5(string filepath)
{
  ofstream file(filepath, ios_base::app);

  file << "***** Exercise 5 *****" << endl;
  file << "Perplexity: " << perplexity_() << std::endl;
}

float Corpus::oovRate_(void) { return (float)unknown_words_ / n_words_; }

float Corpus::perplexity_(void)
{
  // open file
  ifstream infile(filepath_);
  float LL = 0.0;
  size_t counter = 0;

  // go through every sentence
  for (string sentence; getline(infile, sentence);)
  {
    std::string w, v;
    trigram_.analyse(sentence);

    istringstream string_stream(sentence);

    for (string w; string_stream >> w;)
    {

      if (!isInVocabulary_(w))
      {
        w = "<unk>";
      }

      if (!v.empty())
      {
        float prob = probBi_(w, v);

        if (prob > 0)
        {
          LL += std::logf(prob);
          counter++;
        }
      }

      v = w;
    }
  }

  return exp(-LL / counter);
}

float Corpus::probBi_(std::string w, std::string v)
{
  std::string vw = v + delim + w;
  float nO = bigram_.nO(v);
  float nvw = bigram_.frequencyOf(vw);
  float nv = unigram_.frequencyOf(v);
  float a = nvw > bi_discount_ ? (nvw - bi_discount_) / nv : 0;
  float b = probUni_(w) * bi_discount_ * (nO) / nv;

  return a + b;
}

float Corpus::probUni_(std::string w)
{
  size_t nw = unigram_.frequencyOf(w);
  float a = nw > uni_discount_ ? (nw - uni_discount_) / n_words_ : 0;
  float b = uni_discount_ * used_vocab_ / (n_words_ * vocab_words_);
  return a + b;
}

void Corpus::analyse_(void)
{
  // open file
  ifstream infile(filepath_);

  // construct bi- and unigram templates
  unigram_ = NGram(1);
  bigram_ = NGram(2);

  // go through every sentence
  for (string sentence; getline(infile, sentence); ++n_sentences_)
  {

    std::string sentence_cp = sentence;
    // build ngrams
    trigram_.analyse(sentence);
    bigram_.analyse(sentence_cp);
    unigram_.analyse(sentence_cp);

    int word_count = 0;
    istringstream string_stream(sentence);

    // go through every word of that sentence
    for (string word; string_stream >> word; ++word_count)
    {

      if (isInVocabulary_(word))
      {
        wordmap_.add(word);

        if (wordmap_.get(word) == 1)
        {
          ++used_vocab_;
        }
      }
      else
      {
        wordmap_.add("<unk>");
        ++unknown_words_;
      }
    }

    n_words_ += word_count;
    sentence_lengths_[n_sentences_] = word_count;
  }

  // store ngram discounts
  bi_discount_ = bigram_.discount();
  uni_discount_ = unigram_.discount();
}

bool Corpus::isInVocabulary_(string word)
{
  if (vocabulary_path_.empty())
  {
    return true;
  }

  return vocabulary_.find(word) != string::npos;
}

void Corpus::loadVocab_(void)
{
  // load vocabulary to memory
  if (!vocabulary_path_.empty())
  {
    ifstream infile(vocabulary_path_);
    vocab_words_ = 0;
    for (string sentence; getline(infile, sentence);)
    {
      vocabulary_ += sentence;
      istringstream string_stream(sentence);

      // count vocabulary words
      for (string word; string_stream >> word; ++vocab_words_)
      {
      }
    }
  }
}
