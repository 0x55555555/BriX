#pragma once
#include "shift/sglobal.h"

#if defined(GAME_BUILD)
#  define GAME_EXPORT X_DECL_EXPORT
#else
#  define GAME_EXPORT X_DECL_IMPORT
#endif

S_MODULE(GAME_EXPORT, Game)
