#pragma once
#include "PixelGameEngine_api.hpp"
#include "sol.hpp"

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

extern "C" {
	struct lua_State;
}

inline std::unique_ptr<sol::state_view> lua;

namespace PixelGameEngine_wrapper {

	class LuaWrapper final : public olc::PixelGameEngine {
	public:
		explicit LuaWrapper(const std::string& app_name) {
			sAppName = app_name;
		}

		~LuaWrapper() override {
			lua.reset();
			printf("Released lua state from module\n");
		}

		void PrintConsole(const std::string& msg, const olc::Key exit_key, const bool suspend) {

			if (!IsConsoleShowing()) {
				ConsoleShow(exit_key, suspend);
			}

			ConsoleOut() << "[Lua]: " << msg << std::endl;
		}

		bool OnUserCreate() override {
			sol::optional<sol::function> create = (*lua)["OnUserCreate"];
			if (!create) {
				printf("[Error]: you must provide an 'OnUserCreate' method\n");
				return false;
			}

			const auto result = (*create)();
			if (!result.valid()) {
				const sol::error err = result;
				printf("[Error]: %s", err.what());
				return false;
			}

			if (result.get_type() != sol::type::boolean) {
				printf("[Error]: method 'OnUserCreate' must return a boolean\n");
				return false;
			}

			return result.get<bool>();
		}

		bool OnUserUpdate(float f_elapsed_time) override {
			sol::optional<sol::function> update = (*lua)["OnUserUpdate"];
			if (!update) {
				printf("[Error]: you must provide an 'OnUserUpdate' method\n");
				return false;
			}

			const auto result = (*update)(f_elapsed_time);
			if (!result.valid()) {
				const sol::error err = result;
				printf("[Error]: %s", err.what());
				return false;
			}

			if (result.get_type() != sol::type::boolean) {
				printf("[Error]: method 'OnUserUpdate' must return a boolean\n");
				return false;
			}

			return result.get<bool>();
		}

		bool OnUserDestroy() override {
			sol::optional<sol::function> destroy = (*lua)["OnUserDestroy"];
			if (!destroy)
				return true;

			const auto result = (*destroy)();
			if (!result.valid()) {
				const sol::error err = result;
				printf("[Error]: %s", err.what());
				return false;
			}

			if (result.get_type() != sol::type::boolean) {
				printf("[Error]: method 'OnUserDestroy' must return a boolean\n");
				return false;
			}

			return result.get<bool>();
		}
	};

} // namespace PixelGameEngine_wrapper

extern "C" MY_OBJECT_API int luaopen_LuaPixelGameEngine(lua_State * L);