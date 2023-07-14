

#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "movie.hpp"
#include "family.hpp"
#include "documentary.hpp"
#include "memtrace.h"
#include "gtest_lite.h"


class container {
    int numarr;
    movie** array;
   
public:
    container(int num = 0) :numarr(num), array(NULL) {}
    
    ~container() {
        if (array != NULL) {
            for (int i = 0; i < numarr; i++) {
                delete array[i];
            }
            delete[] array;
        }
    }
    int num() const {return numarr;}
    void add(movie* element);
    void new_movie_from_user();
    void fill();
    void print() const;
    void erase_a_movie();
    void erase(int num);
    void save();
};

#endif

