#pragma once
#include <unordered_map>
#include "auth.hpp"
#include "../protection/skStr.h"

class c_globals {
public:
	bool active = true;

	int tab = 0;
    
};

inline c_globals globals;

