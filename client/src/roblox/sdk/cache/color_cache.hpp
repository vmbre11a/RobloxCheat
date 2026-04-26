#pragma once

#include <imgui/imgui.h>

#include <core/config/config.hpp>

namespace
	cache{


	namespace
		color{

		inline ImColor player_box;

		inline bool dirty = true;


		inline void dirty_make( ){ dirty = true; }

		inline void update( ){
			//player_box = ImGui::ColorConvertFloat4ToU32( );				

		}

	} // color


} // cache



