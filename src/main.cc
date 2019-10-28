#include "lm/corpus.h"

int main(int argc, char **argv)
{

  std::string data_file = "../../data/lm/test.corpus";
  std::string vocabulary_file = "../../data/lm/vocabulary";
  std::string report_file = "../../reports/answers.txt";
  std::string bigram_file = "../../reports/bigram.txt";
  std::string unigram_file = "../../reports/unigram.txt";

  Corpus corpus(data_file, vocabulary_file);

  corpus.exercise1(report_file);
  corpus.exercise2(report_file);
  corpus.exercise3(bigram_file, unigram_file);
  corpus.exercise4(report_file);
  corpus.exercise5(report_file);

  return 0;
}
