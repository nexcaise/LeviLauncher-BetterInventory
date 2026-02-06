#include <pl/Gloss.h>
#include "util/Logger.hpp"
#include "features/Hooks.hpp"

Logger logger("Offhand");

__attribute__((constructor))
void Init() {
    logger.info("Init()");
    GlossInit(true);
    RegisterHooks();
}