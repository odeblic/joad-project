#include "generic_convolution.hpp"

#include <iostream>

void convolution(const std::string& s1_, const std::string& s2_, const int min_token_size)
{
// TODO use multithreading to make it faster

  int matching_token_count = 0;

  if(min_token_size < 1)
  {
    return;
  }

  const std::string& s1 = s1_.size() > s2_.size() ? s1_ : s2_;
  const std::string& s2 = s1_.size() > s2_.size() ? s2_ : s1_;

  std::cout << "s1 : \"" << s1 << "\"" << std::endl;
  std::cout << "s2 : \"" << s2 << "\"" << std::endl;

  std::string matching(s2.size(), ' ');

  for(size_t index1 = 0; index1 < s1.size() ; ++index1)
  {
    int matching_char_count_tmp = 0;
    int matching_char_count = 0;
    int matching_token_count_local = 0;

    for(size_t index2 = 0; index2 < s2.size() ; ++index2)
    {
      if(s1.at((index1 + index2) % s1.size()) == s2.at(index2))
      {
        ++matching_char_count;
        matching.at(index2) = 'x';
        ++matching_char_count_tmp;
      }
      else
      {
        matching.at(index2) = '.';
        matching_char_count_tmp = 0;
      }

      if(matching_char_count_tmp == min_token_size)
      {
        ++matching_token_count_local;
      }
    }

    if(matching_token_count_local > 0)
    {
      std::cout << s1 << std::endl;
      if(s2.size() + index1 <= s1.size())
      {
        const std::string space(index1, ' ');
        std::cout << space << s2 << std::endl;
        std::cout << space << matching;
      }
      else
      {
        const std::string space(s1.size() - s2.size(), ' ');
        std::cout << s2.substr(s1.size() - index1) << space << s2.substr(0, s1.size() - index1) << std::endl;
        std::cout << matching.substr(s1.size() - index1) << space << matching.substr(0, s1.size() - index1);
      }
      std::cout << '\t' << '[' << matching_char_count << ':' << matching_token_count_local << ']' << std::endl;
    }

    matching_token_count += matching_token_count_local;
  }

  std::cout << "I found " << matching_token_count << " tokens of at least " << min_token_size
    << " characters\nwhich are present in both strings s1 and s2." << std::endl;
}
