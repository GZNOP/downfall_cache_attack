#include <iomanip>
#include <iostream>
#include <map>
#include "lib.h"

unsigned int cpt = 0;
typedef std::map<std::string, size_t> Map;
static Map* map;

void map_create() {
    map = new Map();
}

void map_increment(char* k) {
    Map* m = reinterpret_cast<Map*>(map);
    (*m)[std::string(k)]++;
    cpt++;
}

// Normally here, we should count the occurencies of each dumped bytes array and
// print only the more used ones. But we don't do this because we wanted to see 
// every dumps
void map_dump() {
    for (std::map<std::string, size_t>::iterator i = map->begin(); i != map->end(); i++) {
        std::cout << i->first << ": " << i->second << std::endl << "0x";
        for (size_t j = 0; j < i->first.length(); j++)
        {
          std::cout << std::hex << (0xFF & i->first.at(j));
        }
        std::cout << std::endl;
    }
    std::cout << "Dumped " << std::dec <<  cpt << " times." << std::endl; 
}
