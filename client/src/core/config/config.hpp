#pragma once

#include <imgui/imgui.h>


namespace
	config{

	namespace
		esp{
		
		using imvec4 = ImVec4;


		struct esp_config{
	
			bool player = false;

			bool player_box = false;

			
		
			imvec4 c_player_box = { 255 , 255 , 255 , 255 };

		};// esp_config

		inline esp_config esp;
	} // esp


} // config
