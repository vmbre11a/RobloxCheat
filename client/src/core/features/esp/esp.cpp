#include "esp.hpp"

#include <roblox/sdk/cache/player_cache.hpp>

#include <roblox/sdk/cache/color_cache.hpp>

#include <core/memory/memory.hpp>

void features::esp::wallhack_t::main_loop( ){
	sdk::render::render_t render( sdk::roblox::rbx->get_render_engine( )  );
	main_loop( render );
}


void features::esp::wallhack_t::main_loop( sdk::render::render_t render ){

	const auto& esp = config::esp::esp;

	const auto& draw = ImGui::GetBackgroundDrawList( );

	for( auto& entity : cache::player::players ){
		if( entity.second.is_local ) continue;

		cache::player::player_cached player = entity.second;

		sdk::geom::vec2 feet_pos{ };
		sdk::geom::vec2 head_pos{ };

		auto character = sdk::instance::instance_t( player.character );

		sdk::geom::vec3 head = character.get_by_name( sdk::roblox::name::r6::head ).get_pos( );
		sdk::geom::vec3 feet = character.get_by_name( sdk::roblox::name::r6::right_leg ).get_pos( );

		if( !render.world_2_screen( head , head_pos) ) continue;
		if( !render.world_2_screen( feet, feet_pos ) ) continue;

		float height = feet_pos.y - head_pos.y;
		float width  = height / 2.0f;
		
		imvec2 top_left     = { head_pos.x - width / 2.0f, head_pos.y };
		imvec2 bottom_right = { head_pos.x + width / 2.0f, feet_pos.y };

		if( esp.player_box ){
			draw_box( draw , top_left , bottom_right , cache::color::player_box );
		}
	}
}