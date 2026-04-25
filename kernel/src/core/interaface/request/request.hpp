#pragma once

#include "global/definition.hpp"

namespace
	interface{

	namespace
		request{
	
		NTSTATUS
			invalid_device( PDEVICE_OBJECT device , PIRP irp ){
	
			UNREFERENCED_PARAMETER( device );
			irp->IoStatus.Information = 0;
			irp->IoStatus.Status = STATUS_INVALID_DEVICE_REQUEST;
			IoCompleteRequest( irp , IO_NO_INCREMENT );
			return irp->IoStatus.Status;
		}
		
			
		NTSTATUS
			succes_device( PDEVICE_OBJECT device , PIRP irp ){
		
			UNREFERENCED_PARAMETER( device );
			irp->IoStatus.Information = 0;
			irp->IoStatus.Status = STATUS_SUCCESS;
			IoCompleteRequest( irp , IO_NO_INCREMENT );
			return irp->IoStatus.Status;
		}

	} // request



} // interface
