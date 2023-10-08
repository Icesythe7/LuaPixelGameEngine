#include "PixelGameEngine_wrapper.hpp"

namespace PixelGameEngine_wrapper {

	void open_engine(sol::this_state L) {
		lua = std::make_shared<sol::state_view>(L);

		// Globals 
		lua->set("PixelF", &olc::PixelF);
		lua->set("PixelLerp", &olc::PixelLerp);

		// LayerDesc
		lua->new_usertype<olc::LayerDesc>(
			sol::no_constructor,
			"vOffset", &olc::LayerDesc::vOffset,
			"vScale", &olc::LayerDesc::vScale,
			"bShow", &olc::LayerDesc::bShow,
			"bUpdate", &olc::LayerDesc::bUpdate,
			"pDrawTarget", &olc::LayerDesc::pDrawTarget,
			"nResID", &olc::LayerDesc::nResID,
			"vecDecalInstance", &olc::LayerDesc::vecDecalInstance,
			"tint", &olc::LayerDesc::tint,
			"funcHook", &olc::LayerDesc::funcHook
		);

		lua->new_usertype<olc::Pixel>("Pixel",
			sol::constructors<olc::Pixel(),
			olc::Pixel(uint32_t),
			olc::Pixel(uint8_t, uint8_t, uint8_t, uint8_t)>(),
			"n", &olc::Pixel::n,
			"a", &olc::Pixel::a,
			"r", &olc::Pixel::r,
			"g", &olc::Pixel::g,
			"b", &olc::Pixel::b,
			"inv", &olc::Pixel::inv,
			sol::meta_function::equal_to, &olc::Pixel::operator==,
			sol::meta_function::division, &olc::Pixel::operator/,
			sol::meta_function::addition, &olc::Pixel::operator+,
			sol::meta_function::subtraction, &olc::Pixel::operator-,
			sol::meta_function::multiplication, sol::overload(sol::resolve<olc::Pixel(float)const>(&olc::Pixel::operator*), sol::resolve<olc::Pixel(const olc::Pixel&)const>(&olc::Pixel::operator*))
		);

		lua->create_named_table("Color",
			"GREY", &olc::GREY,
			"DARK_GREY", &olc::DARK_GREY,
			"VERY_DARK_GREY", &olc::VERY_DARK_GREY,
			"RED", &olc::RED,
			"DARK_RED", &olc::DARK_RED,
			"VERY_DARK_RED", &olc::VERY_DARK_RED,
			"YELLOW", &olc::YELLOW,
			"DARK_YELLOW", &olc::DARK_YELLOW,
			"VERY_DARK_YELLOW", &olc::VERY_DARK_YELLOW,
			"GREEN", &olc::GREEN,
			"DARK_GREEN", &olc::DARK_GREEN,
			"VERY_DARK_GREEN", &olc::VERY_DARK_GREEN,
			"CYAN", &olc::CYAN,
			"DARK_CYAN", &olc::DARK_CYAN,
			"VERY_DARK_CYAN", &olc::VERY_DARK_CYAN,
			"BLUE", &olc::BLUE,
			"DARK_BLUE", &olc::DARK_BLUE,
			"VERY_DARK_BLUE", olc::VERY_DARK_BLUE,
			"MAGENTA", &olc::MAGENTA,
			"DARK_MAGENTA", &olc::DARK_MAGENTA,
			"VERY_DARK_MAGENTA", olc::VERY_DARK_MAGENTA,
			"WHITE", &olc::WHITE,
			"BLACK", &olc::BLACK,
			"BLANK", &olc::BLANK
		);

		lua->new_enum<olc::Pixel::Mode>("PixelMode", {
			{"NORMAL", olc::Pixel::Mode::NORMAL},
			{"MASK", olc::Pixel::Mode::MASK},
			{"ALPHA", olc::Pixel::Mode::ALPHA},
			{"CUSTOM", olc::Pixel::Mode::CUSTOM},
		});

		lua->new_usertype<olc::HWButton>(sol::no_constructor,
			"bPressed", sol::readonly_property(&olc::HWButton::bPressed),
			"bReleased", sol::readonly_property(&olc::HWButton::bReleased),
			"bHeld", sol::readonly_property(&olc::HWButton::bHeld)
		);

		lua->new_usertype<olc::vi2d>("vi2d",
			sol::constructors<olc::vi2d(), olc::vi2d(int32_t, int32_t)>(),
			"x", &olc::vi2d::x,
			"y", &olc::vi2d::y,
			"mag", &olc::vi2d::mag,
			"mag2", &olc::vi2d::mag2,
			"norm", &olc::vi2d::norm,
			"perp", &olc::vi2d::perp,
			"floor", &olc::vi2d::floor,
			"ceil", &olc::vi2d::ceil,
			"max", &olc::vi2d::max,
			"min", &olc::vi2d::min,
			"cart", &olc::vi2d::cart,
			"polar", &olc::vi2d::polar,
			"clamp", &olc::vi2d::clamp,
			"lerp", &olc::vi2d::lerp,
			"dot", &olc::vi2d::dot,
			"cross", &olc::vi2d::cross,
			sol::meta_function::to_string, &olc::vi2d::str,
			sol::meta_function::addition, sol::overload(sol::resolve<olc::vi2d(const olc::vi2d&)const>(&olc::vi2d::operator+), sol::resolve<olc::vi2d()const>(&olc::vi2d::operator+)),
			sol::meta_function::subtraction, sol::overload(sol::resolve<olc::vi2d(const olc::vi2d&)const>(&olc::vi2d::operator-), sol::resolve<olc::vi2d()const>(&olc::vi2d::operator-)),
			sol::meta_function::multiplication, sol::overload(sol::resolve<olc::vi2d(const int32_t&)const>(&olc::vi2d::operator*), sol::resolve<olc::vi2d(const olc::vi2d&)const>(&olc::vi2d::operator*)),
			sol::meta_function::division, sol::overload(sol::resolve<olc::vi2d(const int32_t&)const>(&olc::vi2d::operator/), sol::resolve<olc::vi2d(const olc::vi2d&)const>(&olc::vi2d::operator/)),
			sol::meta_function::equal_to, &olc::vi2d::operator==
		);

		lua->new_usertype<olc::vu2d>("vu2d",
			sol::constructors<olc::vu2d(), olc::vu2d(uint32_t, uint32_t)>(),
			"x", &olc::vu2d::x,
			"y", &olc::vu2d::y,
			"mag", &olc::vu2d::mag,
			"mag2", &olc::vu2d::mag2,
			"norm", &olc::vu2d::norm,
			"perp", &olc::vu2d::perp,
			"floor", &olc::vu2d::floor,
			"ceil", &olc::vu2d::ceil,
			"max", &olc::vu2d::max,
			"min", &olc::vu2d::min,
			"cart", &olc::vu2d::cart,
			"polar", &olc::vu2d::polar,
			"clamp", &olc::vu2d::clamp,
			"lerp", &olc::vu2d::lerp,
			"dot", &olc::vu2d::dot,
			"cross", &olc::vu2d::cross,
			sol::meta_function::to_string, &olc::vu2d::str,
			sol::meta_function::addition, sol::overload(sol::resolve<olc::vu2d(const olc::vu2d&)const>(&olc::vu2d::operator+), sol::resolve<olc::vu2d()const>(&olc::vu2d::operator+)),
			sol::meta_function::subtraction, sol::overload(sol::resolve<olc::vu2d(const olc::vu2d&)const>(&olc::vu2d::operator-), sol::resolve<olc::vu2d()const>(&olc::vu2d::operator-)),
			sol::meta_function::multiplication, sol::overload(sol::resolve<olc::vu2d(const uint32_t&)const>(&olc::vu2d::operator*), sol::resolve<olc::vu2d(const olc::vu2d&)const>(&olc::vu2d::operator*)),
			sol::meta_function::division, sol::overload(sol::resolve<olc::vu2d(const uint32_t&)const>(&olc::vu2d::operator/), sol::resolve<olc::vu2d(const olc::vu2d&)const>(&olc::vu2d::operator/)),
			sol::meta_function::equal_to, &olc::vu2d::operator==
		);

		lua->new_usertype<olc::vf2d>("vf2d",
			sol::constructors<olc::vf2d(), olc::vf2d(float, float)>(),
			"x", &olc::vf2d::x,
			"y", &olc::vf2d::y,
			"mag", &olc::vf2d::mag,
			"mag2", &olc::vf2d::mag2,
			"norm", &olc::vf2d::norm,
			"perp", &olc::vf2d::perp,
			"floor", &olc::vf2d::floor,
			"ceil", &olc::vf2d::ceil,
			"max", &olc::vf2d::max,
			"min", &olc::vf2d::min,
			"cart", &olc::vf2d::cart,
			"polar", &olc::vf2d::polar,
			"clamp", &olc::vf2d::clamp,
			"lerp", &olc::vf2d::lerp,
			"dot", &olc::vf2d::dot,
			"cross", &olc::vf2d::cross,
			sol::meta_function::to_string, &olc::vf2d::str,
			sol::meta_function::addition, sol::overload(sol::resolve<olc::vf2d(const olc::vf2d&)const>(&olc::vf2d::operator+), sol::resolve<olc::vf2d()const>(&olc::vf2d::operator+)),
			sol::meta_function::subtraction, sol::overload(sol::resolve<olc::vf2d(const olc::vf2d&)const>(&olc::vf2d::operator-), sol::resolve<olc::vf2d()const>(&olc::vf2d::operator-)),
			sol::meta_function::multiplication, sol::overload(sol::resolve<olc::vf2d(const float&)const>(&olc::vf2d::operator*), sol::resolve<olc::vf2d(const olc::vf2d&)const>(&olc::vf2d::operator*)),
			sol::meta_function::division, sol::overload(sol::resolve<olc::vf2d(const float&)const>(&olc::vf2d::operator/), sol::resolve<olc::vf2d(const olc::vf2d&)const>(&olc::vf2d::operator/)),
			sol::meta_function::equal_to, &olc::vf2d::operator==
		);

		lua->new_usertype<olc::vd2d>("vd2d",
			sol::constructors<olc::vd2d(), olc::vd2d(double, double)>(),
			"x", &olc::vd2d::x,
			"y", &olc::vd2d::y,
			"mag", &olc::vd2d::mag,
			"mag2", &olc::vd2d::mag2,
			"norm", &olc::vd2d::norm,
			"perp", &olc::vd2d::perp,
			"floor", &olc::vd2d::floor,
			"ceil", &olc::vd2d::ceil,
			"max", &olc::vd2d::max,
			"min", &olc::vd2d::min,
			"cart", &olc::vd2d::cart,
			"polar", &olc::vd2d::polar,
			"clamp", &olc::vd2d::clamp,
			"lerp", &olc::vd2d::lerp,
			"dot", &olc::vd2d::dot,
			"cross", &olc::vd2d::cross,
			sol::meta_function::to_string, &olc::vd2d::str,
			sol::meta_function::addition, sol::overload(sol::resolve<olc::vd2d(const olc::vd2d&)const>(&olc::vd2d::operator+), sol::resolve<olc::vd2d()const>(&olc::vd2d::operator+)),
			sol::meta_function::subtraction, sol::overload(sol::resolve<olc::vd2d(const olc::vd2d&)const>(&olc::vd2d::operator-), sol::resolve<olc::vd2d()const>(&olc::vd2d::operator-)),
			sol::meta_function::multiplication, sol::overload(sol::resolve<olc::vd2d(const double&)const>(&olc::vd2d::operator*), sol::resolve<olc::vd2d(const olc::vd2d&)const>(&olc::vd2d::operator*)),
			sol::meta_function::division, sol::overload(sol::resolve<olc::vd2d(const double&)const>(&olc::vd2d::operator/), sol::resolve<olc::vd2d(const olc::vd2d&)const>(&olc::vd2d::operator/)),
			sol::meta_function::equal_to, &olc::vd2d::operator==
		);

		lua->new_usertype<olc::Sprite>("Sprite",
			sol::constructors<olc::Sprite(),
			olc::Sprite(const std::string&, olc::ResourcePack*),
			olc::Sprite(int32_t, int32_t)>(),
			"LoadFromFile", &olc::Sprite::LoadFromFile,
			"width", &olc::Sprite::width,
			"height", &olc::Sprite::height
		);

		lua->new_enum<olc::Sprite::Mode>("SpriteMode", {
			{"NORMAL", olc::Sprite::Mode::NORMAL},
			{"PERIODIC", olc::Sprite::Mode::PERIODIC},
			{"CLAMP", olc::Sprite::Mode::CLAMP},
			});

		lua->new_enum<olc::Sprite::Flip>("SpriteFlip", {
			{"NONE", olc::Sprite::Flip::NONE},
			{"HORIZ", olc::Sprite::Flip::HORIZ},
			{"VERT", olc::Sprite::Flip::VERT},
			});

		lua->new_usertype<LuaWrapper>("PixelGameEngine",
			sol::constructors<LuaWrapper(const std::string&)>(),
			"PrintConsole", &LuaWrapper::PrintConsole,
			"Construct", &LuaWrapper::Construct,
			"SetScreenSize", &LuaWrapper::SetScreenSize,
			"Start", &LuaWrapper::Start,
			//"SetDrawTarget", &LuaWrapper::SetDrawTarget, // fix for overload
			"EnableLayer", &LuaWrapper::EnableLayer,
			"SetLayerOffset", &LuaWrapper::SetLayerOffset,
			"SetLayerOffsetV", &LuaWrapper::SetLayerOffset2,
			"SetLayerScale", &LuaWrapper::SetLayerScale,
			"SetLayerScaleV", &LuaWrapper::SetLayerScale2,
			"SetLayerTint", &LuaWrapper::SetLayerTint,
			"SetLayerCustomRenderFunction", &LuaWrapper::SetLayerCustomRenderFunction,
			//"GetLayers", &LuaWrapper::GetLayers, // fix for table
			"CreateLayer", &LuaWrapper::CreateLayer,
			"GetDrawTarget", &LuaWrapper::GetDrawTarget,
			"GetDrawTargetWidth", &LuaWrapper::GetDrawTargetWidth,
			"GetDrawTargetHeight", &LuaWrapper::GetDrawTargetHeight,
			"GetFPS", &LuaWrapper::GetFPS,
			"IsFocused", &LuaWrapper::IsFocused,
			"GetKey", &LuaWrapper::GetKey,
			"GetMouse", &LuaWrapper::GetMouse,
			"GetMouseX", &LuaWrapper::GetMouseX,
			"GetMouseY", &LuaWrapper::GetMouseY,
			"GetMousePos", &LuaWrapper::GetMousePos,
			"GetMouseWheel", &LuaWrapper::GetMouseWheel,
			"ScreenWidth", &LuaWrapper::ScreenWidth,
			"ScreenHeight", &LuaWrapper::ScreenHeight,
			"GetElapsedTime", &LuaWrapper::GetElapsedTime,
			"GetWindowSize", &LuaWrapper::GetWindowSize,
			"GetPixelSize", &LuaWrapper::GetPixelSize,
			"GetScreenPixelSize", &LuaWrapper::GetScreenPixelSize,
			"GetScreenSize", &LuaWrapper::GetScreenSize,
			"GetWindowMouse", &LuaWrapper::GetWindowMouse,
			"DrawV", &LuaWrapper::Draw2,
			"Draw", &LuaWrapper::Draw,
			"DrawLineV", &LuaWrapper::DrawLine2,
			"DrawLine", &LuaWrapper::DrawLine,
			"DrawCircleV", &LuaWrapper::DrawCircle2,
			"DrawCircle", &LuaWrapper::DrawCircle,
			"FillCircleV", &LuaWrapper::FillCircle2,
			"FillCircle", &LuaWrapper::FillCircle,
			"DrawRectV", &LuaWrapper::DrawRect2,
			"DrawRect", &LuaWrapper::DrawRect,
			"Clear", &LuaWrapper::Clear,
			"ClearBuffer", &LuaWrapper::ClearBuffer,
			"GetFontSprite", &LuaWrapper::GetFontSprite,
			"ClipLineToScreen", &LuaWrapper::ClipLineToScreen,
			"EnablePixelTransfer", &LuaWrapper::EnablePixelTransfer,
			"FillRectV", &LuaWrapper::FillRect2,
			"FillRect", &LuaWrapper::FillRect,
			"DrawTriangleV", &LuaWrapper::DrawTriangle2,
			"DrawTriangle", &LuaWrapper::DrawTriangle,
			"FillTriangleV", &LuaWrapper::FillTriangle2,
			"FillTriangle", &LuaWrapper::FillTriangle,
			"FillTexturedTriangle", &LuaWrapper::FillTexturedTriangle,
			"FillTexturedPolygon", &LuaWrapper::FillTexturedPolygon,
			"DrawSpriteV", &LuaWrapper::DrawSprite2,
			"DrawSprite", &LuaWrapper::DrawSprite,
			"DrawPartialSpriteV", &LuaWrapper::DrawPartialSprite2,
			"DrawPartialSprite", &LuaWrapper::DrawPartialSprite,
			"SetDecalMode", &LuaWrapper::SetDecalMode,
			"SetDecalStructure", &LuaWrapper::SetDecalStructure,



			"DrawStringV", &LuaWrapper::DrawString2,
			"DrawString", &LuaWrapper::DrawString,
			"SetPixelMode", &LuaWrapper::SetPixelMode,
			"ConsoleShow", &LuaWrapper::ConsoleShow
		);

		lua->new_enum<olc::rcode>("rcode", {
			{"FAIL", olc::rcode::FAIL},
			{"OK", olc::rcode::OK},
			{"NO_FILE", olc::rcode::NO_FILE},
			});

		lua->new_enum<olc::Mouse>("Mouse", {
			{"LEFT", olc::Mouse::LEFT_BUTTON},
			{"RIGHT", olc::Mouse::RIGHT_BUTTON},
			{"MIDDLE", olc::Mouse::MIDDLE_BUTTON},
			});

		lua->new_enum<olc::Key>("Key", {
			{"NONE", olc::NONE},

			{"A", olc::A},
			{"B", olc::B},
			{"C", olc::C},
			{"D", olc::D},
			{"E", olc::E},
			{"F", olc::F},
			{"G", olc::G},
			{"H", olc::H},
			{"I", olc::I},
			{"J", olc::J},
			{"K", olc::K},
			{"L", olc::L},
			{"M", olc::M},
			{"N", olc::N},
			{"O", olc::O},
			{"P", olc::P},
			{"Q", olc::Q},
			{"R", olc::R},
			{"S", olc::S},
			{"T", olc::T},
			{"U", olc::U},
			{"V", olc::V},
			{"W", olc::W},
			{"X", olc::X},
			{"Y", olc::Y},
			{"Z", olc::Z},

			{"K0", olc::K0},
			{"K1", olc::K1},
			{"K2", olc::K2},
			{"K3", olc::K3},
			{"K4", olc::K4},
			{"K5", olc::K5},
			{"K6", olc::K6},
			{"K7", olc::K7},
			{"K8", olc::K8},
			{"K9", olc::K9},

			{"F1", olc::F1},
			{"F2", olc::F2},
			{"F3", olc::F3},
			{"F4", olc::F4},
			{"F5", olc::F5},
			{"F6", olc::F6},
			{"F7", olc::F7},
			{"F8", olc::F8},
			{"F9", olc::F9},
			{"F10", olc::F10},
			{"F11", olc::F11},
			{"F12", olc::F12},

			{"UP", olc::UP},
			{"DOWN", olc::DOWN},
			{"LEFT", olc::LEFT},
			{"RIGHT", olc::RIGHT},

			{"SPACE", olc::SPACE},
			{"TAB", olc::TAB},
			{"SHIFT", olc::SHIFT},
			{"CTRL", olc::CTRL},
			{"INS", olc::INS},
			{"DEL", olc::DEL},
			{"HOME", olc::HOME},
			{"END", olc::END},
			{"PGUP", olc::PGUP},
			{"PGDN", olc::PGDN},

			{"BACK", olc::BACK},
			{"ESCAPE", olc::ESCAPE},
			{"RETURN", olc::RETURN},
			{"ENTER", olc::ENTER},
			{"PAUSE", olc::PAUSE},
			{"SCROLL", olc::SCROLL},

			{"NP0", olc::NP0},
			{"NP1", olc::NP1},
			{"NP2", olc::NP2},
			{"NP3", olc::NP3},
			{"NP4", olc::NP4},
			{"NP5", olc::NP5},
			{"NP6", olc::NP6},
			{"NP7", olc::NP7},
			{"NP8", olc::NP8},
			{"NP9", olc::NP9},

			{"NP_MUL", olc::NP_MUL},
			{"NP_DIV", olc::NP_DIV},
			{"NP_ADD", olc::NP_ADD},
			{"NP_SUB", olc::NP_SUB},
			{"NP_DECIMAL", olc::NP_DECIMAL},
			{"PERIOD", olc::PERIOD},

			{"EQUALS", olc::EQUALS},
			{"COMMA", olc::COMMA},
			{"MINUS", olc::MINUS},

			{"OEM_1", olc::OEM_1},
			{"OEM_2", olc::OEM_2},
			{"OEM_3", olc::OEM_3},
			{"OEM_4", olc::OEM_4},
			{"OEM_5", olc::OEM_5},
			{"OEM_6", olc::OEM_6},
			{"OEM_7", olc::OEM_7},
			{"OEM_8", olc::OEM_8},

			{"CAPS_LOCK", olc::CAPS_LOCK},
			{"ENUM_END", olc::ENUM_END},
		});
	}

} // namespace PixelGameEngine_wrapper

extern "C" int luaopen_LuaPixelGameEngine(lua_State * L) {
	sol::stack::call_lua(L, 1, PixelGameEngine_wrapper::open_engine);
	return 0;
}