#include "stb/stb_image_resize.h"
#include "stb/stb_image_write.h"
#include <filesystem>
#include <iostream>

int main( int argc, char** argv ){
	if( argc < 2 ){
		std::cout << "Usage: " << argv[0] << " folder_to_save_into" << std::endl;
		return 1;
	}

	std::filesystem::path save_path( argv[1] );
	if( !std::filesystem::exists( save_path )){
		std::cout << save_path.string() << " doesn't exist.";
	}

	char testimage[256];

	for( size_t i = 0; i < 256; ++i ){
		testimage[i] = i / 256.0;
	}

	constexpr size_t layers = 3;

	for( size_t res = 0; res < layers; ++res ){
		auto curr_path = save_path / std::to_string( res );
		if( std::filesystem::exists( curr_path ))
			std::filesystem::remove( curr_path );
		std::filesystem::create_directory( curr_path );
	}
}
