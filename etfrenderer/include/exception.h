#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>


/**
  */
class FunctionNotImplemented : public std::runtime_error
{
public:
    FunctionNotImplemented() :
        std::runtime_error("Function not implemented") {}
};

/**
  */
class MethodNotImplemented : public std::runtime_error
{
public:
    MethodNotImplemented() :
        std::runtime_error("Method not implemented") {}
};

/**
  */
class ETFRendererException : public std::runtime_error
{
public:
    ETFRendererException() :
        std::runtime_error("Unknown ETFRendererException") {}
    ETFRendererException(const char* message) :
        std::runtime_error(message) {}
};


#endif // EXCEPTION_H
