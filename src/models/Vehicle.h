#pragma once
#include <string>

class Vehicle {
private:
    std::string regNumber;
    std::string make;
    std::string model;
    int year;
    int customerId;

    std::string escape(std::string str) const {
        for (char& c : str) if (c == ',') c = ';';
        return str;
    }

public:
    Vehicle() : year(0), customerId(0) {}

    Vehicle(const std::string& regNo, const std::string& make, 
            const std::string& model, int year, int customerId)
        : regNumber(regNo), make(make), model(model), 
          year(year), customerId(customerId) {}
          
    // Getters
    std::string getRegNumber() const { return regNumber; }
    std::string getMake() const { return make; }
    std::string getModel() const { return model; }
    int getYear() const { return year; }
    int getCustomerId() const { return customerId; }

    // Setters
    void setRegNumber(const std::string& val) { regNumber = val; }
    void setMake(const std::string& val) { make = val; }
    void setModel(const std::string& val) { model = val; }
    void setYear(int val) { year = val; }
    void setCustomerId(int val) { customerId = val; }

    std::string serialize() const {
        return escape(regNumber) + "," + 
               escape(make) + "," + 
               escape(model) + "," + 
               std::to_string(year) + "," + 
               std::to_string(customerId);
    }
};
