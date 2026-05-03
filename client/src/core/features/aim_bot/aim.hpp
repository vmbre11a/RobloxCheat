#pragma once

#include <iostream> 

#include <roblox/sdk/class/render.hpp>

namespace
	features{

	namespace
		aim{
		
		class aimbot_t{
		private:

		public:
		
			void main_loop( );
		
			void main_loop( sdk::render::render_t render );
		
		
		}; // aimbot_t

	
		inline std::unique_ptr< aimbot_t > aim = std::make_unique< aimbot_t > ( );
	
	} // aim

} // features


