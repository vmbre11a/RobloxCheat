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
			
			float player_max_distance = 300.0f;	
			// color
			imvec4 c_player_box = { 255 , 255 , 255 , 255 };

		};// esp_config

		inline esp_config esp;
	} // esp

	namespace
		aim_bot{

		struct aim_config{	
			// bool
			bool player = false;

			bool smooth = false;
			
			// int

			// float
			float max_distance = 300.0f;			
			
			float smoothing = 4.0f;

			// color
			

		};	// aim_config
	
		inline aim_config aim;
	} // aim_bot

} // config 