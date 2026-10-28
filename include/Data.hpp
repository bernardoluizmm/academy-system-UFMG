#ifndef DATA_HPP
#define DATA_HPP

#include <string>
#include <ostream>

class Data 
{
private:
    std::string _data;
    int _dia;
    int _mes;

    void validarData(int dia, int mes);

public:
    Data(const std::string& dataInput);
    Data() = default; 

    std::string getDataValidada() const;

    bool operator<(const Data& outra) const;

    friend std::ostream& operator<<(std::ostream& os, const Data& d);
};

#endif