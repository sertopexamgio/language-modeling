/*-************************************************************************************************************
 *
 *	\brief	NGram class describes an ngram.
 *
 **************************************************************************************************************/

#include "lm/ngram.h"

NGram::NGram(uint n) : n_(n) {}

void NGram::add(std::string word)
{
  curr_ngram_.push_back(word);

  // pop front if needed
  if (curr_ngram_.size() > n_)
  {
    curr_ngram_.erase(curr_ngram_.begin());
  }

  if (curr_ngram_.size() == n_)
  {
    std::string ngram_str;
    for (auto word : curr_ngram_)
    {
      ngram_str = ngram_str + delim + word;
    }

    ngrams_.add(ngram_str);
  }
}

NGram NGram::getNMinusOne(void)
{
  NGram n_minus_one_gram(n_ - 1);

  std::vector<std::string> words = ngrams_.keys();
  std::vector<std::size_t> freq = ngrams_.frequencies();
  for (size_t i = 0; i < words.size(); ++i)
  {
    n_minus_one_gram.ngrams_.add(ignore_(words[i]), freq[i]);
  }

  return n_minus_one_gram;
}

size_t NGram::frequencyOf(std::string word) { return ngrams_.get(word); }

std::vector<size_t> NGram::countOfCounts(void)
{
  std::vector<size_t> frequencies = ngrams_.frequencies(), result;

  for (auto f : frequencies)
  {
    ++countcounts_[f];
  }

  for (auto count : countcounts_)
  {
    result.push_back(count.second);
  }

  return result;
}

float NGram::nO(std::string word)
{
  word = word + delim;
  auto words = ngrams_.keys();
  size_t count = 0;
  for (auto w : words)
  {
    if (w.find(word) == 0)
      count++;
  }

  return count;
}

float NGram::discount(void)
{
  auto counts = countOfCounts();
  size_t n1 = counts[0];
  size_t n2 = counts[1];
  return (float)n1 / (n1 + 2 * n2);
}

std::string NGram::out(void) { return ngrams_.out(); }

std::string NGram::mostFrequent(size_t n)
{
  return ngrams_.mostFrequentWords(n);
}

void NGram::analyse(std::string &sentence)
{
  pad_(sentence);

  std::istringstream string_stream(sentence);
  for (std::string word; string_stream >> word;)
  {
    NGram::add(word);
  }

  curr_ngram_.clear();
}

void NGram::pad_(std::string &sentence)
{
  sentence = start_ + delim + sentence + delim + end_;
}

std::string NGram::ignore_(std::string word, uint n)
{
  std::istringstream ss(word);
  std::string token, result;

  while (std::getline(ss, token, delim))
  {
    if (n > 0)
    {
      --n; // ignore n first words
      continue;
    }

    if (token.empty())
      continue;

    result = result + delim + token;
  }

  return result;
}
