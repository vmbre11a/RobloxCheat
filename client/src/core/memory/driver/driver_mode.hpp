#pragma once

#include <include.hpp> 

#include <roblox/sdk/math/vec2.hpp>

namespace
	mem_driver{

	namespace
		utils{ 
		inline std::uint64_t get_process_id_by_name( const wchar_t* name ){
			std::uint64_t pid{ };

			return pid;	
		}

		inline std::uintptr_t get_module_by_name( const std::uint64_t pid , const wchar_t* name ) {
			std::uintptr_t base{ };
			
			return base;
		}
	} // utils

	template< typename T > 
	T rpm_driver( const std::uintptr_t addr ){
		return {};
	}

	inline void rpm_driver_buffer( const std::uintptr_t addr , void* out , size_t size ) {

	};

	inline void mouse_move_driver( float x , float ){

	}
	inline sdk::geom::i_vec2 get_mouse_pos_driver( ){
		return{ };
	}
}// mem_driver
