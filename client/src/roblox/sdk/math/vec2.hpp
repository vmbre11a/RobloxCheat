#pragma once

#include <cmath>


namespace 
	sdk{ 
namespace
	geom{


	template< typename T >
	struct vec2_tpl{
		T x , y;		

		vec2_tpl( ) noexcept : x( 0 ) , y( 0 ){ }
		vec2_tpl( const vec2_tpl& t ) noexcept : x( t.x ) , y( t.y ){ }
		vec2_tpl( T a , T b ) noexcept : x( a ) , y( b ){ }
	
		void set( T a , T b ) noexcept { x = a; y = b; }

		T get_length( ) const noexcept { 
			return ( T )sqrt( x * x + y * y ); 
		}
		
		
		T get_distance( const vec2_tpl& b ) const noexcept { 
			return ( T )sqrt( 
				( x - b.x ) * ( x - b.x) +
				( y - b.y )	* ( y - b.y )
			);
		}

		vec2_tpl operator +( const vec2_tpl& a ){
			return vec2_tpl( x + a.x , y + a.y );
		}
		vec2_tpl operator -( const vec2_tpl& a ){
			return vec2_tpl( x - a.x , y - a.y );
		}

		bool is_zero( ) const noexcept { return x == 0 && y == 0; }
	};

	typedef geom::vec2_tpl< float >					vec2;

} // geom 

} // sdk 