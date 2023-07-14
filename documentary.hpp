//
//  documentary.hpp
//  NHF
//
//  Created by Ákos Gyöngyösi on 2023. 05. 20..
//

#ifndef documentary_hpp
#define documentary_hpp

#include <iostream>
#include "movie.hpp"
#include "memtrace.h"
#include "gtest_lite.h"

class documentary : public movie {
    std::string text_description;
    
public:
    documentary(std::string n, int p, int r, std::string t = "--no description--") :movie(n, p, r), text_description(t) {}
    std::string getdescription() const {return text_description;}
    void print() const{
        std::cout << "Title: " << getname() << std::endl <<
        "Playback time: " << getplayback_time() << std::endl <<
        "Released in: " << getreleased() << std::endl <<
        "Description: " << getdescription() << std::endl;
        
    }
    virtual std::string movie_save() {
        std::ostringstream ss;
        ss << 3 << '#' << getname() << '#' << getplayback_time() << '#' << getreleased() << '#' << getdescription() << '#';
        return ss.str();
    }
    ~documentary() {
        
    }
};

#endif /* documentary_hpp */
