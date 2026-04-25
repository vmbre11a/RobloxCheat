#pragma once

#include "global/definition.hpp"

#include "core/interaface/memory/shared_memory.hpp"

namespace
	interface{


	namespace
		utils{

		void driver_unload( PDRIVER_OBJECT driver ){
			UNREFERENCED_PARAMETER( driver );
			shared_memory::cleanup( );
		}

	} // utils

} // interface
