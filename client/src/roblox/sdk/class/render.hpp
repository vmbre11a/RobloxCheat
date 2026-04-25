#pragma once

#include "instance.hpp"

namespace
	sdk{

	namespace
		render{
	
			class render_t : public instance::instance_t{
			private:
		
			public:

				render_t( const std::uintptr_t _self ) : instance::instance_t( _self ){ }
				render_t( ) = default;
				~render_t( ) = default;


			};

	
	} // render


} // sdk


