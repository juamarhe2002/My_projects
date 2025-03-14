//
// Created by juanm on 23/04/2022.
//

#ifndef PRELIMINARY_PROYECT_EMPLOYEE_H
#define PRELIMINARY_PROYECT_EMPLOYEE_H

#include "AnimalHab.h"

class Employee {
private:
    int IDEmployee; // ID of an employee.
    char* name; // Name of the employee.
    char* Occupation; // Occupation of the employee.
    int notifications; // Amount of notifications the employee has.

public:
    /**
     * It initializes the attributes of the employee with these parameters.
     * The number of notifications its initialized to 0.
     *
     * @brief Constructor of an Employee.
     *
     * @param IDEmployee
     * @param name
     * @param Occupation
     */
    Employee(int IDEmployee, const char* name, const char* Occupation);
    ~Employee(); // Destructor of an Employee.
    Employee(const Employee& copiedEmployee);

    /**
     * Gets the ID of an employee.
     *
     * @return int ID of an employee.
     */
    int get_IDEmployee()const;

    /**
     * Gets the name of an employee.
     *
     * @return const char* Name of the employee.
     */
    const char* get_name() const;

    /**
     * Gets the occupation of an employee.
     *
     * @return const char* Occupation of an employee.
     */
    const char* get_Occupation() const;

    /**
     * Gets the amount of notification of an employee.
     *
     * @return int Amount of notifications of an employee.
     */
    int & get_notifications();

    /**
     * Prints the information of an employee.
     */
    void print();

};


#endif //PRELIMINARY_PROYECT_EMPLOYEE_H
