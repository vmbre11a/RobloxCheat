#pragma once

#include <include.hpp> 

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

}// mem_driver
