#include "result.h"

template<typename T, typename E>
Result<T, E>::Result(T value, E error, ResultType result_type)
 : value(value), error(error), result_type(result_type)
{}

template<typename T, typename E>
bool Result<T, E>::isOk() const {
    return this->result_type == ResultType::Ok;
}

template<typename T, typename E>
bool Result<T, E>::isError() const {
    return this->result_type == ResultType::Error;
}

template<typename T, typename E>
T Result<T, E>::getValue() const {
    return this->value;
}

template<typename T, typename E>
E Result<T, E>::getError() const {
    return this->error;
}

template<typename T, typename E>
Result<T, E> Ok(T value) {
    E error;
    return Result<T, E>(value, error, ResultType::Ok);
}

template<typename T, typename E>
Result<T, E> Error(E error) {
    T value;
    return Result<T, E>(value, error, ResultType::Error);
}

