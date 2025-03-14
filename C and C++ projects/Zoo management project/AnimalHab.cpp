//
// Created by juanm on 23/04/2022.
//

#include "AnimalHab.h"
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

AnimalHab::AnimalHab(int habitatNum, const char* Species, int foodFreq, int cleanFreq, int day){

    this->habitatNum = habitatNum;
    this->Species = new char[strlen(Species) + 1];
    strcpy(this->Species, Species);
    this->foodFreq = foodFreq;
    this->cleanFreq = cleanFreq;
    this->foodLT = day;
    this->cleanLT = day;
    this->foodReceived = 1;
    this->habCleaned = 1;

}

AnimalHab::AnimalHab(const AnimalHab& copiedAnimal){

    this->habitatNum = copiedAnimal.habitatNum;
    this->Species = new char[strlen(copiedAnimal.Species) + 1];
    strcpy(this->Species, copiedAnimal.Species);
    this->foodFreq = copiedAnimal.foodFreq;
    this->cleanFreq = copiedAnimal.cleanFreq;
    this->foodLT = copiedAnimal.foodLT;
    this->cleanLT = copiedAnimal.cleanLT;
    this->foodReceived = copiedAnimal.foodReceived;
    this->habCleaned = copiedAnimal.habCleaned;

}

AnimalHab::~AnimalHab() {

    //print();
    delete[] this->Species;

}

int AnimalHab::get_habitatNo() const {
    int rethabnum = this->habitatNum;
    return rethabnum;
}

const char* AnimalHab::get_Species() const{
    const char* retSpec = this->Species;
    return retSpec;
}

int AnimalHab::get_foodReceived() const {
    int retfoodRec = this->foodReceived;
    return retfoodRec;
}

void AnimalHab::set_foodReceived(int amount) {
    this->foodReceived = amount;
}

int AnimalHab::get_habitatCleaned() const {
    int rethabclean = this->habCleaned;
    return rethabclean;
}

void AnimalHab::set_habitatCleaned(int amount) {
    this->habCleaned = amount;
}

void AnimalHab::set_foodLastTime(const int actualDay) {
    this->foodLT = actualDay;
}

void AnimalHab::set_cleanLastTime(const int actualDay) {
    this->cleanLT = actualDay;
}

int AnimalHab::chk_food(int currDay) const {

    if(this->foodReceived <= 0){
        return 1;
    }else if(this->foodReceived > 1 && this->foodReceived <= 3){
        return 2;
    }else if(foodReceived > 3){
        return 3;
    }else if( (currDay - this->foodLT) > this->foodFreq){
        return 4;
    }

    return 0;
}

bool AnimalHab::chk_foodPeriod(int currDay) const {

    if( ((currDay - this->foodLT) >= this->foodFreq) && (this->foodReceived > 0) ){
        return true;
    }
    return false;

}

int AnimalHab::chk_cleaning(int currDay) const {

    if(this->habCleaned <= 0){
        return 1;
    }else if(this->habCleaned > 1 && this->habCleaned <= 3){
        return 2;
    }else if( this->habCleaned > 3){
        return 3;
    }else if( (currDay - this->cleanLT) > this->cleanFreq){
        return 4;
    }

    return 0;

}

bool AnimalHab::chk_cleaningPeriod(int currDay) const {

    if( ((currDay - this->cleanLT) >= this->cleanFreq) && (this->habCleaned > 0) ){
        return true;
    }
    return false;
}

void AnimalHab::print() {

    cout << endl << "Habitat number: " << this->habitatNum;
    cout << endl << "Species: " <<  this->Species;
    cout << endl << "Food frequency: " <<  this->foodFreq;
    cout << "\tCleaning frequency: " << this->cleanFreq;
    cout << endl << "Received food: " << this->foodReceived;
    cout << "\tHabitat cleaned: " << this->habCleaned;
    cout << endl << "Last time food : " << this->foodLT;
    cout << "\tLast time cleaned: " << this->cleanLT << endl;

}
