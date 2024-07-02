#include "utf8.h"
#include <iostream>
#include <fcntl.h>
#include <io.h>

void attemptConversion(uint32_t u8ch_, size_t sz_, const std::string &expected)
{
    auto res = utf8::numericToString(utf8::u8tou32(u8ch_, sz_));
    std::cout << "Result:   " << res;
    if (res == expected)
        std::cout << " - CORRECT!\n";
    else
        std::cout << " - FAILED!\nExpected: " << expected << std::endl;
}

void attemptConversion(const char *u8ch_, const std::string &expected)
{
    auto res = utf8::numericToString(utf8::tou32(u8ch_));
    std::cout << "Result:   " << res;
    if (res == expected)
        std::cout << " - CORRECT!\n";
    else
        std::cout << " - FAILED!\nExpected: " << expected << std::endl;
}

void TestConversions()
{
    attemptConversion(0b00110000, 1, "00000000'00000000'00000000'00110000"); // '0' U+0030
    attemptConversion(0b01111101, 1, "00000000'00000000'00000000'01111101"); // '}' U+007D
    attemptConversion(0b01111111, 1, "00000000'00000000'00000000'01111111"); // Delete U+007F

    attemptConversion(0b1101000010010111, 2, "00000000'00000000'00000100'00010111"); // 'З' U+0417
    attemptConversion(0b1101110110011000, 2, "00000000'00000000'00000111'01011000"); // 'ݘ' U+0758
    attemptConversion(0b1101111110111111, 2, "00000000'00000000'00000111'11111111"); // '߿' U+07FF

    attemptConversion(0b111000001010001010110011, 3, "00000000'00000000'00001000'10110011"); // 'ࢳ' U+08B3
    attemptConversion(0b111001011010010010101001, 3, "00000000'00000000'01011001'00101001"); // '天' U+5929
    attemptConversion(0b111011111011111110100110, 3, "00000000'00000000'11111111'11100110"); // '￦' U+FFE6

    attemptConversion(0b11110000100111111000110010001101, 4, "00000000'00000001'11110011'00001101"); // '🌍' U+1F30D
    attemptConversion(0b11110000100111111001110010000111, 4, "00000000'00000001'11110111'00000111"); // '🜇' U+1F707
    attemptConversion(0b11110000100111111010100110101101, 4, "00000000'00000001'11111010'01101101"); // U+1FA6D

    const char *prep = "0}З天🌍";
    const char *iter = prep;
    attemptConversion(iter, "00000000'00000000'00000000'00110000");
    iter = utf8::iterateForward(iter);
    attemptConversion(iter, "00000000'00000000'00000000'01111101");
    iter = utf8::iterateForward(iter);
    attemptConversion(iter, "00000000'00000000'00000100'00010111");
    iter = utf8::iterateForward(iter);
    attemptConversion(iter, "00000000'00000000'01011001'00101001");
    iter = utf8::iterateForward(iter);
    attemptConversion(iter, "00000000'00000001'11110011'00001101");

}

void TestIteratorOperatorsU8(const std::string &s_)
{
    auto s = s_;
    std::string collector = "";
    for (const auto &el : U8Wrapper(s))
    {
        std::cout << el;
        collector += el;
        collector = collector + el;
        collector = el + collector;
    }
    std::cout << std::endl;
    std::cout << "Wrapped:   " << U8Wrapper(s) << std::endl;
    std::cout << "Collector: " << collector << std::endl;
}

void TestIteratorOperatorsU32(const std::string &s_)
{
    auto s = s_;
    std::wstring collector = L"";
    for (const auto &el : U8Wrapper(s))
    {
        collector += el;
        collector = collector + el;
        collector = el + collector;
    }
    std::wcout << std::endl;
    std::wcout << "WCollector: " << collector << std::endl;
}

int main()
{
    std::string ch1 = "天";
    std::cout << utf8::numericToString(utf8::readChar(ch1.c_str())) << std::endl;
    std::cout << utf8::getChar(utf8::readChar(ch1.c_str())) << std::endl;
    std::cout << U8Wrapper(ch1).begin().getCharAsString() << std::endl;

    std::string sample = "🌍привет fG天";
    std::cout << "Basic string: \"" << sample << "\"\n";

    TestConversions();
    
    TestIteratorOperatorsU8(sample);

    _setmode(_fileno(stdout), _O_WTEXT);
    _setmode(_fileno(stdin), _O_WTEXT);

    TestIteratorOperatorsU32(sample);

    std::wstring ws = U8Wrapper(sample).toWString();
    std::wcout << ws << std::endl;
}
