#pragma once

#include <windows.h>

#include <d3d11.h>

#include <iostream>

namespace
	overlay{


	class overlay_t{
	private:
		// var
		ID3D11DeviceContext* d3_context{ };
		IDXGISwapChain* d3_swap{ };
		ID3D11RenderTargetView* d3_render{ };

		WNDCLASSEXW wc{ };


		void toggle_menu( );
		void start_render( );
		void render( );	
		void end_render( );
		
	public:
		// var	
		HWND window{ };
		bool show_menu{ };
		ID3D11Device* d3_device{ };
	
		overlay_t( );
		~overlay_t( );
		
		void render_loop( );
		
		
	};

	inline std::unique_ptr< overlay_t > menu = std::make_unique< overlay_t >( );
} // overlay




