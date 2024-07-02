A small, fast and portable (hopefully) library to properly iterate over UTF-8 strings and convert both characters and strings to UTF-32.

This library only uses `wchar_t` and `wstring` for output and relies on regular `std::string` and `const char *` to represent UTF-8 characters, and `uint32_t` - to represent both UTF-8 and UTF-32.

The actual library includes only 2 files, `utf8.h` and `utf8.cpp`.
