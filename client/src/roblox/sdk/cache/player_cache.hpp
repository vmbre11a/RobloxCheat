#pragma once

#include "core/memory/memory.hpp"

#include <roblox/sdk/class/roblox.hpp>


namespace
	cache{

	namespace 
		player{


		struct player_cached{
			std::uintptr_t player{ };
			std::uintptr_t character{ };
			std::uintptr_t humanoid{ };
			std::uintptr_t root_part{ };
		
			std::string name{ };
			int max_health{ };	

			bool is_local{ };
		}; // player_cached

		inline std::unordered_map< std::string , player_cached > players;
		inline player_cached* local_player{ };

		inline void fill_cached( player_cached& c , std::string& name , sdk::instance::instance_t player ){
			auto character = player.get_model_ref( );
			c.character = character.self;
			if( !character.self ) return;
			c.humanoid = character.get_by_class( sdk::roblox::name::humanoid ).self;
			c.root_part = character.get_by_name( sdk::roblox::name::hmd_root ).self;
			c.max_health = memory::mem->rpm< int >( c.humanoid + offsets::MaxHealth );
		} // fill_cached

		inline void update( ){
			auto actors_list = sdk::roblox::rbx->get_players( ).get_childs( );
		
			std::unordered_set< std::string > active_name{ };
			// get all_player
			for( auto& actor : actors_list ){
				auto name = actor.get_name( );
				if( !name.empty( ) )
					active_name.insert( name );
			}
			// if have go delete	
			for( auto it = players.begin( ); it != players.end( ); ){
				if( active_name.find( it->first ) == active_name.end( ) )	
					it = players.erase( it );
				else
					++it;
			}

			auto your_name = sdk::roblox::rbx->get_local_player( ).get_name( );
			
			for( auto& actor : actors_list ){
				auto name = actor.get_name( );
				if( name.empty( ) ) continue;

				auto& cached = players[ name ];
				fill_cached( cached , name , actor );

				if( name == your_name ){
					cached.is_local = true;
					local_player = &cached;
				}
			}

		} // update
	
	} // player

} // cache
