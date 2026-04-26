#pragma once

#include <imgui/imgui.h>

#include <core/config/config.hpp>

namespace
	cache{


	namespace
		color{

		using imcolor = ImColor;


		inline imcolor player_box;

		inline bool dirty = true;


		inline void dirty_make( ){ dirty = true; }

		inline void update( ){
			const auto& color = config::esp::esp;

			player_box = ImGui::ColorConvertFloat4ToU32( color.c_player_box );				

			dirty = false;
		}

	} // color


} // cache



