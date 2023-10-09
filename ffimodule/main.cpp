#include "PixelGameEngine_wrapper.hpp"

namespace PixelGameEngine_wrapper {

	void open_engine(sol::this_state L) { 
		lua = std::make_unique<sol::state_view>(L);

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
#define FIELD(x) #x, &olc::vi2d::x
			FIELD(x),		FIELD(y),		FIELD(mag),
			FIELD(mag2),	FIELD(norm),	FIELD(perp),
			FIELD(floor),	FIELD(ceil),	FIELD(max),
			FIELD(min),		FIELD(cart),	FIELD(polar),
			FIELD(clamp),	FIELD(lerp),	FIELD(dot),
			FIELD(cross),
			sol::meta_function::to_string, &olc::vi2d::str,
			sol::meta_function::addition, sol::overload(sol::resolve<olc::vi2d(const olc::vi2d&)const>(&olc::vi2d::operator+), sol::resolve<olc::vi2d()const>(&olc::vi2d::operator+)),
			sol::meta_function::subtraction, sol::overload(sol::resolve<olc::vi2d(const olc::vi2d&)const>(&olc::vi2d::operator-), sol::resolve<olc::vi2d()const>(&olc::vi2d::operator-)),
			sol::meta_function::multiplication, sol::overload(sol::resolve<olc::vi2d(const int32_t&)const>(&olc::vi2d::operator*), sol::resolve<olc::vi2d(const olc::vi2d&)const>(&olc::vi2d::operator*)),
			sol::meta_function::division, sol::overload(sol::resolve<olc::vi2d(const int32_t&)const>(&olc::vi2d::operator/), sol::resolve<olc::vi2d(const olc::vi2d&)const>(&olc::vi2d::operator/)),
			sol::meta_function::equal_to, &olc::vi2d::operator==
#undef FIELD
		);

		lua->new_usertype<olc::vu2d>("vu2d",
			sol::constructors<olc::vu2d(), olc::vu2d(uint32_t, uint32_t)>(),
#define FIELD(x) #x, &olc::vu2d::x
			FIELD(x),		FIELD(y),		FIELD(mag),
			FIELD(mag2),	FIELD(norm),	FIELD(perp),
			FIELD(floor),	FIELD(ceil),	FIELD(max),
			FIELD(min),		FIELD(cart),	FIELD(polar),
			FIELD(clamp),	FIELD(lerp),	FIELD(dot),
			FIELD(cross),
			sol::meta_function::to_string, &olc::vu2d::str,
			sol::meta_function::addition, sol::overload(sol::resolve<olc::vu2d(const olc::vu2d&)const>(&olc::vu2d::operator+), sol::resolve<olc::vu2d()const>(&olc::vu2d::operator+)),
			sol::meta_function::subtraction, sol::overload(sol::resolve<olc::vu2d(const olc::vu2d&)const>(&olc::vu2d::operator-), sol::resolve<olc::vu2d()const>(&olc::vu2d::operator-)),
			sol::meta_function::multiplication, sol::overload(sol::resolve<olc::vu2d(const uint32_t&)const>(&olc::vu2d::operator*), sol::resolve<olc::vu2d(const olc::vu2d&)const>(&olc::vu2d::operator*)),
			sol::meta_function::division, sol::overload(sol::resolve<olc::vu2d(const uint32_t&)const>(&olc::vu2d::operator/), sol::resolve<olc::vu2d(const olc::vu2d&)const>(&olc::vu2d::operator/)),
			sol::meta_function::equal_to, &olc::vu2d::operator==
#undef FIELD
		);

