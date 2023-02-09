#include <iostream>
#include <string>
#include "Data.hpp"
#include <stdint.h>
#include "Data.hpp"
#include <iostream>
#include <string>


uintptr_t serialize(Data* ptr)
{
	return reinterpret_cast<uintptr_t>(ptr);
}
Data* deserialize(uintptr_t raw)
{
	return reinterpret_cast<Data*>(raw);
}

void debugData(Data* dataPtr)
{
    std::cout << "Data address:" << dataPtr << std::endl;
    std::cout << "Data.str: \"" << dataPtr->str << "\"" << std::endl;
    std::cout << "Data.number: " << dataPtr->number << std::endl << std::endl;
}

void testSerializer(Data* dataPtr)
{
    std::cout << "Data struct:" << std::endl;
    debugData(dataPtr);
    uintptr_t uintptr = serialize(dataPtr);
    std::cout << "serialized data as uintptr: " << uintptr << std::endl;
    Data* deserializedDataPtr = deserialize(uintptr);
    std::cout << "Deserialized data struct:" << std::endl;
    debugData(deserializedDataPtr);
}

int main()
{

    Data firstData;
    firstData.str = "What a beautifull code!";
    firstData.number = 1;
    testSerializer(&firstData);
    std::cout << std::endl << std::endl << std::endl;

    Data secondData;
    secondData.str = "What a terrible code!";
    secondData.number = 56;
    testSerializer(&secondData);
}