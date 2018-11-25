#include "std_rand.h"


std_rand::std_rand()
{
    n_rand_seed = m_rand_dev();
}

int std_rand::safe_int()
{
    return m_rand_dev();
}

std::string std_rand::safe_string(int maxlen)
{
    static const char char_table[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int n_table_max_index = sizeof(char_table) - 1;
    std::string str_out;
    for (int i = 0; i < maxlen; i++)
    {
        str_out.push_back(char_table[m_rand_dev() % n_table_max_index]);
    }
    return str_out;
}

int std_rand::fast_int()
{
    std::mt19937 gen(n_rand_seed);
    n_rand_seed = gen();
    return gen();
}

std::string std_rand::fast_string(int maxlen)
{
    static const char char_table[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int n_table_max_index = sizeof(char_table) - 1;
    std::string str_out;
    std::mt19937 gen(n_rand_seed);
    n_rand_seed = gen();
    for (int i = 0; i < maxlen; i++)
    {
        str_out.push_back(char_table[gen() % n_table_max_index]);
    }
    return str_out;
}
