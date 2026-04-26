#pragma once

#include <imgui/imgui.h>


namespace
	config{

	namespace
		esp{
		
		using imvec4 = ImVec4;


		struct esp_config{
			// bool	
			bool player = false;

			bool player_box = false;
			
			// int
			int player_box_selected = 0;
	
			// float
			float player_box_filled = 0.5f;
			
			// color
			imvec4 c_player_box = { 255 , 255 , 255 , 255 };

		};// esp_config

		inline esp_config esp;
	} // esp


} // config
