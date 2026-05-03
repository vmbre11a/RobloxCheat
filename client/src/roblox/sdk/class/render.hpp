#pragma once

#include "instance.hpp"

namespace
	sdk{

	namespace
		render{
	
			class render_t : public instance::instance_t{
			private:
		
			public:

				render_t( const std::uintptr_t _self ) : instance::instance_t( _self ){ }
				render_t( ) = default;
				~render_t( ) = default;

				geom::mat4 get_view_matrix( ){
					return memory::mem->rpm< geom::mat4 >(
						self  + Offsets::VisualEngine::ViewMatrix);
				}


				bool world_2_screen( const geom::vec3& world , geom::vec2& out  ){
					auto screen_size = memory::mem->get_screen_size( );
					
					auto view = get_view_matrix( );
					
					geom::vec4 q{ };
					
					q.x = ( world.x * view.data[ 0 ] ) + ( world.y * view.data[ 1 ] ) + 
						( world.z * view.data[ 2 ] ) + view.data[ 3 ];
	
					q.y = ( world.x * view.data[ 4 ] ) + ( world.y * view.data[ 5 ] ) +
						( world.z * view.data[ 6 ] ) + view.data[ 7 ];

					q.z = ( world.x * view.data[ 8 ] ) + ( world.y * view.data[ 9 ] ) +
						( world.z * view.data[ 10 ] ) +  view.data[ 11 ] ;

					q.w = ( world.x * view.data[ 12 ] ) + ( world.y * view.data[ 13 ] ) +
						( world.z * view.data[ 14 ] ) + view.data[ 15 ] ;

					if( q.w < 0.1f ) return false;

					geom::vec3 ndc{ };

					ndc.x = q.x / q.w;
					ndc.y = q.y / q.w;
					ndc.z = q.z / q.w;


					out.x = ( screen_size.x / 2.0f * ndc.x ) + ( screen_size.x / 2.0f );
					out.y = -( screen_size.y / 2.0f * ndc.y ) + ( screen_size.y / 2.0f );

					return true;
				} // w2s
				
			}; // class
	} // render
} // sdk


