#pragma once
#include <string>
#include <stdexcept>

class InsurancePolicy {
private:
    int policyNo;
    std::string vehicleReg;
    std::string startDate;
    std::string endDate;
    double premium;
    double coverageAmount;

public:
    InsurancePolicy() : policyNo(0), premium(0.0), coverageAmount(0.0) {}

    InsurancePolicy(int no, const std::string& vReg, const std::string& start,
                    const std::string& end, double p, double c)
        : policyNo(no), vehicleReg(vReg), startDate(start), 
          endDate(end) {
        setPremium(p);
        setCoverageAmount(c);
    }
          
    // Getters
    int getPolicyNo() const { return policyNo; }
    std::string getVehicleReg() const { return vehicleReg; }
    std::string getStartDate() const { return startDate; }
    std::string getEndDate() const { return endDate; }
    double getPremium() const { return premium; }
    double getCoverageAmount() const { return coverageAmount; }

    // Setters
    void setPolicyNo(int val) { policyNo = val; }
    void setVehicleReg(const std::string& val) { vehicleReg = val; }
    void setStartDate(const std::string& val) { startDate = val; }
    void setEndDate(const std::string& val) { endDate = val; }
    
    void setPremium(double val) { 
        if (val < 0) throw std::runtime_error("Premium cannot be negative.");
        premium = val; 
    }
    
    void setCoverageAmount(double val) { 
        if (val < 0) throw std::runtime_error("Coverage amount cannot be negative.");
        coverageAmount = val; 
    }

    std::string escape(std::string str) const {
        for (char& c : str) if (c == ',') c = ';';
        return str;
    }

    std::string serialize() const {
        return std::to_string(policyNo) + "," + 
               escape(vehicleReg) + "," + 
               escape(startDate) + "," + 
               escape(endDate) + "," + 
               std::to_string(premium) + "," + 
               std::to_string(coverageAmount);
    }
};
