#include "aim.hpp"

#include <core/config/config.hpp>

#include <roblox/sdk/cache/player_cache.hpp>

#include <roblox/sdk/cache/color_cache.hpp>

void features::aim::aimbot_t::main_loop( ){
	sdk::render::render_t render( sdk::roblox::rbx->get_render_engine( )  );
	main_loop( render );
}

void features::aim::aimbot_t::main_loop( sdk::render::render_t render ){
	
	const auto& cfg = config::aim_bot::aim;
	
		
	sdk::geom::vec3 local_pos = sdk::instance::instance_t( 
		cache::player::local_player->character ).get_by_name( sdk::roblox::name::r6::head ).get_pos( ); 

	float best_dist = FLT_MAX;

	sdk::geom::vec2 best_pos{ };
	
	sdk::geom::i_vec2 mouse_pos = memory::mem->get_mouse_pos( );

	for( auto& player : cache::player::players ){
		if( player.second.is_local ) continue;
			
		auto entity = player.second;

		sdk::geom::vec3 target_pos = sdk::instance::instance_t( 
			entity.character ).get_by_name( sdk::roblox::name::r6::head ).get_pos( );
	
		float distance = ( local_pos - target_pos ).get_length( );
		if( distance > cfg.max_distance ) continue;

		
		sdk::geom::vec2 screen_pos{};
		if( !render.world_2_screen( target_pos , screen_pos ) ) continue;

		float dx = screen_pos.x - mouse_pos.x;
		float dy = screen_pos.y - mouse_pos.y;
		float dist_2d = sqrt( dx * dx + dy * dy );

		if( dist_2d < best_dist ){
		    best_dist = dist_2d;
		    best_pos = screen_pos;
		}
		

	} // for
	
	if( best_dist == FLT_MAX ) return; 

	float dx = best_pos.x - mouse_pos.x;
	float dy = best_pos.y - mouse_pos.y;
	
	float smooth_ = 1.0f / cfg.smoothing;
	memory::mem->set_mouse_pos( dx * smooth_, dy * smooth_ );

}
