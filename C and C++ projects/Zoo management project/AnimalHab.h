//
// Created by juanm on 23/04/2022.
//

#ifndef PRELIMINARY_PROYECT_ANIMALHAB_H
#define PRELIMINARY_PROYECT_ANIMALHAB_H

#include "Employee.h"

class AnimalHab {
private:
    int habitatNum; // Habitat number in which the animal lives.
    char* Species; // Species (name) of the animal.
    int foodReceived; // How many times it has received food in the period.
    int habCleaned; // How many times its habitat has been cleaned in the period.
    int foodFreq; // Food frequency.
    int cleanFreq; // Cleaning frequency of the habitat.
    int foodLT; // Last time the animal received food.
    int cleanLT; // Last time its habitat was cleaned.

public:
    /**
     * It will be initialized with the values passed down as parameters.
     * The parameters: foodLT and cleanLT will be initialized with the
     * day of creation of the new AnimalHab.
     *
     * @brief Constructor of an AnimalHab.
     *
     * @param habitatNum Number of the habitat in which the animal will live.
     * @param Species Name of the animal species.
     * @param foodFreq Food frequency.
     * @param cleanFreq Cleaning frequency.
     * @param day Day of addition.
     */
    AnimalHab(int habitatNum, const char* Species, int foodFreq, int cleanFreq, int day);
    ~AnimalHab(); // Destructor of an AnimalHab.
    AnimalHab(const AnimalHab& copiedAnimal);

    /**
     * Gets the habitat number of an animal.
     *
     * @return int the habitat number of an animal.
     */
    int get_habitatNo() const;

    /**
     * Gets the species of an animal.
     *
     * @return const char* the species of an animal.
     */
    const char* get_Species() const;

    /**
     * Gets the amount of food received.
     *
     * @return int the amount of food received.
     */
    int get_foodReceived() const;

    /**
     * Sets the amount of food received.
     *
     * @param amount Amount of food received.
     */
    void set_foodReceived(int amount);

    /**
     * Gets the amount of times the habitat was cleaned.
     *
     * @return int the amount of times it was cleaned.
     */
    int get_habitatCleaned() const;

    /**
     * Sets the amount of times it was cleaned.
     *
     * @param amount Amount of times its cleaned.
     */
    void set_habitatCleaned(int amount);

    /**
     * Sets when it received food.
     *
     * @param actualDay day in which received food.
     */
    void set_foodLastTime(const int actualDay);

    /**
     * Sets the last time the habitat was cleaned
     *
     * @param actualDay Day in which is cleaned.
     */
    void set_cleanLastTime(const int actualDay);

    int chk_food(int currDay) const;

    bool chk_foodPeriod(int currDay) const;

    int chk_cleaning(int currDay) const;

    bool chk_cleaningPeriod(int currDay) const;

    /**
     * Prints the information of an AnimalHab.
     */
    void print();

};


#endif //PRELIMINARY_PROYECT_ANIMALHAB_H
