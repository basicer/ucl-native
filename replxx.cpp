#define SOL_LUAJIT 1
#include <unordered_map>

#include <replxx.hxx>
#include <sol/sol.hpp>

using Replxx = replxx::Replxx;

void load_replxx(sol::state& lua)
{


	lua.new_usertype<Replxx>("replxx",
		"install_window_change_handler", &Replxx::install_window_change_handler,
		"input", &Replxx::input,
		//"print", &Replxx::print,
		"print", [](Replxx& self, std::string text) { self.print("%s\n", text.c_str()); },
		"emulate_key_press", &Replxx::emulate_key_press,
		
		"history_add", &Replxx::history_add,
		"history_clear", &Replxx::history_clear,

		//"bind_key_internal", &Replxx::bind_key_internal
		"bind", [](Replxx& self, sol::object key, const sol::object action) {
			char32_t ckey = '\0';

			if (key.is<int>()) {
				ckey = key.as<int>();
			} else if (key.is<std::string>()) {
				ckey = key.as<std::string>()[0];
			}

			if (ckey == '\0') return;

			if (action.is<sol::function>())
				self.bind_key(ckey, [=](char32_t c) { action.as<sol::function>()(); return Replxx::ACTION_RESULT::CONTINUE; });
			else
				self.bind_key_internal(ckey, action.as<std::string>().c_str());
			
		},

		"set_completion_callback", &Replxx::set_completion_callback,
		"set_hint_callback", &Replxx::set_hint_callback,
		"set_highlighter_callback", &Replxx::set_highlighter_callback,

		"set_immediate_completion", &Replxx::set_immediate_completion,
		"set_double_tab_completion", &Replxx::set_double_tab_completion
	);

	lua["replxx"]["colors"] = lua.create_table_with(
		"BLACK", Replxx::Color::BLACK,   
		"RED", Replxx::Color::RED,
		"GREEN", Replxx::Color::GREEN,
		"BROWN", Replxx::Color::BROWN,
		"BLUE", Replxx::Color::BLUE,
		"MAGENTA", Replxx::Color::MAGENTA,
		"CYAN", Replxx::Color::CYAN,
		"LIGHTGRAY", Replxx::Color::LIGHTGRAY,
		"GRAY", Replxx::Color::GRAY,
		"BRIGHTRED", Replxx::Color::BRIGHTRED,
		"BRIGHTGREEN", Replxx::Color::BRIGHTGREEN,
		"YELLOW", Replxx::Color::YELLOW,
		"BRIGHTBLUE", Replxx::Color::BRIGHTBLUE,
		"BRIGHTMAGENTA", Replxx::Color::BRIGHTMAGENTA,
		"BRIGHTCYAN", Replxx::Color::BRIGHTCYAN,
		"WHITE", Replxx::Color::WHITE,
		"NORMAL", Replxx::Color::NORMAL,
		"DEFAULT", Replxx::Color::DEFAULT,
		"ERROR", Replxx::Color::ERROR
	);

	lua["replxx"]["keys"] = lua.create_table_with(
		"ESCAPE",      (int32_t)Replxx::KEY::ESCAPE,
		"PAGE_UP",     (int32_t)Replxx::KEY::PAGE_UP,
		"PAGE_DOWN",   (int32_t)Replxx::KEY::PAGE_DOWN,
		"DOWN",        (int32_t)Replxx::KEY::DOWN, 
		"UP",          (int32_t)Replxx::KEY::UP,
		"LEFT",        (int32_t)Replxx::KEY::LEFT,
		"RIGHT",       (int32_t)Replxx::KEY::RIGHT,
		"HOME",        (int32_t)Replxx::KEY::HOME,
		"END",         (int32_t)Replxx::KEY::END,
		"DELETE",      (int32_t)Replxx::KEY::DELETE,
		"INSERT",      (int32_t)Replxx::KEY::INSERT,
		"F1",          (int32_t)Replxx::KEY::F1,
		"F2",          (int32_t)Replxx::KEY::F2,
		"F3",          (int32_t)Replxx::KEY::F3,
		"F4",          (int32_t)Replxx::KEY::F4,
		"F5",          (int32_t)Replxx::KEY::F5,
		"F6",          (int32_t)Replxx::KEY::F6,
		"F7",          (int32_t)Replxx::KEY::F7,
		"F8",          (int32_t)Replxx::KEY::F8,
		"F9",          (int32_t)Replxx::KEY::F9,
		"F10",         (int32_t)Replxx::KEY::F10,
		"F11",         (int32_t)Replxx::KEY::F11,
		"F12",         (int32_t)Replxx::KEY::F12,
		"F13",         (int32_t)Replxx::KEY::F13,
		"F14",         (int32_t)Replxx::KEY::F14,
		"F15",         (int32_t)Replxx::KEY::F15,
		"F16",         (int32_t)Replxx::KEY::F16,
		"F17",         (int32_t)Replxx::KEY::F17,
		"F18",         (int32_t)Replxx::KEY::F18,
		"F19",         (int32_t)Replxx::KEY::F19,
		"F20",         (int32_t)Replxx::KEY::F20,
		"F21",         (int32_t)Replxx::KEY::F21,
		"F22",         (int32_t)Replxx::KEY::F22,
		"F23",         (int32_t)Replxx::KEY::F23,
		"F24",         (int32_t)Replxx::KEY::F24,
		"MOUSE",       (int32_t)Replxx::KEY::MOUSE,     
		"PASTE_START", (int32_t)Replxx::KEY::PASTE_START,
		"PASTE_FINISH",(int32_t)Replxx::KEY::PASTE_FINISH,
		"BACKSPACE",   (int32_t)Replxx::KEY::BACKSPACE,
		"ENTER",       (int32_t)Replxx::KEY::ENTER,
		"TAB",         (int32_t)Replxx::KEY::TAB
	);

	lua["replxx"]["keys"]["control"] = [](char v) { return (int32_t)Replxx::KEY::control(v); };
	lua["replxx"]["keys"]["shift"]   = [](char v) { return (int32_t)Replxx::KEY::shift(v); };
	lua["replxx"]["keys"]["meta"]    = [](char v) { return (int32_t)Replxx::KEY::meta(v); };

	lua.new_usertype<replxx::Replxx::Completion>(
		"Completion", sol::constructors<
			replxx::Replxx::Completion(std::string),
			replxx::Replxx::Completion(std::string, replxx::Replxx::Color)
		>()
	);
}