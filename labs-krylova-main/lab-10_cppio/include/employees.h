#ifndef LAB10_EMPLOYEES_H_INCLUDED
#define LAB10_EMPLOYEES_H_INCLUDED

#include "bin_manip.h"
#include <stdint.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <istream>
#include <ostream>
#include <fstream>

namespace Employee {


    class Employee {

    public:
        Employee(const char *name, int32_t base_salary);

        Employee();

        virtual ~Employee();

        virtual int32_t salary() const = 0;

        virtual std::istream &read_text(std::istream &in);

        virtual std::ifstream &read_binary(std::ifstream &in);

        virtual std::ostream &write_text(std::ostream &out) const;

        virtual std::ofstream &write_binary(std::ofstream &out) const;


        friend std::istream &operator>>(std::istream &in, Employee &e);

        friend std::ifstream &operator>>(std::ifstream &in, Employee &e);

        friend std::ostream &operator<<(std::ostream &out, const Employee &e);

        friend std::ofstream &operator<<(std::ofstream &out, const Employee &e);


    protected:
        int32_t _base_salary;
        char *_name;
    };

    class Developer : public Employee {
    public:
        Developer(const char *name, int32_t base_salary, bool has_bonus);

        Developer();

        int32_t salary() const override {
            int salary = _base_salary;
            if (_has_bonus) {
                salary += 1000;
            }
            return salary;
        }

        Developer(std::istream &in);

        Developer(std::ifstream &in);

        virtual std::istream &read_text(std::istream &in) override;

        virtual std::ifstream &read_binary(std::ifstream &in) override;

        virtual std::ostream &write_text(std::ostream &out) const override;

        virtual std::ofstream &write_binary(std::ofstream &out) const override;

        /* ?? operator>>(??); */
        /* ?? operator<<(??); */
    private:
        bool _has_bonus;
    };

    class SalesManager : public Employee {
    public:
        SalesManager(const char *name, int32_t base_salary, int32_t sold_nm, int32_t price);

        SalesManager();

        SalesManager(std::istream &in);

        SalesManager(std::ifstream &in);

        int32_t salary() const override {
            return _base_salary + _sold_nm * _price * 0.01;
        }
        /* ?? operator>>(??); */
        /* ?? operator<<(??); */
        virtual std::istream &read_text(std::istream &in) override;

        virtual std::ifstream &read_binary(std::ifstream &in) override;

        virtual std::ostream &write_text(std::ostream &out) const override;

        virtual std::ofstream &write_binary(std::ofstream &out) const override;


    private:
        int32_t _sold_nm, _price;
    };

    class EmployeesArray {
    public:
        EmployeesArray();

        ~EmployeesArray();

        void add(const Employee *e);

        int32_t total_salary() const;

        /* ?? operator>>(??); */
        /* ?? operator<<(??); */
        friend std::istream &operator>>(std::istream &in, EmployeesArray &array);

        friend std::ifstream &operator>>(std::ifstream &in, EmployeesArray &array);

        friend std::ostream &operator<<(std::ostream &out, const EmployeesArray &array);

        friend std::ofstream &operator<<(std::ofstream &out, const EmployeesArray &array);

    private:
        std::vector<Employee *> _employees;
        int32_t _size;
    };

}

#endif
