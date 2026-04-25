#pragma once

#include <imgui/imgui.h>


namespace
	config{

	namespace
		esp{

		struct esp_config{
	
			bool player = false;

			bool player_box = false;

		};// esp_config

		inline esp_config esp;
	} // esp


} // config
