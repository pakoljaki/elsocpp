
#include <iostream>
#include <string>
#include "memtrace.h"
#include "gtest_lite.h"


#ifndef MOVIE_H
#define MOVIE_H

class movie {
    std::string name;
    int playback_time;
    int released;
    
public:
    movie(std::string n = "--no movie--", int p = 0, int r = 0) : name(n), playback_time(p), released(r) {}
    std::string getname() const {return name;}
    int getplayback_time() const {return playback_time;}
    int getreleased() const {return released;}
    virtual void print() const{
        std::cout << "Title: " << getname() << std::endl <<
        "Playback time: " << getplayback_time() << std::endl <<
        "Released in: " << getreleased() << std::endl;
    }
    virtual std::string movie_save() {
        std::ostringstream ss;
        ss << 1 << '#' << getname() << '#' << getplayback_time() << '#' << getreleased() << '#';
        return ss.str();
    }
    virtual ~movie() {
    }
};



#endif


