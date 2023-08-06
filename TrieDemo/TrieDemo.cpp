
#include <iostream>
#include <fstream>
#include "../Cpp/MyTrie.h"

using namespace ds;

std::string read_characters_file()
{
    std::ifstream file("characters.csv");
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void add_characters_to_trie(const std::string& characters_string, MyTrie& in_out_trie)
{
    auto left = characters_string.cbegin();
    for (auto right = characters_string.cbegin(); right != characters_string.cend(); ++right)
    {
        char c = (char)*right;
        if (c == ' ') continue;
        if (c != ',') continue;
        std::string word = std::string(left, right);
        in_out_trie.add_word(word);
        left = right;
        left++;
    }
}

int main()
{
    MyTrie my_trie;
    {
        std::string data = read_characters_file();
        add_characters_to_trie(data, my_trie);
    }

	std::string input;
    do
    {
        std::cout << "Start writing a name name of a league champ (before 2018): \n";
        std::cin >> input;
        size_t i = 0;
        auto iterator = my_trie.search_begin();
        bool error = false;
        while (i < input.size())
        {
            if(!iterator.next(input[i]))
            {
                std::cout << "couldn't find any words with prefix" << std::endl;
            	error = true;
                break;
            }
            ++i;
        }
        if (error) continue;
        
        std::cout << "\nSuggestions: \n";

    	auto suggestions = iterator.suggest_words(4);
        for(auto& suggestion : suggestions)
        {
            std::cout << suggestion << std::endl;
        }
        std::cout << std::endl;
    }
	while (input != "0");
}