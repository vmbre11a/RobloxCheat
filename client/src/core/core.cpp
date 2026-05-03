#include "core.hpp"

#include "include.hpp"

#include "memory/memory.hpp"

#include "roblox/sdk/class/roblox.hpp"

#include "overlay/overlay.hpp"

#include <roblox/sdk/math/vec2.hpp>

namespace
	core{


	bool init( const wchar_t* process_name ,bool use_driver , bool print_process_info ) {

		memory::mem->set_memory_mode( use_driver );

		std::uint64_t pid = memory::mem->get_pid_by_name( process_name );
		if( !pid ){
			printf("[ - ] pid: 0x%X\n" , GetLastError( ) );
			return false;
		}

		memory::mem->set_process_id( pid );

		HANDLE h_process = OpenProcess( PROCESS_ALL_ACCESS , FALSE , pid );	

		memory::mem->set_process_handle( h_process );
			
		std::uintptr_t base = memory::mem->get_module_by_name( process_name );
		if( !base ){
			printf("[ - ] base: 0x%x\n" , GetLastError( ) );
			return false;
		}

		memory::mem->set_base( base );

		if( print_process_info )
			wprintf(L"[ ~ ] target_name: %ls\n[ ~ ] pid: %d\n[ ~ ] base: 0x%llx\n", 
				process_name , 
				static_cast< int >( pid ), 
				base );

		if( !sdk::roblox::rbx->init( base ) ){ // get base addr
			printf("[ - ] addr failed , maybe you no in place then need re-call \n");
		}	
		memory::mem->update_screen_size( );
		
		overlay::menu->render_loop( ); // start render ( main loop )

		return true;
	}	

}