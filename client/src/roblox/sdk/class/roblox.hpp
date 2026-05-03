#pragma once 

#include "render.hpp" // render.hpp include instance

#include "roblox_name.hpp"


namespace
	sdk{
	
	namespace 
		roblox{
		
		class roblox_t{
		private:
			instance::instance_t local_player{ };
			instance::instance_t data_model{ };
			instance::instance_t players{ };
			instance::instance_t workspace{ };
			instance::instance_t camera{ };
			render::render_t render_engine{ };	
		public:
			roblox_t( ) = default;
			~roblox_t( ) = default;

			bool init( const std::uintptr_t base){
				std::uintptr_t fake_data_model = memory::mem->rpm< std::uintptr_t >( base + Offsets::FakeDataModel::Pointer );
				if( !fake_data_model ){
					printf("[ - ] f_d_model: zero\n");
					return false;
				}
				data_model = memory::mem->rpm< std::uintptr_t >( fake_data_model + Offsets::FakeDataModel::RealDataModel );
				if( !data_model.valid( ) ){
					printf("[ - ] d_model: zero\n");
					return false;	
				}
				render_engine = memory::mem->rpm< std::uintptr_t >( base + Offsets::VisualEngine::Pointer );
				if( !render_engine.valid( ) ){
					printf("[ - ] render_engine: zero\n");
					return false;
				}
				workspace = data_model.get_by_class( name::work_space );
				if( !workspace.valid( ) ){
					printf("[ - ] wspace: zero\n");
					return false;
				}
				players = data_model.get_by_class( name::players );
				if( !players.valid( ) ){
					printf("[ - ] players: zero\n");
					return false;
				}	
				camera = workspace.get_by_class( name::camera );
				if( !camera.valid( ) ){
					printf("[ - ] camera: zero\n");
					return false;
				}
				local_player = memory::mem->rpm< std::uintptr_t >(players.self + Offsets::Player::LocalPlayer );
				if( !local_player.valid( ) ){
					printf("[ - ] l_player: zero\n");
					return false;
				}

				return true;
			}

			instance::instance_t& get_data_model( ) { return data_model; }
			instance::instance_t& get_players( ) { return players; }
			instance::instance_t& get_workspace( ) { return workspace; }
			instance::instance_t& get_camera( ) { return camera; }
			instance::instance_t& get_local_player( ) { return local_player; }
			render::render_t&	  get_render_engine( ){ return render_engine; }
		};   

	inline std::unique_ptr< roblox_t >rbx = std::make_unique< roblox_t >( );
	} // roblox

} // sdk 


