#define SOL_LUAJIT 1

#include <cstdlib>
#include <unordered_map>
#include <string_view>

#include <sol/sol.hpp>

#include "out.h"

void load_replxx(sol::state& lua);

int main(int argc, const char* argv[])
{
	sol::state lua;
	lua.open_libraries(
		sol::lib::base, sol::lib::coroutine, sol::lib::string, sol::lib::io, 
		sol::lib::table, sol::lib::math, sol::lib::debug, sol::lib::bit32, 
		sol::lib::os, sol::lib::ffi, sol::lib::package
	);
	
	load_replxx(lua);

	// int x = 0;
	// lua.set_function("beep", [&x]{ ++x; });


	sol::table args = lua.create_table_with();
	for ( int i = 1; i < argc; ++i ) {
		args[i] = std::string(argv[i]);
	}

	lua["arg"] = args;
	sol::load_result fx;
	if (const char * path = std::getenv("UCL_DEBUG_LOAD"))
	{
		fx = lua.load_file(path);
	} else {
		fx = lua.load_buffer((const char *)&luaJIT_BC_out[0], luaJIT_BC_out_SIZE, "ucl.lua");
	}


	if (!fx.valid()) {
		sol::error err = fx;
		std::cerr << err.what() << std::endl;
		return 1;
	}

	sol::protected_function_result result = fx();

	if (result.valid()) {
		return 0;
	}

	else {
		sol::error err = result;
		std::string what = err.what();
		std::cerr << what << std::endl;
		return 1;
	}

}
