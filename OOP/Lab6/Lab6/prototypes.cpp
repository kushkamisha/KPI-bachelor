//
//  prototypes.cpp
//  Lab6
//
//  Created by Kushka Misha on 12/6/17.
//  Copyright © 2017 Kushka Misha. All rights reserved.
//

#include "prototypes.hpp"

// display all data from Patient class
void Patient::getPatientInfo() {
    cout << "========== Patient ==========" << endl
         << "=============================" << endl
         << "Name: " << name << endl
         << "Surname: " << surname << endl
         << "Age: " << age << endl
         << "Sex: " << sex << endl << endl;
}

// display all data from Disease class
void Disease::getDiseaseInfo() {
    cout << "========== Disease ==========" << endl
         << "=============================" << endl
         << "Appellation: " << appellation << endl
         << "Treatment: " << treatment << endl
         << "Cost: " << cost << endl << endl;
}

// get cost from Disease class
float Disease::getCost() {
    return cost;
}

// display all data from Doctor class
void Doctor::getDoctorInfo() {
    cout << "========== Doctor ===========" << endl
         << "=============================" << endl
         << "Name: " << name << endl
         << "Surname: " << surname << endl
         << "Number of patients: " << numberOfPatients << endl
    << "Profit: " << profit << endl << endl;
}

// get doctor's id
int Doctor::getId() {
    return id;
}

// get Doctor's number of patients
int Doctor::getNumberOfPatients() {
    return numberOfPatients;
}

// get Doctor's profit
float Doctor::getProfit() {
    return profit;
}

// increase Doctor number of patients by 1
void Doctor::increaseNumberOfPatients() {
    numberOfPatients += 1;
}

// Increase Doctor profit by value
void Doctor::increaseProfit(float additionalProfit) {
    profit += additionalProfit;
}
