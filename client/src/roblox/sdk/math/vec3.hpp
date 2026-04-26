#pragma once

#include <cmath>


namespace 
	sdk{ 
namespace
	geom{

	template< typename T >
	struct vec3_tpl{
		T x , y , z;		

		vec3_tpl( ) noexcept : x( 0 ) , y( 0 ) , z( 0 ){ }
		vec3_tpl( const vec3_tpl& t ) noexcept : x( t.x ) , y( t.y ) , z( t.z ){ }
		vec3_tpl( T a , T b , T c ) noexcept : x( a ) , y( b ) , z( c ){ }
	
		void set( T a , T b , T c ) noexcept { x = a; y = b; z = c; }

		T get_length( ) const noexcept { 
			return ( T )sqrt( x * x + y * y + z * z ); 
		}

		T get_distance( const vec3_tpl& b ) const noexcept { 
			return ( T )sqrt( 
				( x - b.x ) * ( x - b.x) +
				( y - b.y )	* ( y - b.y ) +
				( z - b.z ) * ( z - b.z )
			);
		}

		vec3_tpl operator +( const vec3_tpl& a ){
			return vec3_tpl( x + a.x , y + a.y , z + a.z );
		}
		vec3_tpl operator -( const vec3_tpl& a ){
			return vec3_tpl( x - a.x , y - a.y , z - a.z );
		}

		bool is_zero( ) const noexcept { return x == 0 && y == 0 && z == 0; }
	};

	typedef geom::vec3_tpl< float >					vec3;
} // geom

} // sdk

