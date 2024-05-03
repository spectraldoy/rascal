#ifndef RESULT_H
#define RESULT_H

#include <string>

enum ResultType {
    Ok,
    Error,
};

template<typename T, typename E>
class Result {
public:
    Result(T value, E error, ResultType result_type);
    bool isOk() const;
    bool isError() const;

    T getValue() const;
    E getError() const;

private:
    T value;
    E error;
    ResultType result_type;
};

template<typename T, typename E>
Result<T, E> Ok(T value);

template<typename T, typename E>
Result<T, E> Error(E error);

#endif