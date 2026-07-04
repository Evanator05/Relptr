#include "relptr.hpp"
#include <cinttypes>
#include <vector>
#include <stdio.h>

int main(int argc, char* argv[]) {
    std::vector<uint64_t> numbers{0, 0, 69, 0, 0};
    
    // create relptr base for the numbers vector
    // in a real world application you would probably define this in the header file for whatever you are doing
    using NumbersBase = RelptrBaseVector<RELPTR_TAG(NUMBERSBASE), uint64_t>;

    // bind the NumbersBase to the numbers vector
    NumbersBase::set_base(numbers); 

    Relptr<NumbersBase, uint32_t> testPtr{2}; // creating the relptr with an index of 2 bound to the numbers vector

    Relptr<NumbersBase> testPtr2{}; // not defining type of offset because it defaults to uint32_t

    // the following 2 lines do the exact same thing just showing there are multiple ways of setting it
    testPtr2 = 2; // set testptr to index 2 
    testPtr2 = &numbers[2]; // set testptr directly from address of value in numbers array

    printf("First Fetch: %u\n", *testPtr); // Prints 69
    
    // add a bunch of values to the numbers array forcing it to reallocate somewhere else
    for (size_t i = 0; i < 50; ++i) { 
        numbers.push_back(5);
    }

    printf("Second Fetch: %u\n", *testPtr); // notice that after lots of reallocations testPtr still points to the correct spot in the numbers vector. Prints 69
    *testPtr = 428;
    printf("Test Pointer 2: %u\n", *testPtr2); // notice that after lots of reallocations testPtr still points to the correct spot in the numbers vector. Prints 428
    printf("Serialized Value: %u\n", testPtr); // when serialized the value is just the offset value of the pointer. Prints 2
}