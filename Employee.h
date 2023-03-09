#pragma once
#include <cstdlib>
#include <string>


namespace Record
{
constexpr uint32_t kDedaultStartingSalary = 30000U;

class Employee
{
public:
    Employee() = default;
    Employee(const std::string& firstName, const std::string& lastName, const std::string& profession, const uint32_t& ID = 0, const bool & isFullTime = true);

    void promote(const uint32_t &raiseAmount);
    void demote(const uint32_t &demeritAmount);
    void fire();
    void hire();
    void display() const;

    void setFirstName(const std::string &lastName);
    const std::string &getFirstName() const;
    void setLastName(const std::string &lastName);
    const std::string &getLastName() const;
    void setProfession(const std::string& prfession);
    const std::string& getProfession() const;
    void setEmployeeNumber(const uint32_t &employeeNumber);
    const uint32_t &getEmployeeNumber() const;
    void setSalary(const uint32_t &salary);
    const uint32_t &getSalary() const;
    void setPeriod(const bool &full);
    const bool& getPeriod() const;
    const bool &isFull() const;
    //template <class T>
    bool operator == (const Employee& c);


private:
    std::string mFirstName;
    std::string mLastName;
    std::string mProfession;
    uint32_t mSalary = kDedaultStartingSalary;
    uint32_t mEmployeeNumber;
    bool mIsFull = false;
};
} // namespace Record
