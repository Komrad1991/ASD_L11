#pragma once
#include <vector>
#include <map>
#include <string>
#include <queue>


class AhoCorasick
{
private:
    struct Node
    {
        std::map<char, int> next;
        int link = -1;      
        int exit_link = -1;  
        bool is_terminal = false;
        int pattern_index = -1;
    };

    std::vector<Node> bor;
    std::vector<std::string> patterns;
    int _compares = 0;

public:
    AhoCorasick()
    {
        bor.emplace_back(); 
    }

    void add_pattern(const std::string& pattern)
    {
        int current = 0;
        for (char c : pattern)
        {
            if (bor[current].next.find(c) == bor[current].next.end())
            {
                bor[current].next[c] = bor.size();
                bor.emplace_back();
            }
            current = bor[current].next[c];
        }
        bor[current].is_terminal = true;
        bor[current].pattern_index = patterns.size();
        patterns.push_back(pattern);
    }

    void build_links()
    {
        std::queue<int> q;
        q.push(0);

        while (!q.empty())
        {
            int current = q.front();
            q.pop();

            for (const auto& kv : bor[current].next)
            {
                char c = kv.first;
                int child = kv.second;
                int link = bor[current].link;

                while (link != -1 && bor[link].next.find(c) == bor[link].next.end())
                {
                    link = bor[link].link;
                    _compares++;
                }

                if (link == -1)
                {
                    bor[child].link = 0;
                }
                else
                {
                    bor[child].link = bor[link].next.at(c);
                }

                if (bor[bor[child].link].is_terminal)
                {
                    bor[child].exit_link = bor[child].link;
                }
                else
                {
                    bor[child].exit_link = bor[bor[child].link].exit_link;
                }

                q.push(child);
            }
        }
    }

    std::vector<std::pair<int, int>> search(const std::string& text)
    {
        std::vector<std::pair<int, int>> matches;
        int current = 0;

        for (int i = 0; i < text.size(); ++i)
        {
            char c = text[i];
            _compares++;

            while (current != 0 && bor[current].next.find(c) == bor[current].next.end())
            {
                current = bor[current].link;
                _compares++;
            }

            if (bor[current].next.find(c) != bor[current].next.end())
            {
                current = bor[current].next.at(c);
            }

            if (bor[current].is_terminal)
            {
                matches.emplace_back(i - patterns[bor[current].pattern_index].size() + 1, bor[current].pattern_index);
            }

            int exit_node = bor[current].exit_link;
            while (exit_node != -1)
            {
                matches.emplace_back(i - patterns[bor[exit_node].pattern_index].size() + 1,bor[exit_node].pattern_index);
                exit_node = bor[exit_node].exit_link;
            }
        }

        return matches;
    }

    int compares() const
    {
        return _compares;
    }

    void reset()
    {
        _compares = 0;
    }
};