#include "aho-corasick.h"
#include <iostream>

int main()
{
    {
        AhoCorasick ac;
        ac.add_pattern("he");
        ac.add_pattern("she");
        ac.add_pattern("his");
        ac.add_pattern("hers");
        ac.build_links();

        std::cout << "=== Test 1 ===\n";
        ac.search("ushers");
    }

    // Test 2
    {
        AhoCorasick ac;
        ac.add_pattern("a");
        ac.add_pattern("aa");
        ac.add_pattern("aaa");
        ac.build_links();

        std::cout << "\n=== Test 2 ===\n";
        ac.search("aaaaaaaa");
    }

    // Test 3
    {
        AhoCorasick ac;
        ac.add_pattern("hello");
        ac.add_pattern("world");
        ac.build_links();

        std::cout << "\n=== Test 3 ===\n";
        ac.search("no matches here");
    }
}