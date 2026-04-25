#include "core/core.hpp"

#include "include.hpp"

#include "roblox/sdk/class/roblox.hpp"


int
main( ){

	bool status = core::init( L"RobloxPlayerBeta.exe", false , true ); // target_name , use_driver , need printf_info ( name , pid , base ) 
	if( !status ){
		printf("trouble attach\n");
		std::this_thread::sleep_for( std::chrono::seconds( 2 ) );
	}
	std::this_thread::sleep_for( std::chrono::seconds( 2 ) );
	return 0;
}