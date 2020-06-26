#include <iostream>
#include <string>
#include <locale>       // for wstring_convert
#include <codecvt>      // for codecvt_utf8

/***

    C++ 11 introduces the following String Literals.

      "..."         /// String literal,                 where size is of const char N, including the NULL terminator
    L "..."         /// Wide String Literal,            where size is of const wchar_t N
    u8"..."         /// UTF-8 encoded string literal,   where size is const char8_t[N]       /// char8_t is available since C++ 20
    u"..."          /// UTF-16 encoded string literal,  where size is const char16_t[N]
    U"..."          /// UTF-32 encoded string literal,  where size is const char32_t[N]
    u8"..."         /// UTF-8 encoded string literal,   where size is const char8_t[N]

    R"delim(...)delim"  /// Used to define a Raw string literal to avoid escaping special charaters in the string literal
                        /// The delimeter is optional.

    To print a 'UTF-16' or 'UTF-32' string, you can either convert each of the characters to a hex and print using cout OR
    convert the string to a utf-8 and print using cout.
    Use wstring_covert to convert from wide strings to byte strings and vice-versa using a conversion object of 'Codecvt'. 
    
    The wide string 'wchar_t' is printed using a 'std::wcout'.
    
***/

int main()
{
    char str1[] = "String with \\n special \" characters ()";
    char str2[] = R"rawstr(String with \n special " characters () )rawstr";     // Raw String Literal

    std::cout << "str1: " << str1 << std::endl;
    std::cout << "str2: " << str2 << std::endl;

    wchar_t strL[]      = L"Hello C++11";
    char stru8[]        = u8"Hello C++11";
    char16_t stru[]     = u"Hello C++11";
    char32_t strU[]     = U"Hello C++11";

    /// char8_t stru8[]    = u8"Hello C++11";           /// char8_t is available since C++ 20

    std::cout << std::endl;

    std::wcout << "strL(wchar_t): "  << strL  << ", sizeof(strL): " << sizeof(strL)   << std::endl;
    std::cout << "stru8(char): " << stru8 << ", sizeof(stru8): " << sizeof(stru8) << std::endl;

    std::cout << "=================================================" << std::endl;
    std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> cv16to8bytes;
    std::string struConv = cv16to8bytes.to_bytes(stru);
    std::cout << "stru(char16_t): " << struConv << ", sizeof(stru): " << sizeof(stru)   << std::endl;

    std::cout << "Printing bytes stru(char16_t):" << std::endl;
    for(char16_t c: stru)
        std::cout << std::hex << c << "(" << static_cast<char>(c) << ") " ; std::cout << std::endl;
 
    std::cout << "=================================================" << std::endl;
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> cv32to8bytes;
    std::string strUConv = cv32to8bytes.to_bytes(strU);
    std::cout << "strU(char32_t): " << strUConv << ", sizeof(strU): " << sizeof(strU)   << std::endl;

    std::cout << "Printing bytes strU(char32_t):" << std::endl;
    for(char32_t c: strU)
        std::cout << std::hex << c << " "; std::cout << std::endl;
    
    return 0;
}
