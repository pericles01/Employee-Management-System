#include "Employee.h"
#include <iostream>


Record::Employee::Employee(const std::string& firstName, const std::string& lastName, const std::string& profession, const uint32_t& ID, const bool& isFullTime): mFirstName(firstName), mLastName(lastName), mProfession(profession), mEmployeeNumber(ID),mIsFull(isFullTime)
{
}

void Record::Employee::setFirstName(const std::string &firstName)
{
    mFirstName = firstName;
}

const std::string &Record::Employee::getFirstName() const
{
    return mFirstName;
}

void Record::Employee::setLastName(const std::string &lastName)
{
    mLastName = lastName;
}

const std::string &Record::Employee::getLastName() const
{
    return mLastName;
}

void Record::Employee::setProfession(const std::string& profession)
{
    mProfession = profession;
}

const std::string& Record::Employee::getProfession() const
{
    return mProfession;
}

void Record::Employee::setEmployeeNumber(const uint32_t &employeeNumber)
{
    mEmployeeNumber = employeeNumber;
}

const uint32_t &Record::Employee::getEmployeeNumber() const
{
    return mEmployeeNumber;
}

void Record::Employee::setSalary(const uint32_t &salary)
{
    mSalary = salary;
}

const uint32_t &Record::Employee::getSalary() const
{
    return mSalary;
}

void Record::Employee::setPeriod(const bool& full) {
    mIsFull = full;
}

const bool& Record::Employee::getPeriod() const {
    return mIsFull;
}

void Record::Employee::promote(const uint32_t &raiseAmount)
{
    uint32_t newSalary = getSalary() + raiseAmount;
    setSalary(newSalary);
}

void Record::Employee::demote(const uint32_t &demeritAmount)
{
    uint32_t newSalary = getSalary() - demeritAmount;
    setSalary(newSalary);
}

void Record::Employee::fire()
{
    uint32_t newSalary = 0;
    setSalary(newSalary);
}

void Record::Employee::hire()
{
    uint32_t newSalary = Record::kDedaultStartingSalary;
    setSalary(newSalary);
}

const bool &Record::Employee::isFull() const
{
    return mIsFull;
}

void Record::Employee::display() const
{
    std::cout << "Employee Id: " << getEmployeeNumber() << std::endl;
    std::cout << "First name: " << getFirstName() << std::endl;
    std::cout << "Last name: " << getLastName() << std::endl;
    std::cout << "Profession: " << getProfession() << std::endl;
    std::cout << "Current salary: " << getSalary() << " Eur" << std::endl;
    std::cout << "Type: "<<(isFull() ? "Full time Employee" : "Part time Employee") << std::endl;
}

//template <class T>
bool Record::Employee::operator == (const Employee& c)
{
    if (this->getFirstName() == c.getFirstName() && this->getLastName() == c.getLastName() && this->getEmployeeNumber() == c.getEmployeeNumber())
        return true;
    else
        return false;
}
