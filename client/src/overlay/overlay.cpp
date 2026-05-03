#include "include.hpp"

#include "overlay.hpp"

#include <imgui/imgui.h>

#include <imgui/imgui_impl_win32.h>

#include <imgui/imgui_impl_dx11.h>

#include <dwmapi.h>

#include <core/config/config.hpp>

#include <roblox/sdk/cache/color_cache.hpp>

#include <roblox/sdk/cache/player_cache.hpp>

#include <core/features/esp/esp.hpp>

#include <core/features/aim_bot/aim.hpp>

#pragma comment(lib,"d3d11.lib")

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI Window_Procedure(HWND hWindoww, UINT message, WPARAM wParam, LPARAM lParam)
{
	overlay::overlay_t* overlay = reinterpret_cast<overlay::overlay_t*>(GetWindowLongPtr(hWindoww, GWLP_USERDATA));

	if (ImGui_ImplWin32_WndProcHandler(hWindoww, message, wParam, lParam))
		return true;

	switch (message)
	{
	case WM_NCHITTEST:
		if (overlay && overlay::menu->show_menu)
			return HTCLIENT;
		break;
	case WM_SYSCOMMAND:
		if ((wParam & 0xFFF0) == SC_KEYMENU)
			return 0;
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	}

	return ::DefWindowProcW(hWindoww, message, wParam, lParam);
}

overlay::overlay_t::overlay_t( ){

	wc = { sizeof( WNDCLASSEXW ) };
	wc.lpfnWndProc = Window_Procedure;
	wc.lpszClassName = L"window";
	wc.hInstance = GetModuleHandle( nullptr );
	RegisterClassExW( &wc );

	int x_screen = GetSystemMetrics( 0 );
	int y_screen = GetSystemMetrics( 1 );

	window = CreateWindowExW(
		WS_EX_TOOLWINDOW | WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE,
		L"window" , L"window",
		WS_POPUP,
		0, 0 ,
		x_screen , y_screen,
		nullptr , nullptr,
		wc.hInstance,
		nullptr
	);
	SetWindowDisplayAffinity( window , WDA_EXCLUDEFROMCAPTURE);
	SetLayeredWindowAttributes( window , RGB( 0 , 0 , 0 ) , 255 , LWA_ALPHA  );
	
	MARGINS marg{ -1 };
	DwmExtendFrameIntoClientArea( window , &marg );

	SetWindowLongPtr( window, GWLP_USERDATA, reinterpret_cast< LONG_PTR >( this ) );
	RegisterHotKey(NULL, 1, MOD_NOREPEAT, VK_DELETE); 

	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = x_screen;
	sd.BufferDesc.Height = y_screen;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = window;
	sd.SampleDesc.Count = 1;
	sd.Windowed = TRUE;
	sd.BufferCount = 2; // or 1
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	D3D_FEATURE_LEVEL feature_level{ };
	const D3D_FEATURE_LEVEL feature_level_array[1] = { D3D_FEATURE_LEVEL_11_0 };
	HRESULT hr = D3D11CreateDeviceAndSwapChain
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr, D3D11_CREATE_DEVICE_BGRA_SUPPORT,
		feature_level_array, 1,
		D3D11_SDK_VERSION,
		&sd, &d3_swap, &d3_device, &feature_level, &d3_context
	);


	ID3D11Texture2D* back_buffer{ };

	
	d3_swap->GetBuffer( 0, IID_PPV_ARGS( &back_buffer ) );
	d3_device->CreateRenderTargetView( back_buffer, nullptr, &d3_render );
	back_buffer->Release();


	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = nullptr;
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\segoeui.ttf", 15.0f, nullptr, io.Fonts->GetGlyphRangesCyrillic());
	ImGui::StyleColorsDark( );
 

	ImGui_ImplWin32_Init( window );
	ImGui_ImplDX11_Init( d3_device , d3_context );

	ShowWindow( window , SW_SHOW );
}

overlay::overlay_t::~overlay_t( ){
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	d3_render->Release();
	d3_swap->Release();
	d3_context->Release();
	d3_device->Release();

	DestroyWindow( window );
	UnregisterClassW(wc.lpszClassName, wc.hInstance);
}

