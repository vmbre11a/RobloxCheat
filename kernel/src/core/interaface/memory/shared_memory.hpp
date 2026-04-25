#pragma once

#include "global/definition.hpp"

#include "../interface.hpp"


namespace 
	interface{


	namespace
		shared_memory{
	
		PVOID g_shared_memory{ };
		HANDLE g_section{ };
		constexpr size_t g_shared_size = 4096;

		NTSTATUS create_shared_memory( ){
			NTSTATUS status{ };
			OBJECT_ATTRIBUTES oa{ };	
			LARGE_INTEGER size{ };

			UNICODE_STRING section_name = RTL_CONSTANT_STRING( name::section_name );
			
			InitializeObjectAttributes( &oa , &section_name , 
				OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE , 
				NULL , NULL);

			size.QuadPart = g_shared_size;

			status = ZwCreateSection( 
				&g_section , 
				SECTION_ALL_ACCESS,
				&oa,
				&size, 
				PAGE_READWRITE,
				SEC_COMMIT,
				NULL
			);
			if( !NT_SUCCESS( status ) ){
				log("[ - ] [SMEM] create section: %x\n" , status );
				return status;
			}

			SIZE_T view_size = g_shared_size;
			status = ZwMapViewOfSection(
				g_section,
				ZwCurrentProcess( ),
				&g_shared_memory,
				0,0, NULL,
				&view_size,
				ViewUnmap,
				0,
				PAGE_READWRITE
			);
			return status;
		} // create_shared_memory


		void cleanup( ){
			if( g_shared_memory ) ZwUnmapViewOfSection( ZwCurrentProcess( ) , g_shared_memory );
			if( g_section ) ZwClose( g_section );
		}
	
	} // shared_memory


} // interface
