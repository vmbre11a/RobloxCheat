#pragma once

#include "../../offset.hpp"

#include "../math/cframe.hpp"

#include "../math/vec2.hpp"

#include "../math/vec4.hpp"

#include "../math/mat4.hpp"


namespace
	sdk{


	namespace
		instance{

		class instance_t{
		private:

		public:
			std::uintptr_t self{ };

			instance_t( const std::uintptr_t _self ) : self( _self ){ }
			instance_t( ) = default;
			~instance_t( ) = default;

			std::string get_name( ){
				std::uintptr_t name = memory::mem->rpm< std::uintptr_t >( self + Offsets::Instance::Name );
				if( !name ) return { };
				return memory::mem->rpm_str( name );
			}

			std::string get_class( ){
				std::uintptr_t desc = memory::mem->rpm< std::uintptr_t >( self + Offsets::Instance::ClassDescriptor );
				if( !desc ) return{ };
				std::uintptr_t name = memory::mem->rpm< std::uintptr_t >( desc + Offsets::Instance::ClassName );
				return memory::mem->rpm_str( name );
			}
			
			std::uintptr_t get_primitive( ){
				return memory::mem->rpm< std::uintptr_t >( 
					self + Offsets::BasePart::Primitive );
			}

			geom::vec3 get_pos( ){
				std::uintptr_t primitive = get_primitive( );
				return memory::mem->rpm< geom::vec3 >( 
					primitive + Offsets::Primitive::Position );
			}

			float get_distance( const geom::vec3& target ) {
				auto current = get_pos( );
				return ( current - target ).get_length( );
			}

			instance_t get_model_ref( ){
				return instance_t( memory::mem->rpm< std::uintptr_t >( 
					self + Offsets::Player::ModelInstance ) );			
			}

			instance_t get_parent( ){
				return instance_t( memory::mem->rpm< std::uintptr_t >( self + Offsets::Instance::Parent ) );	
			}

			std::vector< instance_t > get_childs( ){
				std::vector< instance_t > childs{ };

				std::uintptr_t start = memory::mem->rpm< std::uintptr_t >( self + Offsets::Instance::ChildrenStart );
				std::uintptr_t end =  memory::mem->rpm< std::uintptr_t >( start + Offsets::Instance::ChildrenEnd );

				for( std::uintptr_t ptr = memory::mem->rpm< std::uintptr_t >( start ) ; ptr != end ; ptr += 0x10 ){
					std::uintptr_t child = memory::mem->rpm< std::uintptr_t >( ptr );
					childs.emplace_back( child );
				}

				return childs;
			}

			instance_t get_by_name( const std::string& target_name ){
				auto child = this->get_childs( );
				for( auto& c : child ){
					if( c.get_name( ) == target_name ) 
						return c;
				}
				return instance_t{ };
			}

			instance_t get_by_class( const std::string& target_name ){
				auto child = this->get_childs( );
				for( auto& c : child ){
					//printf("test: %s\n" , c.get_class( ).c_str( ) );
					if( c.get_class( ) == target_name )	
						return c;
				}
				return instance_t{ };
			}


			bool valid( ){
				return self != 0; 
			}
		};


	} // instance


} // sdk


