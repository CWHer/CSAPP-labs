// #include "cachelab.h"
#include <vector>
#include <memory>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdio>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::numeric_limits;
using std::string;
using std::stringstream;
using std::unordered_map;
using std::vector;
typedef unsigned long long u64;

const bool out_log = false;

struct Result
{
    int hit, miss, eviction;
    Result() : hit(0), miss(0),
               eviction(0) {}
    void printSummary()
    {
        printf("hits:%d misses:%d evictions:%d\n",
               hit, miss, eviction);
    }
};

class Cache
{
private:
    u64 s; // 2^s cache set
    u64 E; // a cache set contains E lines
    u64 b; // 2^b block each line
    Result result;

    struct CacheLine
    {
        bool valid_bit;
        u64 tag_bit;
        u64 B;
        int last_time;

        CacheLine() : valid_bit(0), last_time(0) {}

        bool access(int cur_time, u64 tag, u64 idx_b)
        {
            if (valid_bit && tag == tag_bit && idx_b < B)
            {
                last_time = cur_time;
                return true;
            }
            return false;
        }
    };

    struct CacheSet
    {
        u64 E, b;
        unordered_map<u64, CacheLine> lines;

        CacheSet(u64 E, u64 b) : E(E), b(b) {}

        bool access(int cur_time, u64 tag, u64 idx_b)
        {
            if (lines.count(tag) == 0)
                return false;
            return lines[tag].access(cur_time, tag, idx_b);
        }

        int insert(int cur_time, u64 tag, u64 idx_b)
        {
            if (lines.size() < E) // not full
            {
                CacheLine new_line;
                new_line.valid_bit = true;
                new_line.B = 1 << b;
                new_line.last_time = cur_time;
                new_line.tag_bit = tag;
                lines[tag] = std::move(new_line);
                return 0;
            }
            // evict
            evict();
            if (out_log)
                cout << "eviction" << ' ';
            insert(cur_time, tag, idx_b);
            return 1;
        }

        void evict()
        {
            int last_time = numeric_limits<int>::max();
            for (const auto &line : lines)
                last_time = std::min(last_time,
                                     line.second.last_time);
            for (auto &line : lines)
                if (line.second.last_time == last_time)
                {
                    lines.erase(line.first);
                    return;
                }
        }
    };

    vector<CacheSet> cache_sets;

    // after s,E,b are initialized
    void initCache()
    {
        for (int i = 0; i < (1 << s); ++i)
            cache_sets.emplace_back(CacheSet(E, b));
    }

    bool access(int cur_time, u64 tag, u64 idx_s, u64 idx_b)
    {
        return cache_sets[idx_s].access(cur_time, tag, idx_b);
    }

    void insert(int cur_time, u64 tag, u64 idx_s, u64 idx_b)
    {
        if (cache_sets[idx_s]
                .insert(cur_time, tag, idx_b))
            result.eviction++;
    }

public:
    Cache(u64 s, u64 E, u64 b)
    {
        this->s = s;
        this->E = E;
        this->b = b;
        initCache();
    }

    // store is similar to load
    //  without modify data
    void store(int cur_time, u64 addr)
    {
        load(cur_time, addr);
    }

    void load(int cur_time, u64 addr)
    {
        u64 idx_b = addr & ((1 << b) - 1);
        u64 idx_s = (addr >> b) & ((1 << s) - 1);
        u64 tag = addr >> (b + s);
        if (access(cur_time, tag, idx_s, idx_b))
        {
            result.hit++;
            if (out_log)
                cout << "hit" << ' ';
            return;
        }
        else
        {
            result.miss++;
            if (out_log)
                cout << "miss" << ' ';
            insert(cur_time, tag, idx_s, idx_b);
        }
    }

    void print()
    {
        result.printSummary();
    }
};

int main()
{
    // freopen("test.in", "r", stdin);

    int s, E, b;
    cout << "Input s E b" << endl;
    cin >> s >> E >> b;
    Cache cache(s, E, b);

    cout << "Input file path" << endl;
    string file_path;
    cin >> file_path;
    ifstream fin(file_path);
    if (!fin.is_open())
    {
        cout << "Can't open file" << endl;
        return 1;
    }

    string line;
    int cur_time = 0;
    while (!fin.eof())
    {
        cur_time++;
        getline(fin, line);
        if (line.empty())
            continue;
        stringstream in(line);
        char opt;
        u64 addr, mem_size;
        in >> opt >>
            std::hex >> addr >>
            std::dec >> mem_size;
        switch (opt)
        {
        case 'L':
            cache.load(cur_time, addr);
            break;
        case 'S':
            cache.store(cur_time, addr);
            break;
        case 'M':
            cache.load(cur_time, addr);
            cache.store(cur_time, addr);
            break;

        default:
            break;
        }
        if (out_log)
            cout << endl;
    }
    cache.print();
    return 0;
}
