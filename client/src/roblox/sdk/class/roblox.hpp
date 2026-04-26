#pragma once 
#include "render.hpp" // render.hpp include instance

namespace
	sdk{

	
	namespace 
		roblox{
	
		
		namespace 
			name{ 
			inline const char* work_space =			"Workspace";
			inline const char* players =			"Players";
			inline const char* camera =				"Camera";
			inline const char* humanoid =			"Humanoid";
			inline const char* hmd_root =			"HumanoidRootPart";
		}
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

			void init( const std::uintptr_t base){
				std::uintptr_t fake_data_model = memory::mem->rpm< std::uintptr_t >( base + offsets::FakeDataModelPointer );
				if( !fake_data_model ){
					printf("[ - ] f_d_model: zero\n");
					return;
				}
				data_model = memory::mem->rpm< std::uintptr_t >( fake_data_model + offsets::FakeDataModelToDataModel );
				if( !data_model.valid( ) ){
					printf("[ - ] d_model: zero\n");
					return;	
				}
				render_engine = memory::mem->rpm< std::uintptr_t >( base + offsets::VisualEnginePointer );
				if( !render_engine.valid( ) ){
					printf("[ - ] render_engine: zero\n");
					return;
				}
				workspace = data_model.get_by_class( name::work_space );
				if( !workspace.valid( ) ){
					printf("[ - ] wspace: zero\n");
					return;
				}
				players = data_model.get_by_class( name::players );
				if( !players.valid( ) ){
					printf("[ - ] players: zero\n");
					return;
				}	
				camera = workspace.get_by_class( name::camera );
				if( !camera.valid( ) ){
					printf("[ - ] camera: zero\n");
					return;
				}
				local_player = memory::mem->rpm< std::uintptr_t >(players.self + offsets::LocalPlayer );
				if( !local_player.valid( ) ){
					printf("[ - ] l_player: zero\n");
					return;
				}
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


