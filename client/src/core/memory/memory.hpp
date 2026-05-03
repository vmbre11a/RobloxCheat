#pragma once 

#include "include.hpp"

#include "driver/driver_mode.hpp" // for wpm/rpm 

#include "user/user_mode.hpp"// for wpm/rpm

#include "roblox/sdk/math/vec2.hpp"


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

		sdk::geom::i_vec2 screen_size{ }; 

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

		void rpm_buffer( const std::uintptr_t addr , void* out , size_t size );

		std::string rpm_str( const std::uintptr_t _addr );

		std::uint64_t get_pid_by_name( const wchar_t* name );

		std::uintptr_t get_module_by_name( const wchar_t* name );
		
		__forceinline bool is_valid( const std::uintptr_t addr ){
			if( addr >= 0x1000 && addr <= 0x7FFFFFFEFFFF )
				return true;

			return false;
		}
		__forceinline bool is_valid( const void* addr ){
			if( reinterpret_cast< std::uint64_t >( addr ) >= 0x1000 && reinterpret_cast< std::uint64_t >( addr ) <= 0x7FFFFFFEFFFF )
				return true;

			return false;
		}
			
		void update_screen_size( );

		// setters
		void set_base(std::uintptr_t base) noexcept; 
		void set_process_id(std::uint64_t pid) noexcept;
		void set_process_handle(HANDLE hprocess) noexcept;
		void set_memory_mode(bool _use_driver_) noexcept;
		void set_version_game(const std::string& version) noexcept;
		void set_screen_size( const sdk::geom::i_vec2& new_screen ) noexcept;
		void set_mouse_pos( float x , float y );
		void set_mouse_pos( sdk::geom::vec2 new_pos );

		// getters
		std::uintptr_t get_base() const noexcept;
		std::uint64_t get_process_id() const noexcept;
		HANDLE get_process_handle() const noexcept;
		bool get_memory_mode() const noexcept;
		const std::string& get_version_name() const noexcept;
		const sdk::geom::i_vec2& get_screen_size( ) const noexcept;
		const sdk::geom::i_vec2 get_mouse_pos( ) const noexcept;
		
	}; // memory_t
	
	
	inline std::unique_ptr<memory_t> mem = std::make_unique<memory_t>( );
} // n memory 
