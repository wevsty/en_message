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

	std_rand();
    int safe_int();
    std::string safe_string(int maxlen = 8);

    int fast_int();
    std::string fast_string(int maxlen = 8);

private:
    std::random_device m_rand_dev;
    unsigned int n_rand_seed;
};

#endif // __STD_RAND_CLASS_H__
