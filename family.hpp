//
//  family.hpp
//  NHF
//
//  Created by Ákos Gyöngyösi on 2023. 05. 20..
//

#ifndef family_hpp
#define family_hpp

#include <iostream>
#include "movie.hpp"
#include "memtrace.h"
#include "gtest_lite.h"

class family : public movie {
    int age_limit;
    
public:
    family(std::string n, int p, int r, int a = 0) :movie(n, p, r), age_limit(a) {}
    int getage_limit() const {return age_limit;}
    void print() const{
        std::cout << "Title: " << getname() << std::endl <<
        "Playback time: " << getplayback_time() << std::endl <<
        "Released in: " << getreleased() << std::endl <<
        "Age limit: " << getage_limit() << std::endl;
    }
    ~family() {
        
    }
    
    virtual std::string movie_save() {
        std::ostringstream ss;
        ss << 2 << '#' << getname() << '#' << getplayback_time() << '#' << getreleased() << '#' << getage_limit() << '#';
        return ss.str();

    }
    
};

#endif /* family_hpp */
