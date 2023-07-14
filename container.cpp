//
//  container.cpp
//  NHF
//
//  Created by Ákos Gyöngyösi on 2023. 05. 20..
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "container.hpp"
#include "memtrace.h"
#include "gtest_lite.h"

void container::add(movie* element) {
    movie** newarray = new movie*[numarr + 1];
    for (int i = 0; i < numarr; i++) {
        newarray[i] = array[i];
    }
    newarray[numarr] = element;
    if (numarr != 0) {
        delete[] array;
    }
    array = newarray;
    numarr++;
}

void container::new_movie_from_user() {
    std::cout << "******************************\nAdd new movies to database\n******************************\n";
    std::string name, text_desc;
    int playback, released, age, type;
    std::cout << "Add a number, which type of movie you want to add?\n1 movie\n2 family\n3 documentary\n";
    std::cin >> type;
    std::cin.ignore();
    if (type == 1 || type == 2 || type == 3) {
        while (true) {
            std::cout << "Add the name, playback time (in mins), released (year)\n(divide them with whitespaces, in the name use '_' instead of whitespaces)\n";
            std::getline(std::cin, name);
            std::istringstream iss(name);
            if (iss >> name >> playback >> released && iss.eof()) {
                break; //ha jo a formatum kilep
            }
            std::cout << "Invalid input format. Please try again." << std::endl;
        }
        if (type == 1) {
            movie* Movie1 = new movie(name, playback, released);
            add(Movie1); 
        }
        if (type == 2) {
            std::cout << "Add the age limit: ";
            std::cin >> age;
            family* Movie2 = new family(name, playback, released, age);
            add(Movie2);
        }
        if (type == 3) {
            std::cout << "Add text description: ";
            std::cin >> text_desc;
            documentary* Movie3 = new documentary(name, playback, released, text_desc);
            add(Movie3);
        }
    }
    else std::cerr << "You chose a wrong index\n";
    return;
}

void container::fill() { //filmek betoltese
    
    std::ifstream file("movies.txt");
    //std::ifstream file;
    //file.open("movies.txt");
    if (!file) {
        std::cerr << "Opening movies.txt for reading was unsuccesfull.\n";
        return;
    }
    int number_of_elements;
    file >> number_of_elements;
    file.ignore(1);
    for (int i = 0; i < number_of_elements; i++) {
        std::string line;
        std::getline(file, line);
        std::stringstream s(line);
        std::string name, playback_string, released_string, t, a, text;
        getline(s, t, '#');
        int type = stoi(t);
        getline(s, name, '#');
        getline(s, playback_string, '#');
        int playback = stoi(playback_string);
        getline(s, released_string, '#');
        int released = stoi(released_string);
        
        switch (type) {
            case 1: {
                movie* Movie1 = new movie(name, playback, released);
                add(Movie1);
               // Movie1->print();
                //delete Movie1;
                break;
            }
            case 2: {
                getline(s, a, '#');
                int age_limit = stoi(a);
                family* Movie2 = new family(name, playback, released, age_limit);
                add(Movie2);
               // Movie2->print();
                //delete Movie2;
                break;
            }
            case 3: {
                std::getline(s, text, '#');
                documentary* Movie3 = new documentary(name, playback, released, text);
                add(Movie3);
               // Movie3->print();
                //delete Movie3;
                break;
            }
            default:
                break;
        }
        
    }
   
    //file.close();
}

void container::print() const{
    std::cout << "******************************\nList of all movies in the database\n******************************\n";
    if (numarr == 0) {
        std::cout << "There are no movies in the database!" << std::endl;
    }
    else {
        for (int i = 0; i < numarr; i++) {
            array[i]->print();
            std::cout << "******************************" << std::endl;
        }
    }
    
    
    
}
void container::erase_a_movie() {
    std::cout << "******************************\nDelete movie from database\n******************************\n";
    int num;
    for (int i = 0; i < numarr; i++) {
        std::cout << " (" << i+1 << ") " << array[i]->getname() << std::endl;
    }
    std::cout << "Choose index number of the movie you want to delete: ";
    
    while (!(std::cin >> num)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number: ";
        }
    erase(num);
    
}

void container::erase(int num) {
    if (num < 1 || num > numarr) {
        return;
    }
    if (numarr == 0) {
        std::cout << "There are no movies in the database, so none can be erased\n" << std::endl;
    }
    if (numarr == 1) {
        delete array[0];
        numarr--;
    }
    else {
        movie** newarray = new movie*[numarr - 1];
        int j = 0;
        for (int i = 0; i < numarr; i++) {
            if (num - 1 != i) {
                newarray[j++] = array[i];
            }
            else
                delete array[i];
        }
        delete[] array;
        array = newarray;
        numarr--;
    }
}

void container::save() {
    std::cout << "******************************\nSave and exit\n******************************\n";
    //std::ifstream file("movies.txt");
    std::ofstream file;
    file.open("movies.txt", std::ofstream::out | std::ofstream::trunc);
    if (!file.is_open()) {
        std::cerr << "Opening movies.txt for writing was unsuccesfull.\n";
        return;
    }
    file << numarr << std::endl;
    for (int i = 0; i < numarr; i++) {
        file << array[i]->movie_save() << std::endl;
    }
   // file.close();
}
