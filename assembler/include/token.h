#if !defined(TOKEN_H)
#define TOKEN_H

#include <string>
#include <regex>
#include <map>
#include <climits>

enum token_type
{
    ident,
    label,
    number,
    colon,
    comma,
    right_brace,
    left_brace,
    plus,
    minus,
    divide,
    multiply,
    left_round_brace,
    right_round_brace,
    newline,
    ending
};

struct token
{
    std::string value;
    token_type type;
};

class symbol_provider
{
private:
    std::vector<token> tokens;
    int ptr = 0;
public:
    symbol_provider(std::vector<token> tokens): tokens(tokens){}
    token get_next(){return tokens[ptr++];};
};




class tokenizer
{
public:
    static std::vector<token> parse(std::string str)
    {
        std::map<std::string, token_type> patterns =
            {
                {"[A-Za-z_][A-Za-z_0-9]*", token_type::ident},
                {"[-]?[0-9]+[.]?[0-9]*", token_type::number},
                {"[:]", token_type::colon},
                {"[,]", token_type::comma},
                {"[[]",token_type::left_brace},
                {"[]]", token_type::right_brace},
                {"[+]", token_type::plus},
                {"[-]", token_type::minus},
                {"[/]", token_type::divide},
                {"[*]", token_type::multiply},
                {"[(]", token_type::left_round_brace},
                {"\n",  token_type::newline},
                {"[)]", token_type::right_round_brace},
            };

        std::vector<std::pair<int,token>> matches;

        for (auto pattern = patterns.begin(); pattern != patterns.end(); pattern++)
        {
            std::regex r(pattern->first, std::regex::extended );
            auto words_begin = std::sregex_iterator(str.begin(), str.end(), r);
            auto words_end = std::sregex_iterator();

            for (std::sregex_iterator it = words_begin; it != words_end; ++it)
                matches.push_back(std::make_pair(it->position(), token({it->str(), pattern->second})));
        }
        matches.push_back(std::make_pair(INT_MAX, token({"",token_type::ending})));
        sort(matches.begin(),matches.end(),
            [](std::pair<int,token> a, std::pair<int,token>b){return a.first < b.first;});
        std::vector<token> res;

        for(auto t : matches)
            res.push_back(t.second);
        return res;
    }
};

#endif // TOKEN_H
