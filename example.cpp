#include "relptr.hpp"
#include <cinttypes>
#include <vector>
#include <stdio.h>

int main(int argc, char* argv[]) {
    std::vector<uint64_t> numbers{0, 0, 69, 0, 0};

    // binding the numbers array to the base indexer
    RelptrBaseVector<
        struct NumbersBase, // use 'struct BaseName' to pick a name for all Relptrs to use as the base. Prefixing with struct to allow freetyping a name
        uint64_t // the type of data stored at this base
        >::set_base(numbers); 

    Relptr<
        uint64_t, // the type of data stored at the pointer
        RelptrBaseVector< // the indexer for grabbing the pointer base
            struct NumbersBase, // using 'struct BaseName' to pick what base to use for this Relptr
            uint64_t // the type of data stored at the base
            >, 
        uint32_t // the type of integer used to offset from the base (could be a uint8_t for up to 255 offset ect)
        > testPtr{2}; // creating the relptr with an index of 2 bound to the numbers vector

    printf("First Fetch: %u\n", *testPtr);
    for (size_t i = 0; i < 50; ++i) { // add a bunch of values to the numbers array forcing it to reallocate somewhere else
        numbers.push_back(5);
    }
    printf("Second Fetch: %u\n", *testPtr); // notice that after lots of reallocations testPtr still points to the correct spot in the numbers vector
    printf("Serialized Value: %u\n", testPtr); // when serialized the value is just the offset value of the pointer
}