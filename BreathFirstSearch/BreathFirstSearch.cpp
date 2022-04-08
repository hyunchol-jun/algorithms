#include <iostream>
#include <deque>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>

bool personIsSeller(std::string person)
{
    return person[person.length()-1] == 'm';
}

bool personIsAlreadySearched(
        std::vector<std::string> searchedPeople,
        std::string person
        )
{
    auto find = std::find(
            searchedPeople.begin(),
            searchedPeople.end(),
            person
            );
    return find == searchedPeople.end();
}

bool breathFirstSearch(
    std::unordered_map<std::string, std::vector<std::string>> graph,
    std::string name
    )
{
    std::deque<std::string> searchQueue;
    std::vector<std::string> searchedPeople;
    for (const auto& s: graph[name])
        searchQueue.push_back(s);

    while (!searchQueue.empty())
    {
        std::string person {searchQueue.front()};
        searchQueue.pop_front();

        if (personIsAlreadySearched(searchedPeople, person))
        {
            if (personIsSeller(person))
            {
                std::cout << person << " is a mango seller." << '\n';
                return true;
            }
            else
            {
                for (const auto& s: graph[person])
                    searchQueue.push_back(s);
                searchedPeople.push_back(person);
            }
        }
    }
    return false;
}

int main()
{
    std::unordered_map<std::string, std::vector<std::string>> graph {};
    graph["you"] = {"alice", "bob", "claire"};
    graph["bob"] = {"anuj", "peggy"};
    graph["alice"] = {"peggy"};
    graph["claire"] = {"thom", "jonny"};
    graph["anuj"] = {};
    graph["peggy"] = {};
    graph["thom"] = {};
    graph["jonny"] = {};

    breathFirstSearch(graph, "you");
}
