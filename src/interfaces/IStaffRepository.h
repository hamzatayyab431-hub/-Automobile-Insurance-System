#pragma once
#include "IReadRepository.h"
#include "../models/Staff.h"
#include <memory>

class IStaffRepository : public IReadRepository<std::shared_ptr<Staff>> {
public:
    virtual ~IStaffRepository() = default;
};
