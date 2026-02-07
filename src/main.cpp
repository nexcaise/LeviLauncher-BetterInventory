#include <pl/Gloss.h>
#include "features/RegisterHooks.hpp"

__attribute__((constructor))
void Init() {
    GlossInit(true);
    RegisterHooks();
}