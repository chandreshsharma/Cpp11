#include <iostream>
#include <regex>

#include <limits>
#include <ios>

/*********
A program to understand Regular Expressions in C++

The syntax of the Regular expressions offerred in C++11 matches the ones found in Shell, Python etc.

C++ 11 provides different regular expression grammer, that can be used.
The most powerful and the default grammer is the ECMAScript.

The various grammar offered are,
ECMAScript
basic
extended
grep
egrep
awk

Each of the grammar(ECMAScript is the default) can be specified by the following regex_constants

regex_constants::ECMAScript		Use the Modified ECMAScript regular expression grammar
regex_constants::basic			basic POSIX regular expression grammar.
regex_constants::extended		extended POSIX regular expression grammar.
regex_constants::awk			regular expression grammar used by the awk utility in POSIX
regex_constants::grep			regular expression grammar used by the grep utility in POSIX. 
								Same as the basic option with the addition of newline '\n' as an alternation separator.
regex_constants::egrep			regular expression grammar used by the grep utility, with the -E option, in POSIX.
								Same as the extended option with the addition of newline '\n' as an alternation separator in addtion to '|'.

std::match_results:
===================

std::smatch is an instantiation of the match_results class template for matches on string object.
The container-like class is used to store the matches found after a regex matching operation, 
with each match set as the corresponding sub_match type.								

Operations:
~~~~~~~~~~~ 
str():			returns the sequence of characters for the particular sub-match.
operator[]:		returns specified sub-match.
prefix():		returns sub-sequence between the beginning of the target sequence and the beginning of the full match. 
suffix():		returns sub-sequence between the end of the full match and the end of the target sequence.

smatch sm;
sm[0]:			returns the entire string that matches.
sm[n,n != 0]	returns substring that matches the nth group.
*********/
bool match(const std::string & str, const std::regex & rg)
{
    if (std::regex_match(str, rg))
        std::cout << "Pattern found ... " << std::endl; 
    else
        std::cout << "Pattern not found ..." << std::endl;
}

void matchPattern()
{
   std::string str;

   do
   {
        std::cout << "Enter a string:";

        std::cin >> str;

        //    std::regex r("pqr");    // Matches the exact, case sensitive string "pqr". No other string would match.

        //    std::regex r("pqr", std::regex_constants::icase);     // Matches the exact string, case insensitive

        //    std::regex r("pqr.", std::regex_constants::icase);    // A dot '.' matches any character except a newline

        //    std::regex r("pqr?", std::regex_constants::icase);    // A '?' matches zero or one occurance of the preceding character

        //    std::regex r("pqr*", std::regex_constants::icase);    // A '*' matches zero or more occurance(s) of the preceding character

        //    std::regex r("pqr+", std::regex_constants::icase);    // A '+' matches one or more occurance(s) of the preceding character

        //    std::regex r("pq[rs]*", std::regex_constants::icase); // Square brackets [...] match a character within the brackets
        // A * following the [...] matches the character for zero or more occurances.

        //    std::regex r("pq[^rs]*", std::regex_constants::icase);// Square brackets beginning with [^...] match a characte not contained 
        // within the brackets
        // A * following the [...] matches the character for zero or more occurances.

        //    std::regex r("pq[rs]{2}", std::regex_constants::icase); // Parenthesis after braces match exactly n occurances of the letters

        //    std::regex r("pq[rs]{2,}", std::regex_constants::icase); // Parenthesis after braces match n or more occurances of the letters

        //    std::regex r("pq[rs]{2,4}", std::regex_constants::icase); // Parenthesis after braces {n,m} match from n to m occurances of letters

        //    std::regex r("pqr|st[\"uv]");       // Will match either pqr OR st" OR stu OR stv

        //    std::regex r("(pqr)st+\\1");        // The parenthesis match a group and a \\n indicates the re-occurance of the group
        // The above pattern would match [pqrs'one or more occurances of t'pqr] group again

        //    std::regex r("(pqr)st(lm)uv\\2\\1");  // The only pattern that matches is 'pqrstlmuvlmpqr'

        // Predefined patterns.
        // C++ 11 provides a bunch of predefined characters for matching one or more set of characters

        //    std::regex r("[[:lower:]]*");  // Matches any count of lower case alphabets

        //     std::regex r("[[:punct:]]");  // Matches any punctuation mark character

        //     std::regex r("[[:w:]]");      // Matches any alphanumric character

        std::regex r("[[:digit:]]");    // Matches a single digit character


        if (std::regex_match(str, r))
            std::cout << "Pattern found ... " << std::endl; 
        else
            std::cout << "Pattern not found ..." << std::endl;

    }while (str != "end");

}

void searchPattern()
{
    std::string str;
    // Clear the cin buffer 
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); 

    std::cout << std::endl << "Enter the complete string:";
    std::getline(std::cin, str);

    std::string ss;
    std::cout << std::endl << "Enter substring to search inside string:";
    std::cin >> ss;

    std::regex rg(ss);

    if (std::regex_search(str, rg))
        std::cout << "Pattern found ... " << std::endl; 
    else
        std::cout << "Pattern not found ..." << std::endl;
}

void verifyGrammar()
{
//    std::regex r("^pqr.+"); // This is the ECMAScript which is also the default grammar 
                            // Match pattern starting with pqr, followed by 1 or more characters 

    std::regex r("^pqr.+", std::regex_constants::grep); // grep grammar treats the + as as literal rather than subsituting it.

    std::string str;   
    do
    {
        std::cout << "\n Enter string:"; std::cin >> str;

        match(str, r);
    }while(str != "end");
}

void verifySubmatch()
{

    std::string prefix = "{sample prefix}";     // String before the pattern to match
    std::string suffix = "{A sample suffix}";   // String after the pattern to match

    std::string s = "https://www.google.com";

    std::string str = prefix + s + suffix;  // String including the prefix and suffix
    std::cout << "str: " << str << std::endl;
	
    // std::smatch is container-like class used to store the matches found after a regex matching operation, 
	// with each match set as the corresponding sub_match type.

	std::smatch sm;		// smatch is a typedef for match_results 
                        // 'typedef match_results<string::const_iterator> smatch'
	
	std::regex r("([[:w:]]+)://([[:w:]]+).([[:w:]]+).([[:w:]]+)");    // Matches a web URL

    std::regex_search(str, sm, r);

    std::cout << "sm.size(): " << sm.size() << std::endl;

    // Each of the substrings parsed are stored in the smatch container.
    // The substring at index zero stores the entire string, with each of the next indices storing the individual strings.

    for(int i=0; i< sm.size(); ++i)
        std::cout << "sm[" << i << "]: " << sm[i].str() << std::endl;

    std::cout << "sm.prefix : " << sm.prefix().str() << std::endl;
    std::cout << "sm.suffix: " << sm.suffix().str() << std::endl;


    // The std::smatch is a template of the std::string::const_iterator.
    // The standard operations on an iterator can be used on the smatch.

    std::cout << "sm.begin()        :" << *sm.begin() << std::endl;
    std::cout << "sm.begin() + 1    :" << *(sm.begin() + 1) << std::endl;
    std::cout << "sm.end() - 1      :" << *(sm.end() - 1) << std::endl;

}

int main()
{
//    matchPattern();

//    searchPattern();

//    verifyGrammar();

    verifySubmatch();

    return 0;
}
