#pragma once

namespace 
	sdk{

namespace
	geom{

	template< typename T >
	struct vec4_tpl{
			T x , y , z , w;		

		vec4_tpl( ) noexcept : x( 0 ) , y( 0 ) , z( 0 ) , w( 0 ){ }
		vec4_tpl( const vec4_tpl& t ) noexcept : x( t.x ) , y( t.y ) , z( t.z ) , w( t.w ){ }
		vec4_tpl( T a , T b , T c , T d ) noexcept : x( a ) , y( b ) , z( c ) , w( d){ }
	
		void set( T a , T b , T c , T d ) noexcept { x = a; y = b; z = c; w = d; }

		vec4_tpl operator +( const vec4_tpl& a ){
			return vec4_tpl( x + a.x , y + a.y , z + a.z , w + a.w );
		}
		vec4_tpl operator -( const vec4_tpl& a ){
			return vec4_tpl( x - a.x , y - a.y , z - a.z , w - a.w );
		}
		
		T get_length( ) const noexcept { 
			return ( T )sqrt( x * x + y * y + z * z + w * w ); 
		}

		T get_distance( const vec4_tpl& b ) const noexcept { 
			return ( *this - b ).get_length( );
		}

		bool is_zero( ) const noexcept { return x == 0 && y == 0 && z == 0; w == 0; }
	};

	typedef vec4_tpl< float >		vec4;
} // geom

} // sdk
