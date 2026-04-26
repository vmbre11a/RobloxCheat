#pragma once

namespace
	sdk{ 
	namespace 
		geom{ 
	
		template< typename T > 
		struct mat4_tpl{
			T data[ 16 ];
		};
			
			typedef mat4_tpl< float >			mat4;
	} // geom

} // sdk
