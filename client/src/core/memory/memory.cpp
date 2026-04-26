#include "memory.hpp"


void memory::memory_t::rpm_buffer( const std::uintptr_t addr , void* out , size_t size ){
	if( use_driver ){
		mem_driver::rpm_driver_buffer( addr , &out , size );
		return;	
	}
	mem_user::rpm_user_buffer( process_handle , addr , out , size );
}

std::string memory::memory_t::rpm_str( const std::uintptr_t _addr ){
	size_t str_length = memory::mem->rpm< size_t > ( _addr + 0x10 );
	if( !str_length || str_length > 255 )
		return "unk";

	std::uintptr_t addr = ( str_length >= 16 ) ? rpm< size_t >( _addr ) : _addr;
	auto buffer = std::make_unique< char[ ] >( str_length + 1 );
	rpm_buffer( addr , buffer.get( ), str_length + 1 );
	
	return std::string( buffer.get( ) , str_length );
}

std::uint64_t memory::memory_t::get_pid_by_name( const wchar_t* name ){
	if( use_driver ) 	
		return mem_driver::utils::get_process_id_by_name( name );

	return mem_user::utils::get_process_id_by_name( name );
} 

std::uintptr_t memory::memory_t::get_module_by_name( const wchar_t* name ){
	if( use_driver )		
		return mem_driver::utils::get_module_by_name( process_id , name );

	return mem_user::utils::get_module_by_name( process_id , name );
}


void memory::memory_t::set_base( std::uintptr_t base ) noexcept {
	roblox_base = base;	
}

void memory::memory_t::set_process_id( std::uint64_t pid ) noexcept {
	process_id = pid;	
}

void memory::memory_t::set_process_handle( HANDLE hprocess ) noexcept {
	process_handle = hprocess;	
}

void memory::memory_t::set_memory_mode( bool _use_driver_ ) noexcept {
	use_driver = _use_driver_;	
}

void memory::memory_t::set_version_game( const std::string& version ) noexcept {
	version_game = version;	
}

void memory::memory_t::set_screen_size( const sdk::geom::i_vec2 new_size ) noexcept{
	screen_size = new_size;
}


std::uintptr_t memory::memory_t::get_base( ) const noexcept {
	return roblox_base;	
}

std::uint64_t memory::memory_t::get_process_id( ) const noexcept {
	return process_id;	
}

HANDLE memory::memory_t::get_process_handle( ) const noexcept {
	return process_handle;
}

bool memory::memory_t::get_memory_mode( ) const noexcept {
	return use_driver;
}

const std::string& memory::memory_t::get_version_name( ) const noexcept {
	return version_game;	
}

const sdk::geom::i_vec2 memory::memory_t::get_screen_size( ) const noexcept{
	return screen_size;
}


