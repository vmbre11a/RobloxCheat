#pragma once

#include "../global/definition.hpp"


namespace 
	core{


	// main start program ( create driver , init ioctl_cde ) 
	NTSTATUS real_entry( PDRIVER_OBJECT driver , PUNICODE_STRING reg_path );


} // core
