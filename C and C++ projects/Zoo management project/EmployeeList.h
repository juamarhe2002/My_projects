//
// Created by juanm on 24/04/2022.
//

#ifndef PRELIMINARY_PROYECT_EMPLOYEELIST_H
#define PRELIMINARY_PROYECT_EMPLOYEELIST_H

#include "Employee.h"
#include "AnimalHab.h"

class EmployeeList {
private:

    /**
     * @brief Structure that manages the node of Employees.
     *
     * @param employee pointer to current employee.
     * @param designAnimal pointer to the designated animal of the employee.
     * @param habNum Number of the habitat of the animal.
     * @param next pointer to next node.
     */
    struct EmployeeNode {
        int ID;
        Employee* employee;

        int habNum;
        AnimalHab* designAnimal;

        EmployeeNode* next;
    };

    EmployeeNode* head; // Head of the list.

    /**
     * @brief Checks the order of an ID given with respect to a node.
     *
     * @param curr Pointer to current node.
     * @param curr_next Pointer to next node.
     * @param IDEmployee ID checked.
     * @return int Returns number according to the position where the ID
     * should be ordered with respect to the given node.
     */
    int chk_IDOrder(EmployeeNode* curr, EmployeeNode* curr_next, int IDEmployee);

    /**
     * @brief Checks if the current employee should be the one notified.
     *
     * @param curr Pointer to curr node.
     * @param habitatNum Habitat number where the job wasn't done.
     * @return bool Returns true if it should be notified, returns false otherwise.
     */
    bool chk_ifnotifyEmp(EmployeeNode* curr, int currDay);

    int chk_notifications(EmployeeNode* &curr, EmployeeNode* &prev);

    bool findEmployee(int IDEmployee, EmployeeNode*& curr, EmployeeNode*& previous) const;

    bool findHabAnimal(int habNum, EmployeeNode*& curr, EmployeeNode*& prev) const;

    void addEmployee_inOrder(Employee* newEmployee, EmployeeNode* curr, int c);

    void removeNode(EmployeeNode*& curr, EmployeeNode*& prev);

public:
    /**
     * @brief Constructor of an EmployeeList.
     * Initializes the head to nullptr.
     */
    EmployeeList();
    ~EmployeeList(); // Destructor of an Employee List.
    EmployeeList(const EmployeeList& copiedList);
    EmployeeList& operator=(const EmployeeList& assignList);
    int designatedAnimal(int IDEmployee);

    int get_numEmployees();

    /**
     * @brief Checks if the name or ID of an employee aren't repeated in the list.
     *
     * @param IDEmployee ID of the Employee.
     * @param name Name of the Employee
     * @return bool Returns true if the credentials given doesn't exist on the list, returns false otherwise.
     */
    bool chk_Credentials(int IDEmployee, const char* name);

    /**
     * @brief Adds a new employee to the list.
     * Checks if the name or the ID aren't repeated.
     * Reporting the reason why it cannot add the employee in case it happens.
     *
     * @param IDEmployee ID of the new employee.
     * @param name Name of the new employee.
     * @param Occupation Occupation of the new employee.
     */
    void addEmployee(int IDEmployee, const char* name, const char* Occupation);

    void insertEmployee(Employee* newEmployee);

    /**
     * @brief Assigns an animal to an existent employee.
     * If it does not find the employee, it returns an error message.
     *
     * @param IDEmployee ID of the employee.
     * @param designAnimal Pointer to the animal that will be assigned.
     */
    bool assignAnimal(int IDEmployee, AnimalHab* designAnimal);

    bool chk_assignPossibletoEmployee(int IDEmployee);

    Employee* ret_assignEmployee(int IDEmployee);

    int EmployeeOccupation(int IDEmployee);

    /**
     * @brief Removes an employee from the list.
     *
     * @param IDEmployee ID of the employee.
     */
    int removeEmployee(int IDEmployee);

    /**
     * @brief Checks the amount of notifications and decides whether or not to fire it.
     * If it fires it, it will get removed from the list.
     *
     * @param curr Pointer to employee.
     */
    int chk_allEmployees();

    /**
     * @brief Prints the list of Employees.
     */
    void print();

    int get_headEmpID();
    int get_nextEmployee(int IDEmployee);

    /**
     * @brief Feeds an animal according to a specified employee.
     * Checks if the ID corresponds to a Caretaker.
     * If it is, it feeds the animals, otherwise it returns an error message.
     *
     * @param IDEmployee ID of the employee.
     * @param currDay Day of feeding.
     * @param amount Amount of food given to the animal.
     */
    bool feed(int IDEmployee, int currDay, int amount);

    bool allFeed(int currDay, int amount);

    /**
     * @brief Cleans the habitat of an animal according to a specified employee.
     * Checks if the ID corresponds to a Cleaner.
     * If it is, it cleans the habitat, otherwise it returns an error message.
     *
     * @param IDEmployee ID of the employee.
     * @param currDay Day of cleaning.
     * @param amount Amount of time it was cleaned.
     */
    bool clean(int IDEmployee, int currDay, int amount);

    bool allClean(int currDay, int amount);

    /**
     * @brief Searches and notifies an employees according to the undone job in an habitat.
     *
     * @param habitatNum Number of the habitat with an undone job.
     * @param currDay Current day of the observation.
     */
    void notify(int habitatNum, int currDay);

    void chk_forKilledEmployee(int IDEmployee);
    void deassignateAnimal(int habitatNum);

};


#endif //PRELIMINARY_PROYECT_EMPLOYEELIST_H
