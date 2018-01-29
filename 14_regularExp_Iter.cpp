#include <iostream>
#include <regex>

/*********
A program to understand Iterators in Regular Expressions in C++ 11.

Given a pattern to be matched in a string/character sequence, each matching substring is pointed by 
and individual element of the iterator.

regex_iterator:

	std::regex_iterator is a read-only iterator that accesses the individual matches of a regular expression 
	within the underlying character sequence.

	regex_iterator ( BidirectionalIterator first, BidirectionalIterator last, const regex_type& rgx,
					regex_constants::match_flag_type flags = regex_constants::match_default );

	first, last: 	Bidirectional iterators to the initial and final positions in the range used as target sequence 
					for the search. 
	rgx:			A basic_regex object (the pattern) to match.
	flags:			Flags used to control how rgx is matched.


	Type			Definition
	==========================
	cregex_iterator		regex_iterator<const char*>
	wcregex_iterator	regex_iterator<const wchar_t*>
	sregex_iterator		regex_iterator<std::string::const_iterator>
	wsregex_iterator	regex_iterator<std::wstring::const_iterator>

	
	
regex_token_iterator:
	The regex_token_iterator matches each the individual grouping/ sub-matches inside the pattern to be searched.
	It applies the regex expression repeatedly over the target string.
	
	It accesses individual sub-matches for each match of a regular expression within the underlying character sequence. 
	It can also be used to access the parts of the sequence that are not matched by the given regular expression (e.g. as a tokenizer).	


	Type					Definition
	===================================	
	cregex_token_iterator	regex_token_iterator<const char*>
	wcregex_token_iterator	regex_token_iterator<const wchar_t*>
	sregex_token_iterator	regex_token_iterator<std::string::const_iterator>
	wsregex_token_iterator	regex_token_iterator<std::wstring::const_iterator>
	
**********/

int main()
{
    std::string strs = "https://www.google.com; http://www.yahoo.co.in;; http://www.gnu.org";
    std::cout << "String: " << strs << std::endl;

   // icase is a flag passed to the regex constructor to ignore the case when matching pattern.
   // Besides there are other bit flags in regex_constants that allow to specify grammar etc. 

	std::regex r("([[:w:]]+)://([[:w:]]+).([[:w:]]+).([[:w:]]+)", std::regex_constants::icase);      // Matches a web URL

# if 0	
	std::smatch sm;		// 'typedef match_results<string::const_iterator> smatch'
	
    std::regex_search(strs, sm, r);				// Using regex_search matches only the first instance,
												// which isnt what we want.
    for(int i=0; i< sm.size(); ++i)
        std::cout << "sm[" << i << "]: " << sm[i].str() << std::endl;
#else

    // regex_iterator:
	// Given a pattern to be matched in a string/character sequence, each matching substring is pointed by 
	// and individual element of the iterator.
	
    std::regex_iterator <std::string::iterator> rgit(strs.begin(), strs.end(), r);
    std::regex_iterator <std::string::iterator> rgend;

    // Print each of the strings that match the pattern specified by regex r
    for(;rgit != rgend; ++rgit)
    {
        std::cout << rgit->str() << std::endl;

        for(int i = 0; !(rgit->str(i).empty()); ++i)    // Print the submatches for each group inside the string.
            std::cout << " str[" << i << "]: " << rgit->str(i) << std::endl;
    }
	
	// regex_token_iterator
	//	std::sregex_token_iterator rgtit(strs.cbegin(), strs.cend(), r);    // without any parameters the token iterator matchs the entire submatch.

    // The regex_token_iterator is used to match a submatch inside a regex match
    // regex_token iterator applies the regular expression repeatedly over the target string.

    // The regex_token_iterator also takes an additional parameter to identify the token in the pattern matched, 
    // 0 being the default, matches the entire pattern.
    // For e.g. 1 would match the token http/https, 3 google,yahoo,gnu etc.
	
	std::sregex_token_iterator rgtit(strs.cbegin(), strs.cend(), r, /*3*/-1);    // Matches the 3nd token in each of the sub-matches.
	std::sregex_token_iterator rgtend;									    // Specifying -1 matches the part of the string not 
																	    	// matched by the regular expression. In the current case (;) semi-colons

	// Print each of the strings that match the pattern specified by regex r
    for(;rgtit != rgtend; ++rgtit)
    {
        std::cout << rgtit->str() << std::endl; 
    }

    // regex_replace 

    // regex_replace() replaces in a string each of the matches by a regex_iterator, and pointed by $n,
    // with the string matched.

    std::cout << regex_replace(strs, r, "\n$3 is accessed via $1") << std::endl;
    
    // In the above usage of regex_replace, it also matched .in which is not a part of the regex pattern
    // To prevent from a non-matching part getting printed use regex_replace with regex_constants::format_no_copy.

    std::cout << regex_replace(strs, r, "\n$3 is accessed via $1", std::regex_constants::format_no_copy) << std::endl;
    
#endif

    return 0;
}
