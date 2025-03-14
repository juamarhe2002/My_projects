//
// Created by juanm on 5/05/2022.
//

#ifndef PRELIMINARY_PROYECT_TESTCASES_H
#define PRELIMINARY_PROYECT_TESTCASES_H

#include "Zoo.h"

void testAll_EmployeeList();

void testBasicAnimalList();

//Tests Zoo.

bool TestZoo_numberElements(Zoo Auto, Zoo* DynC);

bool TestZoo_wrongHireEmployee(Zoo Auto, Zoo* Dyn);

bool TestZoo_fireEmployee(Zoo Auto, Zoo* DynC);

bool TestZoo_wrongNewAnimalHabitat(Zoo Auto, Zoo* DynC);

bool TestZoo_removeAnimalHabitat(Zoo Auto, Zoo* Dyn);

bool TestZoo_assignAnimalEmployee(Zoo &Auto, Zoo* &Dyn);

bool TestZoo_feeding(Zoo Auto, Zoo* DynC);

bool TestZoo_cleaning(Zoo Auto, Zoo* DynC);

bool TestZoo_DayPasses(Zoo Auto, Zoo *DynC);

bool TestZoo_AnimalsCondition(Zoo Auto, Zoo* DynC);

// Tests Animals Conditions

bool TestAnimalsCondition_normalDay(Zoo Auto, Zoo* DynC);

bool TestAnimalsCondition_notifyCaretaker(Zoo Auto, Zoo* DynC);

bool TestAnimalsCondition_notifyCleaner(Zoo Auto, Zoo* DynC);

bool TestAnimalsCondition_killCaretaker(Zoo Auto, Zoo* DynC);

bool TestAnimalsCondition_escapedAnimal(Zoo Auto, Zoo* DynC);

#endif //PRELIMINARY_PROYECT_TESTCASES_H
