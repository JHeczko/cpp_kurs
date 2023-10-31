#pragma once

#include <string>
#include <cstring>

class NewClass{
    public:
        NewClass(std::string string); // konstruktor
        NewClass(const NewClass&); //kopiujacy konstruktot
        NewClass(NewClass&&); // konstruktor przemieszczenia
        NewClass& operator= (NewClass&&);
        NewClass& operator= (const NewClass&);
        ~NewClass(); //destruktor

    private:
        std::string string;


};