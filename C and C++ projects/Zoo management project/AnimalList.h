//
// Created by juanm on 24/04/2022.
//

#ifndef PRELIMINARY_PROYECT_ANIMALLIST_H
#define PRELIMINARY_PROYECT_ANIMALLIST_H

#include "AnimalHab.h"
#include "Employee.h"

class AnimalList {
private:

    /**
     * @brief Structure that manages the node in the AnimalList.
     *
     * @param animal Pointer to current animal.
     * @param Caretaker Pointer to Caretaker assigned to current animal.
     * @param next Pointer to next node.
     */
    struct AnimalNode {
        AnimalHab* animal;
        Employee* Caretaker;

        AnimalNode* next;
    };

    AnimalNode* head; // Head of the list.

    /**
     * @brief Checks the order of a given habitat number with respect to a node.
     *
     * @param curr Pointer to current node.
     * @param curr_next Pointer to next node.
     * @param habitatNum Habitat number checked.
     * @return int Returns number according to the position of where the given habitat
     *  number should be ordered with respect to given node.
     */
    int chk_habitat(AnimalNode* curr, AnimalNode* curr_next, int habitatNum);

    /**
     * @brief Checks the conditions of a given animal according to current day.
     *
     * @param animal Pointer to current animal.
     * @param currDay Current Day.
     * @return int Returns 0 if the animal is ok, otherwise it returns the habitat number of the animal.
     */
    static int chk_AnimalFood(AnimalNode* curr, int currDay);

    static int chk_AnimalClean(AnimalNode* curr, int currDay);

    bool findHabitat(int habNum , AnimalNode*& curr, AnimalNode*& prev);

    void removeNode(AnimalNode*& curr, AnimalNode*& prev);

    void addHabitat_inOrder(AnimalHab* newHabitat, AnimalNode* curr, int c);

    void insertHab(AnimalHab* newHab);

public:

    /**
     * @brief Constructor of an AnimalList
     * Initializes  the head to nullptr.
     */
    AnimalList();
    ~AnimalList(); // Destructor of an AnimalList.
    AnimalList(const AnimalList& copiedList);
    AnimalList& operator=(const AnimalList& assignList);

    int get_numAnimalHab();

    /**
     * @brief Adds an new animal to the list.
     * Checks if the habitat number doesn't exists.
     * In case it does an error message is displayed.
     *
     * @param habitatNum Habitat number.
     * @param Species Species (name) of the animal.
     * @param foodFreq Food frequency.
     * @param cleanFreq Cleaning frequency.
     * @param day Day of addition.
     */
    void addAnimalHab(int habitatNum, const char* Species, int foodFreq, int cleanFreq, int day);

    void addAnimalHab(AnimalHab* habitat);

    int removeAnimalHabitat(int habitatNum);

    /**
     * @brief Removes an animal when it escapes according to its habitat number.
     *
     * @param habitatNum Habitat number of the animal that escapes.
     */
    void AnimalEscapes(int habitatNum);

    /**
     * @brief Removes a Caretaker of an animal.
     *
     * @param curr Pointer to node where the animal kills.
     */
    int AnimalKills(int habitatNum);

    /**
     * @brief Sets a Caretaker to an animal.
     *
     * @param habitatNum Habitat number of the animal.
     * @param caretaker Caretaker assigned.
     */
    bool set_Caretaker(int habitatNum, Employee* caretaker);

    AnimalHab* ret_assignAnimalHab(int habitatNum);

    bool deassignCaretaker(int habNum);

    int get_numHabHead();

    int get_nextAnimalHab(int currHab);

    /**
     * @brief Check the condition of all the animals in the list.
     * It will show a message if it finds an animal that is not in good condition.
     *
     * @param currDay Current day for comparison.
     * @return int Returns the habitat number of the animal in bad conditions.
     */
    int chk_AnimalsCondition(int habNum, int currDay);

    int case_AnimalCondition(int habNum, int currDay, int k);

    void new_day(int currDay);

    /**
     * @brief Prints the list of animals.
     */
    void print();

};


#endif //PRELIMINARY_PROYECT_ANIMALLIST_H
