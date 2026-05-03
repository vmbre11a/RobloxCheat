#pragma once

#include <iostream>

#include <imgui/imgui.h>

#include <roblox/sdk/class/render.hpp>

namespace
	features{

	namespace 
		esp{

		using imvec2 = ImVec2;	
		using imdraw_list = ImDrawList;
		using imcolor = ImColor;


		class wallhack_t{
		private:
			
			void draw_2d_box( imdraw_list* draw , imvec2 top_left , imvec2 bottom_right , imcolor color );
			void draw_2d_filled_box( imdraw_list* draw , imvec2 top_left , imvec2 bottom_right , imcolor color );



			void draw_box( imdraw_list* draw , imvec2 top_left , imvec2 bottom_right , imcolor );

		public: 
			void main_loop( );

			void main_loop( sdk::render::render_t render );


		};
	
		inline std::unique_ptr< wallhack_t> whack = std::make_unique< wallhack_t >( );
	} // esp



} // features


