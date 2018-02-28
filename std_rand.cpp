#include "std_rand.h"


std_rand::std_rand()
{
	std::random_device rd;
	n_rand_seed = rd();
}

int std_rand::rand_int()
{
	std::mt19937 gen(n_rand_seed);
	n_rand_seed = gen();
	return gen();
}

std::string std_rand::rand_std_string(int maxlen)
{
	const char char_table[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
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
