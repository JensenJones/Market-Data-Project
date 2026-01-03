#pragma once

#include "../MessageHandling/TopOfBook.hpp"

namespace dataProcessing {
    class Greek {
    public:
        virtual ~Greek() = default;
        virtual void update(const TopOfBook& topOfBook) = 0;
        [[nodiscard]] virtual double getGreek() const = 0;
    };
}
