#pragma once
#include <string>

class InsurancePolicy {
private:
    int policyNo;
    std::string vehicleReg;
    std::string startDate;
    std::string endDate;
    double premium;
    double coverageAmount;

    std::string escape(std::string str) const {
        for (char& c : str) if (c == ',') c = ';';
        return str;
    }

public:
    InsurancePolicy() : policyNo(0), premium(0.0), coverageAmount(0.0) {}

    InsurancePolicy(int no, const std::string& vReg, const std::string& start,
                    const std::string& end, double p, double c)
        : policyNo(no), vehicleReg(vReg), startDate(start), 
          endDate(end), premium(p), coverageAmount(c) {}
          
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
    void setPremium(double val) { premium = val; }
    void setCoverageAmount(double val) { coverageAmount = val; }

    std::string serialize() const {
        return std::to_string(policyNo) + "," + 
               escape(vehicleReg) + "," + 
               escape(startDate) + "," + 
               escape(endDate) + "," + 
               std::to_string(premium) + "," + 
               std::to_string(coverageAmount);
    }
};
