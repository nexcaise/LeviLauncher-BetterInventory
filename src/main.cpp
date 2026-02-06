#include <pl/Gloss.h>
#include "features/Hooks.hpp"

__attribute__((constructor))
void Init() {
    GlossInit(true);
    RegisterHooks();
}