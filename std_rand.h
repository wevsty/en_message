#ifndef __STD_RAND_CLASS_H__
#define __STD_RAND_CLASS_H__

#include <QObject>
//#include <stdlib.h>
//#include <stdio.h>
//#include <time.h>
#include <string>
#include <random>

class std_rand
{
public:
    unsigned int n_rand_seed;
    std_rand();
    int rand_int();
    std::string rand_std_string(int maxlen = 8);

};

#endif // __STD_RAND_CLASS_H__
