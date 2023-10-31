#pragma once

#include <iostream>
#include <cstdlib>

class TArr {
public:
    //methods
    void getInfo();
    void zmienCos(int* buf , std::size_t len);
    //x-tors
    TArr(int* buf = nullptr, std::size_t = 0);
    TArr(const TArr&);
    TArr(TArr&&);
    ~TArr();
    //operatory
    const TArr& operator=(const TArr&);
    const TArr& operator=(TArr&&);

private:
    struct InnerArray {
        std::size_t len{0};
        std::size_t ref{0};
        int *buf{nullptr};
}* ptr{nullptr};
};
