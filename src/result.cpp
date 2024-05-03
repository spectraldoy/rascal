#include "result.h"

Result Result::Ok() {
    return Result("", ResultType::OK);
}

Result Result::Error(std::string error) {
    return Result(error, ResultType::ERROR);
}

bool Result::isOk() const {
    return this->result_type == ResultType::OK;
}

bool Result::isError() const {
    return this->result_type == ResultType::ERROR;
}

std::string Result::getError() const {
    return this->error;
}

Result Result::operator&&(const Result& other) {
    if (&other == this) {
        return *this;
    }

    if (this->isError()) {
        return *this;
    } else if (other.isError()) {
        return other;
    }

    return Result::Ok();
}

Result::Result(std::string error, ResultType result_type)
 : error(error), result_type(result_type)
{}