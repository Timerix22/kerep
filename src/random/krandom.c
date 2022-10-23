#include "krandom.h"

bool fate(float chance){
    int limit=1/chance + 0.01f;
    return rand()%limit == 0;
}
