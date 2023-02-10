#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>


bool inRange(int a, int b, int c)
{
    return a >= b && a <= c;
}

bool ft_isPrint(int c)
{
    return inRange(c, 32, 127);
}

template<typename T> bool handleVal(T val)
{
    int valAsInt = static_cast<int>(val);
    float valAsFloat = static_cast<float>(val);
    if (!isnan(valAsFloat) && valAsFloat != INFINITY && valAsFloat != -INFINITY)
        std::cout << "int: " << valAsInt << std::endl;
    else
        std::cout << "int: impossible conversion" << std::endl;
    
    std::cout << "float: " << valAsFloat << 'f' << std::endl;
    std::cout << "double: " << static_cast<double>(val) << std::endl;
    if (ft_isPrint(valAsInt))
        std::cout << "char: '" << static_cast<char>(val) << "'" << std::endl;
    else
        std::cout << "char: impossible conversion" << std::endl;
    return true;
}

template<typename T> bool handleValAsString(std::string str)
{
    std::stringstream ss(str);
    T val;
    ss >> val;
    if (ss.fail())
        std::cerr << "arg cannot be converted into a literral" << std::endl;
    else
        handleVal<T>(val);
    return true;
}

bool matchChar(std::string arg)
{
    if (arg.length() == 1 && ft_isPrint(arg[0]) && !inRange(arg[0], '0', '9'))
        handleVal<char>(arg[0]);
    return arg.length() == 1 && ft_isPrint(arg[0]) && !inRange(arg[0], '0', '9');
}

bool matchFloatingPoint(std::string arg)
{
    if (arg[0] == '-' || arg[0] == '+')
        arg = arg.substr(1, arg.length()- 1);
    bool encouteredPoint = false;
    for (size_t i = 0; i < arg.length(); i++)
        if (arg[i] == '.')
            if (encouteredPoint)
                return false;
            else
                encouteredPoint = true;
        else if (arg[i] < '0' || arg[i] > '9')
            return false;
    return encouteredPoint;
}

bool matchDouble(std::string arg)
{
    if (arg == "nanf")
        return handleVal<float>(NAN);
    if (arg == "+inff" || arg == "inff")
        return handleVal<float>(INFINITY);
    if (arg == "-inff")
        return handleVal<float>(-INFINITY);
    if (matchFloatingPoint(arg))
        return handleValAsString<double>(arg);
    return false;
}

bool matchFloat(std::string arg)
{
    if (arg == "-inf")
        return handleVal<float>(-INFINITY);
    if (arg == "+inf" || arg == "inf")
        return handleVal<float>(INFINITY);
    if (arg == "nan")
        return handleVal<float>(NAN);
    if (arg[arg.length()- 1] != 'f')
        return false;
    arg = arg.substr(0, arg.length() - 1);
    if (matchFloatingPoint(arg))
        return handleValAsString<float>(arg);
    return false;
}

bool matchInt(std::string arg)
{
    if (arg[0] == '-' || arg[0] == '+')
        arg = arg.substr(1, arg.length() - 1);
    for (size_t i = 0; i < arg.length(); i++)
        if (arg[i] < '0' | arg[i] > '9')
            return false;
    handleValAsString<int>(arg);
    return true;
}

//methods
void Convert(std::string arg)
{
    try
    {
        if (!matchInt(arg) && !matchChar(arg) && !matchDouble(arg) && !matchFloat(arg))
            std::cerr << "Error: arg cannot be converted into a literral!" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

int main(int ac, char **av)
{
    if (ac < 2)
        return (std::cerr << "Error: " << av[0] << " must be called with at least one argument!" << std::endl, 1);
    std::string str = av[1];
    Convert(str);
}