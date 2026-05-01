#pragma once

#include "include.hpp"

#include <tlhelp32.h>



namespace
	mem_user{

	extern "C"{
	
		NTSTATUS 
			user_read_virtualmemory( 
				HANDLE process , 
				PVOID base , 
				PVOID buffer , 
				SIZE_T size , 
				PSIZE_T number_of_byte 
			);

		NTSTATUS 
			user_write_virtualmemory( 
				HANDLE process,
				PVOID base,
				PVOID buffer,
				SIZE_T size,
				PSIZE_T nubfer_of_written
			);

	} 

	namespace
		utils{

		inline std::uintptr_t get_module_by_name( const std::uint64_t pid , const wchar_t* name ){
			std::uintptr_t base{ };

			HANDLE snap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
			if( !snap || snap == INVALID_HANDLE_VALUE ) {
				printf("[ - ] [MEM] [USER] [MDL] snap: %d\n" , GetLastError( ) );
				return 0;
			}
			
			MODULEENTRY32W me{ };
			me.dwSize = sizeof( MODULEENTRY32W );
			
			Module32FirstW( snap , &me );

			do{
				if( wcscmp( name , me.szModule) == 0 ){
					base = ( std::uintptr_t )me.modBaseAddr;		
					CloseHandle( snap );
					return base;
				}
			}while( Module32NextW( snap , &me ) );

			if( snap ) CloseHandle( snap );
			return pid;
		} // get_module_by_name 

		inline std::uint64_t get_process_id_by_name( const wchar_t* name ){
			std::uint64_t pid{ };

			HANDLE snap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS , 0 );
			if( !snap || snap == INVALID_HANDLE_VALUE ) {
				printf("[ - ] [MEM] [USER] snap: %d\n" , GetLastError( ) );
				return 0;
			}

			PROCESSENTRY32W pe{ };
			pe.dwSize = sizeof( PROCESSENTRY32W );

			bool status = Process32FirstW( snap , &pe );

			do{
				if( wcscmp( name , pe.szExeFile) == 0 ){
					pid = pe.th32ProcessID;		
					CloseHandle( snap );
					return pid;
				}
			
			}while( Process32NextW( snap , &pe ) );

			if( snap ) CloseHandle( snap );
			return pid;
		} // get_pid_by_name



	}// utils

	template< typename T > 
	T rpm_user( HANDLE process , const std::uintptr_t addr){
		T buffer{ };
		mem_user::user_read_virtualmemory( process , ( LPVOID )addr , &buffer , sizeof( T ) , 0 );
		return buffer;	
	}

	inline void rpm_user_buffer( HANDLE process , std::uintptr_t addr , void* out , size_t size ){
		mem_user::user_read_virtualmemory( process , ( LPVOID )addr , out , size , 0 );
	}
	inline void mouse_move_user( float x , float y ){
		INPUT i{ };
		i.type = 0;
		i.mi.dwFlags = MOUSEEVENTF_MOVE;
		i.mi.dx = x;
		i.mi.dy = y;
		SendInput( 1 , &i , sizeof( i ) );	
	}
} // mem_user