void overlay::overlay_t::toggle_menu( ){
	show_menu = !show_menu;

	LONG style = GetWindowLongW( window , GWL_EXSTYLE );

	if( show_menu ){
		SetWindowLongW( window, GWL_EXSTYLE, style & ~WS_EX_TRANSPARENT );
		SetForegroundWindow( window );	
	}
	else{
		SetWindowLongW( window, GWL_EXSTYLE, style | WS_EX_TRANSPARENT );	
	}
}

void overlay::overlay_t::start_render( ){
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	float colorq[4] = { 0,0,0,0 };
	d3_context->ClearRenderTargetView(d3_render, colorq);
}

void overlay::overlay_t::end_render()
{
	ImGui::Render();
	d3_context->OMSetRenderTargets(1, &d3_render, nullptr);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void overlay::overlay_t::render()
{
	auto color_edit = []( const char* label, config::esp::imvec4& color ) {
		if (ImGui::ColorEdit4(label, (float*)&color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha))
			cache::color::dirty_make();
	};

	auto combo = []( const char* label, int& selected, const char** items , int count ) {
		 ImGui::Combo(label, &selected, items, count );
	};

	ImGui::SetNextWindowSize(ImVec2(410, 410), ImGuiCond_Once);
	ImGui::SetNextWindowBgAlpha(0.90f); 
	ImGui::Begin("##Windows", nullptr,
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoResize
	);
	
	// check box
	ImGui::Checkbox("player" , &config::esp::esp.player );
	ImGui::Checkbox("player aim", &config::aim_bot::aim.player );
	ImGui::Checkbox("player box " , &config::esp::esp.player_box );	
	ImGui::SliderFloat("smooth speed" , &config::aim_bot::aim.smoothing, 1.5f , 7.0f );

	ImGui::SliderFloat("box_filled" , &config::esp::esp.player_box_filled , 0.1f , 0.9f );
	ImGui::SliderFloat("max_distance esp" , &config::esp::esp.player_max_distance, 25.0f , 300.0f );
	ImGui::SliderFloat("max_distance aim" , &config::aim_bot::aim.max_distance, 25.0f , 300.0f );
	
	// combo
	static const char* box_selected[ ] = { "2d" , "2d filled " };

	combo( "box_style" , config::esp::esp.player_box_selected , box_selected , IM_ARRAYSIZE( box_selected ) );

	// color
	color_edit( "player_box " , config::esp::esp.c_player_box );

	ImGui::End( );
}

void overlay::overlay_t::render_loop( ){
	MSG msg{ };
	RtlZeroMemory( &msg , sizeof( msg ) );
	
	auto test_screen_size = memory::mem->get_screen_size( );
	if( test_screen_size.is_zero( ) ){
		memory::mem->update_screen_size( );
	}

	auto last_update_player_cache = std::chrono::steady_clock::now( );

	cache::player::update( ); // no wait first delay
	
	const auto& esp = config::esp::esp;
	const auto& aim = config::aim_bot::aim;
	
	sdk::render::render_t sdk_render( sdk::roblox::rbx->get_render_engine( )  ); // mb you need update this shit

	while( 1 ){

		if( PeekMessage( &msg , nullptr , 0 , 0 , PM_REMOVE ) ){
			if( msg.message == WM_HOTKEY )
				if( msg.wParam == 1 ) toggle_menu( );
			
			TranslateMessage( &msg );
			DispatchMessageW( &msg );
		}

		start_render( );

		auto now = std::chrono::steady_clock::now( );

		if( cache::color::dirty ) cache::color::update( );
		
		auto elapse_player_cache = std::chrono::duration_cast< std::chrono::seconds >( now - last_update_player_cache ).count( );
	
		if( elapse_player_cache >= 7 ){
			cache::player::update( );
		}

		// your function

		if( esp.player )
			features::esp::whack->main_loop( sdk_render );

		if( aim.player )
			features::aim::aim->main_loop( sdk_render );


		if( show_menu ) render( );

		end_render( );

		d3_swap->Present( 0 , 0 );

		std::this_thread::sleep_for( std::chrono::milliseconds( 9 ) );
	}
} 