//
// Created by Edward Webster on 26/01/2021.
//

#ifndef MAIN_CPP_RANDOMGENERATOR_H
#define MAIN_CPP_RANDOMGENERATOR_H

#include <random>

float randomBetween(int a, int b) {
    return a + rand() % (b - a + 1);
}

//int randomBetween(int a, int b) {
//    std::default_random_engine generator;
//    std::uniform_int_distribution<int> distribution(a, b);
//    return distribution(generator);
//}

#endif //MAIN_CPP_RANDOMGENERATOR_H
