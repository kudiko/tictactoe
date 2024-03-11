#include <exception>

int Factorial(int n)
{
    if (n < 0)
    {
        throw std::out_of_range("Can't calculate factorial of negative number");
    }

    if (n == 0)
    {
        return 1;
    }

    return n * Factorial(n - 1);
}