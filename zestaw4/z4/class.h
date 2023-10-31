#pragma once

#include <iostream>

template<class Type> class SmartPtr{
    public:
        SmartPtr(Type* x = nullptr): ptr(x){};
        ~SmartPtr(){if(ptr != nullptr){
            delete ptr;}
            };

        Type& operator*(){
            return *ptr;
        };

        Type* operator->(){
            return ptr;
        };
    private:
        Type* ptr{nullptr};
};