		lua->new_usertype<olc::vf2d>("vf2d",
			sol::constructors<olc::vf2d(), olc::vf2d(float, float)>(),
#define FIELD(x) #x, &olc::vf2d::x
			FIELD(x),		FIELD(y),		FIELD(mag),
			FIELD(mag2),	FIELD(norm),	FIELD(perp),
			FIELD(floor),	FIELD(ceil),	FIELD(max),
			FIELD(min),		FIELD(cart),	FIELD(polar),
			FIELD(clamp),	FIELD(lerp),	FIELD(dot),
			FIELD(cross),
			sol::meta_function::to_string, &olc::vf2d::str,
			sol::meta_function::addition, sol::overload(sol::resolve<olc::vf2d(const olc::vf2d&)const>(&olc::vf2d::operator+), sol::resolve<olc::vf2d()const>(&olc::vf2d::operator+)),
			sol::meta_function::subtraction, sol::overload(sol::resolve<olc::vf2d(const olc::vf2d&)const>(&olc::vf2d::operator-), sol::resolve<olc::vf2d()const>(&olc::vf2d::operator-)),
			sol::meta_function::multiplication, sol::overload(sol::resolve<olc::vf2d(const float&)const>(&olc::vf2d::operator*), sol::resolve<olc::vf2d(const olc::vf2d&)const>(&olc::vf2d::operator*)),
			sol::meta_function::division, sol::overload(sol::resolve<olc::vf2d(const float&)const>(&olc::vf2d::operator/), sol::resolve<olc::vf2d(const olc::vf2d&)const>(&olc::vf2d::operator/)),
			sol::meta_function::equal_to, &olc::vf2d::operator==
#undef FIELD
		);

