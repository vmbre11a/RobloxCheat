#include "core/core.hpp"



NTSTATUS driver_entry(
	PDRIVER_OBJECT driver , 
	PUNICODE_STRING reg_path
){


	return core::real_entry( driver ) ;
}