#pragma once

#include "../offset.hpp"

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
				std::uintptr_t name = memory::mem->rpm< std::uintptr_t >( self + offsets::Name  );
				if( !name ) return { };
				return memory::mem->rpm_str( name );
			}

			std::string get_class( ){
				std::uintptr_t desc = memory::mem->rpm< std::uintptr_t >( self + offsets::ClassDescriptor );
				if( !desc ) return{ };
				std::uintptr_t name = memory::mem->rpm< std::uintptr_t >( desc + offsets::ClassDescriptorToClassName );
				return memory::mem->rpm_str( name );
			}

			std::vector< instance_t > get_childs( ){
				std::vector< instance_t > childs;

				std::uintptr_t start = memory::mem->rpm< std::uintptr_t >( self + offsets::Children );
				std::uintptr_t end =  memory::mem->rpm< std::uintptr_t >( start + offsets::ChildrenEnd );

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
				return instance_t( 0 );
			}

			instance_t get_by_class( const std::string& target_name ){
				auto child = this->get_childs( );
				for( auto& c : child ){
					if( c.get_class( ) == target_name )	
						return c;
				}
				return instance_t( 0 );
			}


			bool valid( ){
				return self != 0; 
			}
		};


	} // instance


} // sdk


