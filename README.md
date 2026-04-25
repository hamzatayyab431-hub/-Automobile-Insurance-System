# Automobile Insurance Information System 🚗🛡️

A robust, SOLID-compliant C++ information system designed for automobile insurance companies. This system manages insurance policies, customer data, vehicle information, claims, and inspection reports with a clean, role-based architecture.

## 📋 Features
- **Role-Based Access**: Specialized interfaces for Managers, Salesmen, and Surveyors.
- **Policy Management**: Create and track insurance policies for vehicles.
- **Claim Processing**: Streamlined workflow from claim filing to final inspection.
- **Data Persistence**: File-based storage system for easy portability.
- **Clean Architecture**: Follows SOLID principles (SRP, Open/Closed, Dependency Inversion).

---

## 📊 System Diagrams

### 1. Class Diagram
This diagram shows the inheritance structure of the staff and the relationships between core entities.

```mermaid
classDiagram
    class Staff {
        <<Abstract>>
        #int id
        #string name
        #string username
        +getRole() string*
        +checkPassword(string) bool
    }
    class Manager {
        +getRole() "Manager"
    }
    class Salesman {
        +getRole() "Salesman"
    }
    class Surveyor {
        +getRole() "Surveyor"
    }
    
    Staff <|-- Manager
    Staff <|-- Salesman
    Staff <|-- Surveyor

    class InsurancePolicy {
        +int policyId
        +int vehicleId
        +double premium
        +string startDate
    }

    class Claim {
        +int claimId
        +int policyId
        +string status
        +string description
    }

    class InspectionReport {
        +int reportId
        +int claimId
        +string assessment
        +double estimatedCost
    }

    InsurancePolicy "1" -- "0..*" Claim : covers
    Claim "1" -- "0..1" InspectionReport : has
    Vehicle "1" -- "1" InsurancePolicy : insured by
useCaseDiagram
    actor "Manager" as M
    actor "Salesman" as S
    actor "Surveyor" as SV

    package "Insurance System" {
        usecase "Login" as UC1
        usecase "Manage Staff Records" as UC2
        usecase "Generate System Reports" as UC3
        usecase "Register New Customer" as UC4
        usecase "Create Insurance Policy" as UC5
        usecase "File New Claim" as UC6
        usecase "Perform Damage Inspection" as UC7
        usecase "Submit Assessment Report" as UC8
    }

    M --> UC1
    M --> UC2
    M --> UC3
    
    S --> UC1
    S --> UC4
    S --> UC5
    S --> UC6

    SV --> UC1
    SV --> UC7
    SV --> UC8
