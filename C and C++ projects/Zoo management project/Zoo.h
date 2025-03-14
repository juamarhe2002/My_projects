//
// Created by juanm on 24/04/2022.
//

#ifndef PRELIMINARY_PROYECT_ZOO_H
#define PRELIMINARY_PROYECT_ZOO_H

#include "AnimalList.h"
#include "EmployeeList.h"


class Zoo {
private:

    /**
     * @brief Lists for the management of the list of animals and employees.
     *
     * @param animalList List of animals of the Zoo
     * @param employeeList List of employees of the Zoo.
     */
    AnimalList* animalList;
    EmployeeList* employeeList;

    int currDay; // Current day in the Zoo. (cannot be negative or a previous day)

    static bool chk_Occupation(const char* Occupation);

public:
    /**
     * @brief Constructor of a Zoo.
     * Initializes lists to nullptr and current day to 0.
     */
    Zoo();
    ~Zoo();//Destructor of a Zoo.
    Zoo(const Zoo &copiedZoo);

    /**
     * @brief Gets the current day of the Zoo.
     *
     * @return int Returns the day in the Zoo.
     */
    int get_currDay() const;

    /**
     * @brief Sets the current day at the Zoo.
     * If the value is lower than the previous one, an error message will be displayed.
     *
     * @param Day New day.
     */
    void set_currDay(int Day);

    int get_numberElements();

    /**
     * @brief Hires a new employee.
     * An error message is displayed if the Occupation is not specified properly.
     *
     * @param IDEmployee ID of the new employee.
     * @param name Name of the new employee.
     * @param Occupation Occupation of the new employee.
     */
    void hireEmployee(int IDEmployee, const char* name, const char* Occupation);

    void fireEmployee(int IDEmployee);

    /**
     * @brief A new animal is added to the Zoo.
     * An error message is displayed if the food or cleaning frequencies are not displayed properly.
     *
     * @param habitatNum Habitat number of the new AnimalHab.
     * @param Species Species (name) of the animal.
     * @param foodFreq Food Frequency.
     * @param cleanFreq Cleaning Frequency.
     */
    void newAnimalHabitat(int habitatNum, const char* Species, int foodFreq, int cleanFreq);

    void removeAnimalHabitat(int habitatNum);

    void assignAnimalEmployee(int habitatNum, int IDEmployee);

    /**
     * @brief Makes all employees allowed, to feed animals.
     *
     * @param amount Current day when they do that.
     */
    void workFeeding(int amount);

    void employeeFeeds(int IDEmployee, int amount);

    /**
     * @brief Makes all employees allowed, to clean habitats.
     *
     * @param amount Current day when they do that
     */
    void workCleaning(int amount);

    void employeeCleans(int IDEmployee, int amount);

    /**
     * @breif Checks the condition of all animals in the Zoo.
     * If an animal is in bad condition, a message will be displayed
     * and a notification to the employee will be issued.
     *
     * @param day Current day at the Zoo.
     */
    void AnimalsCondition(int day);

    void DayPasses(int newDay);

    void print();

};


#endif //PRELIMINARY_PROYECT_ZOO_H
