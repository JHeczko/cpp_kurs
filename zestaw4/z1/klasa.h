#pragma once
#include <string>
#include <compare>
#include <tuple>
#include <cstring>
#include <string>

using namespace std;

class TKlasa {

public:
    TKlasa(const char* c); // zmień to na definicję z inicjalizacją
    const char* operator[](const char* s);
    friend auto operator<=>(const TKlasa& a, const TKlasa& b){
        return (a.str <=> b.str);
    };
private:
    std::string str;
};