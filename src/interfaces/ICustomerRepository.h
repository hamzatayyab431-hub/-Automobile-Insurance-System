#pragma once
#include "IReadRepository.h"
#include "IWriteRepository.h"
#include "IDeleteRepository.h"
#include "../models/Customer.h"
#include <vector>
#include <string>

class ICustomerRepository : public IReadRepository<Customer>,
                            public IWriteRepository<Customer>,
                            public IDeleteRepository<Customer> {
public:
    virtual ~ICustomerRepository() = default;
    virtual std::vector<Customer> findBySalesmanAndMonth(int salesmanId, const std::string& month) = 0;
};
