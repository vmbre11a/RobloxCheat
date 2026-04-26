#include "../esp.hpp"


void features::esp::wallhack_t::draw_2d_box( imdraw_list* draw , imvec2 left_t , imvec2 right_b , imcolor color ){
	draw->AddRect( left_t , right_b , color );
}


