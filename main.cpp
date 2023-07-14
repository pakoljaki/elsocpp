//
//  main.cpp
//  NHF
//
//  Created by Ákos Gyöngyösi on 2023. 05. 11..
//


#include <iostream>
#include <cstring>
#include <sstream>
#include <limits>
#include "movie.hpp"
#include "container.hpp"
#include "documentary.hpp"
#include "family.hpp"

//#ifdef JPORTA
#include "gtest_lite.h"

#include "memtrace.h"
//#endif

int main() {
    
//#ifdef JPORTA
    
    
    TEST(movie, getterek()-print()-movie_save()) {
        movie* movie1 = new movie("star_wars", 135, 1985);
        //getterek
        EXPECT_STREQ("star_wars", movie1->getname().c_str()); //movie-getname()
        EXPECT_EQ(135, movie1->getplayback_time()); //movie-getplayback()
        EXPECT_EQ(1985, movie1->getreleased()); //movie-getreleased()
        //print
        std::ostringstream outputStream;
        std::streambuf* oldCoutBuffer = std::cout.rdbuf(outputStream.rdbuf());
        movie1->print();
        std::cout.rdbuf(oldCoutBuffer);
        std::string output1 = outputStream.str();
        const char* expectedOutput1 = "Title: star_wars\n"
                                     "Playback time: 135\n"
                                     "Released in: 1985\n";
        EXPECT_STREQ(output1.c_str(), expectedOutput1);
        //movie_save
        std::string movie1_str_actual = movie1->movie_save();
        const char* movie1_str_expected = "1#star_wars#135#1985#";
        EXPECT_STREQ(movie1_str_expected, movie1_str_actual.c_str());
        
        delete movie1;
    } ENDM
    TEST(family, getter()-print()-movie_save()) {
        family* movie2 = new family("up", 90, 2005, 6);
        //getter
        EXPECT_EQ(6, movie2->getage_limit()); //family-getagelimit()
        //print
        std::ostringstream outputStream;
        std::streambuf* oldCoutBuffer = std::cout.rdbuf(outputStream.rdbuf());
        movie2->print();
        std::cout.rdbuf(oldCoutBuffer);
        std::string output2 = outputStream.str();
        const char* expectedOutput2 = "Title: up\n"
                                     "Playback time: 90\n"
                                     "Released in: 2005\n"
                                     "Age limit: 6\n";
        EXPECT_STREQ(output2.c_str(), expectedOutput2);
        //movie_save
        std::string movie2_str_actual = movie2->movie_save();
        const char* movie2_str_expected = "2#up#90#2005#6#";
        EXPECT_STREQ(movie2_str_expected, movie2_str_actual.c_str());
        
        delete movie2;
    } ENDM
    TEST(documentary, getter()-print()-movie_save()) {
        documentary* movie3 = new documentary("the_blue_planet", 140, 2019, "david_attenborough_...");
        //getter
        EXPECT_STREQ("david_attenborough_...", movie3->getdescription().c_str());
        //print
        std::ostringstream outputStream;
        std::streambuf* oldCoutBuffer = std::cout.rdbuf(outputStream.rdbuf());
        movie3->print();
        std::cout.rdbuf(oldCoutBuffer);
        std::string output3 = outputStream.str();
        const char* expectedOutput3 = "Title: the_blue_planet\n"
                                     "Playback time: 140\n"
                                     "Released in: 2019\n"
                                     "Description: david_attenborough_...\n";
        EXPECT_STREQ(output3.c_str(), expectedOutput3);
        //movie_save
        std::string movie3_str_actual = movie3->movie_save();
        const char* movie3_str_expected = "3#the_blue_planet#140#2019#david_attenborough_...#";
        EXPECT_STREQ(movie3_str_expected, movie3_str_actual.c_str());
        
        delete movie3;
    } ENDM
    TEST(container, print()-add()-erase()) {
        movie* movie1 = new movie("star_wars", 135, 1985);
        family* movie2 = new family("up", 90, 2005, 6);
        documentary* movie3 = new documentary("the_blue_planet", 140, 2019, "david_attenborough_...");
        container container1;
        //add függvény tesztelése mindhárom tipusú objektumra
        container1.add(movie1);
        container1.add(movie2);
        container1.add(movie3);
        //container.print() fv tesztelése
        std::ostringstream outputStream;
        std::streambuf* oldCoutBuffer = std::cout.rdbuf(outputStream.rdbuf());
        container1.print();
        std::cout.rdbuf(oldCoutBuffer);
        std::string output = outputStream.str();
        const char* expectedOutput = "******************************\n"
                                     "List of all movies in the database\n"
                                     "******************************\n"
                                     "Title: star_wars\n"
                                     "Playback time: 135\n"
                                     "Released in: 1985\n"
                                     "******************************\n"
                                     "Title: up\n"
                                     "Playback time: 90\n"
                                     "Released in: 2005\n"
                                     "Age limit: 6\n"
                                     "******************************\n"
                                     "Title: the_blue_planet\n"
                                     "Playback time: 140\n"
                                     "Released in: 2019\n"
                                     "Description: david_attenborough_...\n"
                                     "******************************\n";
        EXPECT_STREQ(output.c_str(), expectedOutput);
        
        //container.erase fv tesztelése
        //container container2;
        //container2.erase(0);
        //container2.add(movie1);
        //container2.erase(1);
        //EXPECT_EQ(0, container2.num());
        container1.erase(1);
        EXPECT_EQ(2, container1.num());
        
    } ENDM
    
//#endif
    
    
    container Container;
    bool continue_cycle = true;
    int choice;
    Container.fill();
    do {
        std::cout << "******************************\nMenu\n******************************\n 1. Add new movies to database\n 2. List all movies in database\n 3. Delete movie from database\n 4. Save and exit\nAdd a number from between 1 and 4\n";
        
        while (!(std::cin >> choice)) {
            if (std::cin.eof()) {
                return 0;
            }
            if (choice < 1 || choice > 4) {
                std::cerr << "Invalid input, add a number between 1 and 4\n";
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number: ";
            }
        
        
        switch (choice) {
            case 1:
                Container.new_movie_from_user();
                break;
            case 2:
                Container.print();
                break;
            case 3:
                Container.erase_a_movie();
                break;
            case 4:
                Container.save();
                continue_cycle = false;
                break;
            default:
                break;
        }
    } while(continue_cycle);
    
    return 0;
}
