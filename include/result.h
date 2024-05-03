#ifndef RESULT_H
#define RESULT_H

#include <string>

enum ResultType {
    OK,
    ERROR,
};

class Result {
public:
    static Result Ok();
    static Result Error(std::string error);
    bool isOk() const;
    bool isError() const;
    std::string getError() const;
    Result operator&&(const Result& other);

private:
    Result(std::string error, ResultType result_type);
    std::string error;
    ResultType result_type;
};

#endif