#pragma once
#include <string>

class InspectionReport {
private:
    int reportId;
    int claimId;
    int surveyorId;
    std::string date;
    std::string description;
    double estimatedCost;

    std::string escape(std::string str) const {
        for (char& c : str) if (c == ',') c = ';';
        return str;
    }

public:
    InspectionReport() : reportId(0), claimId(0), surveyorId(0), estimatedCost(0.0) {}

    InspectionReport(int rId, int cId, int sId, const std::string& d,
                     const std::string& desc, double cost)
        : reportId(rId), claimId(cId), surveyorId(sId),
          date(d), description(desc), estimatedCost(cost) {}
          
    // Getters
    int getReportId() const { return reportId; }
    int getClaimId() const { return claimId; }
    int getSurveyorId() const { return surveyorId; }
    std::string getDate() const { return date; }
    std::string getDescription() const { return description; }
    double getEstimatedCost() const { return estimatedCost; }

    // Setters
    void setReportId(int val) { reportId = val; }
    void setClaimId(int val) { claimId = val; }
    void setSurveyorId(int val) { surveyorId = val; }
    void setDate(const std::string& val) { date = val; }
    void setDescription(const std::string& val) { description = val; }
    void setEstimatedCost(double val) { estimatedCost = val; }

    std::string serialize() const {
        return std::to_string(reportId) + "," + 
               std::to_string(claimId) + "," + 
               std::to_string(surveyorId) + "," + 
               escape(date) + "," + 
               escape(description) + "," + 
               std::to_string(estimatedCost);
    }
};
