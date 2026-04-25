#pragma once
#include <string>
#include <stdexcept>

class Claim;

// --- State Interface ---
class ClaimState {
public:
    virtual ~ClaimState() = default;
    virtual std::string getStatusName() const = 0;
    virtual void inspect(Claim* claim);
    virtual void approve(Claim* claim, const std::string& reason);
    virtual void reject(Claim* claim, const std::string& reason);
};

// --- Concrete States Declaration ---
class PendingState : public ClaimState {
public:
    std::string getStatusName() const override { return "Pending"; }
    void inspect(Claim* claim) override;
    void approve(Claim* claim, const std::string& reason) override;
    void reject(Claim* claim, const std::string& reason) override;
};

class InspectedState : public ClaimState {
public:
    std::string getStatusName() const override { return "Inspected"; }
    void approve(Claim* claim, const std::string& reason) override;
    void reject(Claim* claim, const std::string& reason) override;
};

class ApprovedState : public ClaimState {
public:
    std::string getStatusName() const override { return "Approved"; }
};

class RejectedState : public ClaimState {
public:
    std::string getStatusName() const override { return "Rejected"; }
};

// --- Claim Class ---
class Claim {
private:
    int claimId;
    int policyNo;
    std::string date;
    std::string description;
    ClaimState* currentState;
    std::string approvalReason;
    int workshopId;

public:
    Claim(int cId, int pNo, const std::string& d, const std::string& desc, 
          const std::string& status, const std::string& reason, int wId)
        : claimId(cId), policyNo(pNo), date(d), description(desc), approvalReason(reason), workshopId(wId) {
        if (status == "Inspected") currentState = new InspectedState();
        else if (status == "Approved") currentState = new ApprovedState();
        else if (status == "Rejected") currentState = new RejectedState();
        else currentState = new PendingState();
    }

    ~Claim() { delete currentState; }

    // Rule of Three
    Claim(const Claim& other) : claimId(other.claimId), policyNo(other.policyNo), date(other.date),
                                description(other.description), approvalReason(other.approvalReason),
                                workshopId(other.workshopId) {
        std::string status = other.getStatus();
        if (status == "Inspected") currentState = new InspectedState();
        else if (status == "Approved") currentState = new ApprovedState();
        else if (status == "Rejected") currentState = new RejectedState();
        else currentState = new PendingState();
    }

    Claim& operator=(const Claim& other) {
        if (this != &other) {
            delete currentState;
            claimId = other.claimId;
            policyNo = other.policyNo;
            date = other.date;
            description = other.description;
            approvalReason = other.approvalReason;
            workshopId = other.workshopId;
            std::string status = other.getStatus();
            if (status == "Inspected") currentState = new InspectedState();
            else if (status == "Approved") currentState = new ApprovedState();
            else if (status == "Rejected") currentState = new RejectedState();
            else currentState = new PendingState();
        }
        return *this;
    }

    // Getters
    int getClaimId() const { return claimId; }
    int getPolicyNo() const { return policyNo; }
    std::string getDate() const { return date; }
    std::string getDescription() const { return description; }
    std::string getStatus() const { return currentState->getStatusName(); }
    std::string getApprovalReason() const { return approvalReason; }
    int getWorkshopId() const { return workshopId; }

    // Setters
    void setClaimId(int val) { claimId = val; }
    void setPolicyNo(int val) { policyNo = val; }
    void setDate(const std::string& val) { date = val; }
    void setDescription(const std::string& val) { description = val; }
    void setApprovalReason(const std::string& val) { approvalReason = val; }
    void setWorkshopId(int val) { workshopId = val; }

    void setState(ClaimState* newState) {
        delete currentState;
        currentState = newState;
    }

    void inspect() { currentState->inspect(this); }
    void approve(const std::string& reason) { currentState->approve(this, reason); }
    void reject(const std::string& reason) { currentState->reject(this, reason); }

    std::string escape(std::string str) const {
        for (char& c : str) if (c == ',') c = ';';
        return str;
    }

    std::string serialize() const {
        return std::to_string(claimId) + "," + 
               std::to_string(policyNo) + "," + 
               escape(date) + "," + 
               escape(description) + "," + 
               getStatus() + "," + 
               escape(approvalReason) + "," + 
               std::to_string(workshopId);
    }
};

// --- State Method Implementations ---
inline void ClaimState::inspect(Claim* claim) { throw std::runtime_error("Cannot inspect in current state."); }
inline void ClaimState::approve(Claim* claim, const std::string& reason) { throw std::runtime_error("Cannot approve in current state."); }
inline void ClaimState::reject(Claim* claim, const std::string& reason) { throw std::runtime_error("Cannot reject in current state."); }

inline void PendingState::inspect(Claim* claim) { claim->setState(new InspectedState()); }
inline void PendingState::approve(Claim* claim, const std::string& reason) { 
    claim->setApprovalReason(reason);
    claim->setState(new ApprovedState()); 
}
inline void PendingState::reject(Claim* claim, const std::string& reason) { 
    claim->setApprovalReason(reason);
    claim->setState(new RejectedState()); 
}

inline void InspectedState::approve(Claim* claim, const std::string& reason) { 
    claim->setApprovalReason(reason);
    claim->setState(new ApprovedState()); 
}
inline void InspectedState::reject(Claim* claim, const std::string& reason) { 
    claim->setApprovalReason(reason);
    claim->setState(new RejectedState()); 
}