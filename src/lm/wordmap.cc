/*-************************************************************************************************************
 *
 *	\brief	WordMap class maps words to frequencies.
 *
 **************************************************************************************************************/
#include <set>
#include <vector>

#include "lm/wordmap.h"

void WordMap::add(std::string word, size_t n)
{
  word_frequencies_[ltrim(rtrim(word))] += n;
}

std::string WordMap::out(void)
{
  std::stringstream result;
  for (auto word : word_frequencies_)
  {
    result << word.first << delim << word.second << "\n";
  }
  return result.str();
}

std::vector<size_t> WordMap::frequencies(void)
{
  std::vector<size_t> res;
  for (auto word : word_frequencies_)
  {
    res.push_back(word.second);
  }

  return res;
}

size_t WordMap::get(std::string word)
{
  std::string s = ltrim(rtrim(word));
  size_t res = word_frequencies_[s];
  if (res == 0)
  {
    word_frequencies_.erase(s);
  }

  return res;
}

std::vector<std::string> WordMap::keys(void)
{
  std::vector<std::string> res;
  for (auto word : word_frequencies_)
  {
    res.push_back(word.first);
  }
  return res;
}

std::string WordMap::mostFrequentWords(size_t n)
{
  std::set<std::pair<std::string, size_t>,
           std::function<bool(std::pair<std::string, size_t>,
                              std::pair<std::string, size_t>)>>
      sortedWordMap(word_frequencies_.begin(), word_frequencies_.end(),
                    [](std::pair<std::string, size_t> elem1,
                       std::pair<std::string, size_t> elem2) {
                      return elem1.second > elem2.second;
                    });

  size_t i = 0;
  std::stringstream result;

  for (std::pair<std::string, size_t> element : sortedWordMap)
  {
    result << ++i << ") " << element.first << delim << element.second
           << std::endl;

    if (i >= n)
    {
      break;
    }
  }

  return result.str();
}

std::string &WordMap::ltrim(std::string &str)
{
  auto it2 = std::find_if(str.begin(), str.end(), [](char ch) {
    return !std::isspace<char>(ch, std::locale::classic());
  });
  str.erase(str.begin(), it2);
  return str;
}

std::string &WordMap::rtrim(std::string &str)
{
  auto it1 = std::find_if(str.rbegin(), str.rend(), [](char ch) {
    return !std::isspace<char>(ch, std::locale::classic());
  });
  str.erase(it1.base(), str.end());
  return str;
}