		lua->new_usertype<olc::vd2d>("vd2d",
			sol::constructors<olc::vd2d(), olc::vd2d(double, double)>(),
#define FIELD(x) #x, &olc::vd2d::x
			FIELD(x),		FIELD(y),		FIELD(mag),
			FIELD(mag2),	FIELD(norm),	FIELD(perp),
			FIELD(floor),	FIELD(ceil),	FIELD(max),
			FIELD(min),		FIELD(cart),	FIELD(polar),
			FIELD(clamp),	FIELD(lerp),	FIELD(dot),
			FIELD(cross),
			sol::meta_function::to_string, &olc::vd2d::str,
			sol::meta_function::addition, sol::overload(sol::resolve<olc::vd2d(const olc::vd2d&)const>(&olc::vd2d::operator+), sol::resolve<olc::vd2d()const>(&olc::vd2d::operator+)),
			sol::meta_function::subtraction, sol::overload(sol::resolve<olc::vd2d(const olc::vd2d&)const>(&olc::vd2d::operator-), sol::resolve<olc::vd2d()const>(&olc::vd2d::operator-)),
			sol::meta_function::multiplication, sol::overload(sol::resolve<olc::vd2d(const double&)const>(&olc::vd2d::operator*), sol::resolve<olc::vd2d(const olc::vd2d&)const>(&olc::vd2d::operator*)),
			sol::meta_function::division, sol::overload(sol::resolve<olc::vd2d(const double&)const>(&olc::vd2d::operator/), sol::resolve<olc::vd2d(const olc::vd2d&)const>(&olc::vd2d::operator/)),
			sol::meta_function::equal_to, &olc::vd2d::operator==
#undef FIELD
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
#define FIELD(x) #x, &LuaWrapper::x
			FIELD(PrintConsole),
			FIELD(Construct),
			FIELD(SetScreenSize),
			FIELD(Start),
			//FIELD(SetDrawTarget),
			FIELD(EnableLayer),
			FIELD(SetLayerOffset),
			FIELD(SetLayerOffsetV),
			FIELD(SetLayerScale),
			FIELD(SetLayerScaleV),
			FIELD(SetLayerTint),
			FIELD(SetLayerCustomRenderFunction),
			//FIELD(GetLayers),
			FIELD(CreateLayer),
			FIELD(GetDrawTarget),
			FIELD(GetDrawTargetWidth),
			FIELD(GetDrawTargetHeight),
			FIELD(GetFPS),
			FIELD(IsFocused),
			FIELD(GetKey),
			FIELD(GetMouse),
			FIELD(GetMouseX),
			FIELD(GetMouseY),
			FIELD(GetMousePos),
			FIELD(GetMouseWheel),
			FIELD(ScreenWidth),
			FIELD(ScreenHeight),
			FIELD(GetElapsedTime),
			FIELD(GetWindowSize),
			FIELD(GetPixelSize),
			FIELD(GetScreenPixelSize),
			FIELD(GetScreenSize),
			FIELD(GetWindowMouse),
			FIELD(DrawV),
			FIELD(Draw),
			FIELD(DrawLineV),
			FIELD(DrawLine),
			FIELD(DrawCircleV),
			FIELD(DrawCircle),
			FIELD(FillCircleV),
			FIELD(FillCircle),
			FIELD(DrawRectV),
			FIELD(DrawRect),
			FIELD(Clear),
			FIELD(ClearBuffer),
			FIELD(GetFontSprite),
			FIELD(ClipLineToScreen),
			FIELD(EnablePixelTransfer),
			FIELD(FillRectV),
			FIELD(FillRect),
			FIELD(DrawTriangleV),
			FIELD(DrawTriangle),
			FIELD(FillTriangleV),
			FIELD(FillTriangle),
			FIELD(FillTexturedTriangle),
			FIELD(FillTexturedPolygon),
			FIELD(DrawSpriteV),
			FIELD(DrawSprite),
			FIELD(DrawPartialSpriteV),
			FIELD(DrawPartialSprite),
			FIELD(SetDecalMode),
			FIELD(SetDecalStructure),


			FIELD(DrawStringV),
			FIELD(DrawString),
			FIELD(SetPixelMode),
			FIELD(ConsoleShow)
#undef FIELD
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
#define FIELD(x) {#x, olc::Key::x}
			FIELD(NONE),

			FIELD(A),FIELD(B),FIELD(C),FIELD(D),
			FIELD(E),FIELD(F),FIELD(G),FIELD(H),
			FIELD(I),FIELD(J),FIELD(K),FIELD(L),
			FIELD(M),FIELD(N),FIELD(O),FIELD(P),
			FIELD(Q),FIELD(R),FIELD(S),FIELD(T),
			FIELD(U),FIELD(V),FIELD(W),FIELD(X),
			FIELD(Y),FIELD(Z),

			FIELD(K0),FIELD(K1),FIELD(K2),FIELD(K3),
			FIELD(K4),FIELD(K5),FIELD(K6),FIELD(K7),
			FIELD(K8),FIELD(K9),

			FIELD(F1),FIELD(F2),FIELD(F3),FIELD(F4),
			FIELD(F5),FIELD(F6),FIELD(F7),FIELD(F8),
			FIELD(F9),FIELD(F10),FIELD(F11),FIELD(F12),

			FIELD(UP),FIELD(DOWN),FIELD(LEFT),FIELD(RIGHT),

			FIELD(SPACE),FIELD(TAB),FIELD(SHIFT),FIELD(CTRL),
			FIELD(INS),FIELD(DEL),FIELD(HOME),FIELD(END),
			FIELD(PGUP),FIELD(PGDN),

			FIELD(BACK),FIELD(ESCAPE),FIELD(RETURN),FIELD(ENTER),
			FIELD(PAUSE),FIELD(SCROLL),

			FIELD(NP0),FIELD(NP1),FIELD(NP2),FIELD(NP3),
			FIELD(NP4),FIELD(NP5),FIELD(NP6),FIELD(NP7),
			FIELD(NP8),FIELD(NP9),

			FIELD(NP_MUL),FIELD(NP_DIV),FIELD(NP_ADD),FIELD(NP_SUB),
			FIELD(NP_DECIMAL),

			FIELD(PERIOD),FIELD(EQUALS),FIELD(COMMA),FIELD(MINUS),

			FIELD(OEM_1),FIELD(OEM_2),FIELD(OEM_3),FIELD(OEM_4),
			FIELD(OEM_5),FIELD(OEM_6),FIELD(OEM_7),FIELD(OEM_8),

			FIELD(CAPS_LOCK),FIELD(ENUM_END),
#undef FIELD
		});
	}

} // namespace PixelGameEngine_wrapper

extern "C" int luaopen_LuaPixelGameEngine(lua_State * L) {
	sol::stack::call_lua(L, 1, PixelGameEngine_wrapper::open_engine);
	return 0;
}