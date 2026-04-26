#include "../esp.hpp"

#include <core/config/config.hpp>

void features::esp::wallhack_t::draw_box( imdraw_list* draw , imvec2 left_t, imvec2 right_b , imcolor color){
	
	switch( config::esp::esp.player_box_selected ){
	case 0:{
		draw_2d_box( draw , left_t , right_b , color );
		break;
	}
	case 1:{
		draw_2d_filled_box( draw , left_t , right_b , color );
		break;
	}


	default: break;
	}

}


