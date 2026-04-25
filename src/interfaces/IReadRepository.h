#pragma once
#include <vector>

template <typename T, typename ID = int>
class IReadRepository {
public:
    virtual ~IReadRepository() = default;
    virtual T getById(ID id) = 0;
    virtual std::vector<T> getAll() = 0;
};
