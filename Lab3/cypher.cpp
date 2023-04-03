#include "inc/generator.h"
#include "inc/prsParam.h"
#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <vector>

void    cypher(KeyGenerator& k) {
    k.setDFromFile("private.txt");
    k.setNFromFile("private.txt");
    k.setEFromFile("public.txt");

}