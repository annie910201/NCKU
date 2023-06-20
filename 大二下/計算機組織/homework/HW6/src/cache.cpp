#include <bits/stdc++.h>

using namespace std;

/* all function */
void count_bit(long long &offest_size, long long &index_size, long long &index_bit, long long &offset_bit);
void update_cache_LRU(vector<vector<long long>> &cache, long long start, long long index);
long long collision_addr(vector<vector<long long>> &cache, long long tag, long long index);
long long directed_mapped(long long block_size, long long cache_size, vector<long long> &addr, ofstream &file_out);
long long four_ways_set_associative(long long block_size, long long cache_size, vector<long long> &addr, ofstream &file_out);
long long fully_associative(long long block_size, long long cache_size, vector<long long> &addr, ofstream &file_out);

/* count offset bit and index bit */
void count_bit(long long &offest_size, long long &index_size, long long &index_bit, long long &offset_bit)
{
    while (offest_size != 1)
    {
        offset_bit++;
        offest_size = offest_size >> 1;
    }
    while (index_size != 1)
    {
        index_bit++;
        index_size = index_size >> 1;
    }
}

/* find if there are collision data and return the index*/
long long collision_addr(vector<vector<long long>> &cache, long long tag, long long index)
{
    for (long long i = 0; i < cache[index].size(); i++)
    {
        if (cache[index][i] == tag)
            return i;
    }
    return -1;
}

/* move bit forward */
void update_cache_LRU(vector<vector<long long>> &cache, long long start, long long index)
{
    long long tmp = cache[index][start];
    for (long long i = start; i < cache[index].size() - 1; i++)
        cache[index][i] = cache[index][i + 1];
    cache[index][cache[index].size() - 1] = tmp;
}

long long directed_mapped(long long block_size, long long cache_size, vector<long long> &addr, ofstream &file_out)
{
    long long number_block = cache_size / block_size;
    long long tag, index;
    long long cache[number_block] = {0};
    long long hit = 0;
    long long offest_size = block_size << 2, index_size = number_block;
    long long index_bit = 0, offset_bit = 0;
    long long mod_addr = 0;
    count_bit(offest_size, index_size, index_bit, offset_bit);

    for (int i = 0; i < addr.size(); i++)
    {
        /*  example: 191(10111111)
            get bytes:1011111100
            offset_bit = 2 ( 4 = 2^2 )
            index_bit = 4 ( 16/1 = 16 = 2^4 )
            tag_bit =  32 - 2 - 4 = (I don't care)
            so
            offset = 00
            index = 1111
            tag = 0...01011
        */
        mod_addr = addr[i] << 2;
        mod_addr = mod_addr >> offset_bit; //count where blocks is it
        tag = mod_addr >> index_bit;
        index = (tag) ? mod_addr % number_block : mod_addr;

        if (!cache[index]) //not filled
        {
            cache[index] = tag;
            file_out << "-1" << endl;
        }
        else if (cache[index] == tag) // hit
        {
            hit++;
            file_out << "-1" << endl;
        }
        else // filled but miss
        {
            file_out << cache[index] << endl;
            cache[index] = tag;
        }
    }
    return hit;
}



long long four_ways_set_associative(long long block_size, long long cache_size, vector<long long> &addr, ofstream &file_out)
{
    long long number_block = (cache_size / block_size) >> 2;//with four sets
    vector<vector<long long>> cache(number_block);
    long long tag, index;
    long long hit = 0;
    long long offest_size = block_size << 2, index_size = number_block;
    long long index_bit = 0, offset_bit = 0;
    long long mod_addr = 0;
    count_bit(offest_size, index_size, index_bit, offset_bit);

    for (long long i = 0; i < addr.size(); i++)
    {
        mod_addr = addr[i] << 2;
        mod_addr = mod_addr >> offset_bit;
        tag = mod_addr >> index_bit;
        index = (tag) ? mod_addr % number_block : mod_addr;

        if (collision_addr(cache, tag, index) != -1) // hit
        {
            file_out << "-1" << endl;
            update_cache_LRU(cache, collision_addr(cache, tag, index), index);
            hit++;
        }
        else if (cache[index].size() != 4 && collision_addr(cache, tag, index) == -1) //not filled and miss
        {
            file_out << "-1" << endl;
            cache[index].push_back(tag);
        }
        else //filled and miss
        {
            file_out << cache[index][0] << endl;
            cache[index][0] = tag;
            update_cache_LRU(cache, 0, index);
        }
    }
    return hit;
}

long long fully_associative(long long block_size, long long cache_size, vector<long long> &addr, ofstream &file_out)
{
    long long number_block = cache_size / block_size;
    vector<vector<long long>> cache(1);//with one set
    long long tag, index = 0;
    long long hit = 0;
    long long offest_size = block_size << 2;
    long long index_bit = 0, offset_bit = 0;
    long long mod_addr = 0;

    /* count bit */
    while (offest_size != 1)
    {
        offset_bit++;
        offest_size = offest_size >> 1;
    }

    for (long long i = 0; i < addr.size(); i++)
    {
        mod_addr = addr[i] << 2;
        mod_addr = mod_addr >> offset_bit;
        tag = mod_addr;
        if (collision_addr(cache, tag, index) != -1) // hit
        {
            file_out << "-1" << endl;
            update_cache_LRU(cache, collision_addr(cache, tag, index), index);
            hit++;
        }
        else if (cache[index].size() != number_block && collision_addr(cache, tag, index) == -1) //not filled and miss
        {
            file_out << "-1" << endl;
            cache[index].push_back(tag);
        }
        else //filled and miss
        {
            file_out << cache[index][0] << endl;
            cache[index][0] = tag;
            update_cache_LRU(cache, 0, index);
        }
    }
    return hit;
}

int main(int argc, char **argv)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long cache_size;
    long long block_size;
    int associativity;
    int replace_mode;
    long long hit = 0;
    int number_addr = 0;
    float miss_rate = 0;
    vector<long long> addr;

    /* input/output file */
    string input;
    ifstream file_txt(argv[1]);
    ofstream file_out;
    file_out.open(argv[2]);
    getline(file_txt, input);
    cache_size = stoi(input);
    getline(file_txt, input);
    block_size = stoi(input);
    getline(file_txt, input);
    associativity = stoi(input);
    getline(file_txt, input);
    replace_mode = stoi(input);
    while (getline(file_txt, input))
    {
        addr.push_back(stoi(input));
        number_addr++;//count the number of data
    }

    switch (associativity)
    {
    case 0:
    {
        hit = directed_mapped(block_size, cache_size, addr, file_out);
        break;
    }
    case 1:
    {
        hit = four_ways_set_associative(block_size, cache_size, addr, file_out);
        break;
    }
    case 2:
    {
        hit = fully_associative(block_size, cache_size, addr, file_out);
        break;
    }
    }
    miss_rate = (double)(number_addr - hit) / (double)number_addr;
    file_out << "Miss rate = " << fixed << setprecision(6) << miss_rate;

    return 0;
}