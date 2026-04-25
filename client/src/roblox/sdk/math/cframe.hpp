#pragma once

#include "vec3.hpp"

namespace
	geom{

	template< typename T >
	struct cframe_tpl{
		T data[ 12 ];
		
		vec3_tpl< T > get_right( ) const{
			return { data[ 0 ] , data[ 3 ] , data[ 6 ] };
		}

		vec3_tpl< T > get_up( ) const {
            return { data[ 1 ], data[ 4 ], data[ 7 ] };
        }

        vec3_tpl< T > get_look( ) const {
            return { data[ 2 ], data[ 5 ], data[ 8 ] };
        }

        vec3_tpl< T > get_pos( ) const {
            return { data[ 9 ], data[ 10 ], data[ 11 ] };
        }


	};

	typedef cframe_tpl< float >		cframe;
} // geom


