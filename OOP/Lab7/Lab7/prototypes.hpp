//
//  prototypes.hpp
//  Lab6
//
//  Created by Kushka Misha on 12/6/17.
//  Copyright © 2017 Kushka Misha. All rights reserved.
//

#ifndef prototypes_hpp
#define prototypes_hpp

#include "stdafx.hpp"

/**
 * Patient class
 */
class Patient {
    string name;
    string surname;
    string sex;
    int age;
    int id;
public:
    Patient(string _name, string _surname, int _age, string _sex, int _id) :
    name(_name), surname(_surname),age(_age), sex(_sex), id(_id) {};
    
    void getPatientInfo();
};

/**
 * Disease class
 */
class Disease {
    string appellation;
    string treatment;
    float cost;
public:
    Disease(string _appellation, string _treatment, float _cost) :
    appellation(_appellation), treatment(_treatment), cost(_cost) {};
    
    void getDiseaseInfo();
    float getCost();
};

/**
 * Doctor class
 */
class Doctor {
    int id;
    string name;
    string surname;
    int numberOfPatients;
    float profit;
public:
    Doctor(int _id, string _name, string _surname, int _numberOfPatients=0, float _profit=0) :
    id(_id), name(_name), surname(_surname),numberOfPatients(_numberOfPatients), profit(_profit) {};
    
    void getDoctorInfo();
    int getId();
    int getNumberOfPatients();
    float getProfit();
    
    void increaseNumberOfPatients();
    void increaseProfit(float);
};

/**
 * DoctorId class
 */
class DoctorId {
    int id;
public:
    DoctorId(int _id) : id(_id) {};
    
    int getDoctorId() {
        return id;
    }
};

/**
 * Variational template class
 */
template<class... Infos>
class Group : public Infos...
{
public:
    Group(const Infos&&... infos) : Infos(infos)... {};
};

#endif /* prototypes_hpp */

