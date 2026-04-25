#pragma once

#include "include.hpp"

#include "driver/driver_mode.hpp" // for wpm/rpm 

#include "user/user_mode.hpp"// for wpm/rpm

namespace
	memory{

	class memory_t{
	private:
		std::uint64_t process_id{ }; // need driver and user 
		HANDLE process_handle{ }; // if you don't use driver	
		
		std::uintptr_t roblox_base{ } ; // need driver and user

		// 0 - user mode , 1 - driver mode
		bool use_driver{ }; // you use: false = use_usermode ( NtReadVirtualMemory )

		std::string version_game{ }; // verify offsets

	public:
		memory_t( ){ }
		~memory_t( ){ 
			if( process_handle )	{
				CloseHandle( process_handle );
			}
		}

		template< typename T >
		T rpm( const std::uintptr_t addr ){
			if( use_driver )	
				return mem_driver::rpm_driver< T >( addr );

			return mem_user::rpm_user< T >( process_handle , addr );
		}

		void rpm_buffer( const std::uintptr_t addr , void* out , size_t size ){
			if( use_driver ){
				mem_driver::rpm_driver_buffer( addr , &out , size );
				return;	
			}
			mem_user::rpm_user_buffer( process_handle , addr , out , size );
		}

		std::string rpm_str( const std::uintptr_t _addr ){
			size_t str_length = rpm< size_t > ( _addr + 0x10 );
			if( !str_length || str_length > 255 )
				return "unk";

			std::uintptr_t addr = ( str_length >= 16 ) ? rpm< size_t >( _addr ) : _addr;
			auto buffer = std::make_unique< char[ ] >( str_length + 1 );
			rpm_buffer( addr , buffer.get( ), str_length + 1 );
			
			return std::string( buffer.get( ) , str_length );
		}

		std::uint64_t get_pid_by_name( const wchar_t* name ){
			if( use_driver ) 	
				return mem_driver::utils::get_process_id_by_name( name );

			return mem_user::utils::get_process_id_by_name( name );
		}

		std::uintptr_t get_module_by_name( const wchar_t* name ){
			if( use_driver )		
				return mem_driver::utils::get_module_by_name( process_id , name );

			return mem_user::utils::get_module_by_name( process_id , name );
		}


		__forceinline auto set_base( std::uintptr_t base ) noexcept {
			roblox_base = base;	
		}
		
		__forceinline auto set_process_id( std::uint64_t pid ) noexcept {
			process_id = pid;	
		}

		__forceinline auto set_process_handle( HANDLE hprocess ) noexcept {
			process_handle = hprocess;	
		}

		__forceinline auto set_memory_mode( bool _use_driver_ ) noexcept {
			use_driver = _use_driver_;	
		}
	
		__forceinline auto set_version_game( const std::string& version ) noexcept {
			version_game = version;	
		}

		__forceinline auto get_base( ) const noexcept {
			return roblox_base;	
		}
	
		__forceinline auto get_process_id( ) const noexcept {
			return process_id;	
		}
	
		__forceinline auto get_process_handle( ) const noexcept {
			return process_handle;
		}
	
		__forceinline auto get_memory_mode( ) const noexcept {
			return use_driver;
		}
		
		__forceinline const std::string& get_version_name( ) const noexcept {
			return version_game;	
		}

	}; // memory_t
	
	
	inline std::unique_ptr<memory_t> mem = std::make_unique<memory_t>( );
} // n memory 
