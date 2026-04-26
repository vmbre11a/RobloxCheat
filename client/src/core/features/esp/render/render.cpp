#include "../esp.hpp"

#include <core/config/config.hpp>

void features::esp::wallhack_t::draw_2d_box( imdraw_list* draw , imvec2 left_t , imvec2 right_b , imcolor color ){
	draw->AddRect( left_t , right_b , color );
}

void features::esp::wallhack_t::draw_2d_filled_box( imdraw_list* draw , imvec2 left_t , imvec2 right_b , imcolor color){
	color.Value.w = config::esp::esp.player_box_filled;
	draw->AddRectFilled( left_t , right_b , color );
}
