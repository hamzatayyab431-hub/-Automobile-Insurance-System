#pragma once
#include <string>

class Claim {
private:
    int claimId;
    int policyNo;
    std::string date;
    std::string description;
    std::string status;
    std::string approvalReason;
    int workshopId;

    std::string escape(std::string str) const {
        for (char& c : str) if (c == ',') c = ';';
        return str;
    }

public:
    Claim() : claimId(0), policyNo(0), workshopId(0) {}

    Claim(int cId, int pNo, const std::string& d, const std::string& desc,
          const std::string& stat, const std::string& appReason, int wId)
        : claimId(cId), policyNo(pNo), date(d), description(desc),
          status(stat), approvalReason(appReason), workshopId(wId) {}

    // Getters and Setters
    int getClaimId() const { return claimId; }
    void setClaimId(int id) { claimId = id; }
    
    int getPolicyNo() const { return policyNo; }
    std::string getDate() const { return date; }
    std::string getDescription() const { return description; }
    std::string getStatus() const { return status; }
    std::string getApprovalReason() const { return approvalReason; }
    int getWorkshopId() const { return workshopId; }

    // State / Business Logic modifiers
    void inspect() { status = "Inspected"; }
    void approve(const std::string& reason) { 
        status = "Approved"; 
        approvalReason = reason; 
    }
    void reject(const std::string& reason) { 
        status = "Rejected"; 
        approvalReason = reason; 
    }

    std::string serialize() const {
        return std::to_string(claimId) + "," + std::to_string(policyNo) + "," + 
               escape(date) + "," + escape(description) + "," + escape(status) + "," + 
               escape(approvalReason) + "," + std::to_string(workshopId);
    }
};