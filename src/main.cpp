#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb/stb_image_resize.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#include <filesystem>
#include <iostream>
#include <vector>

#include "Generator.hpp"

int main( int argc, char** argv ){
	if( argc < 2 ){
		std::cout << "Usage: " << argv[0] << " folder_to_save_into" << std::endl;
		return 1;
	}

	std::filesystem::path save_path( argv[1] );
	if( !std::filesystem::exists( save_path )){
		std::cout << save_path.string() << " doesn't exist.";
	}

	size_t size = 65536 * 2;
	std::vector<uint8_t> testimage( size * size );

	for( size_t i = 0; i < size_t(65536) * size_t(65536); ++i ){
		testimage[i] = std::abs((long)i * 2 - 255) % 255;
	}

	constexpr size_t layers = 2;
	constexpr size_t compression_per_run = 16;
	
	size_t total_iterations = 0;

	for( size_t i = 0; i < layers; ++i ){
		total_iterations += std::pow( std::pow( compression_per_run, layers - i - 1 ), 2 );
	}

	std::cout << total_iterations << std::endl;

	size_t counter = 0;
	for( size_t res = 0; res < layers; ++res ){
		auto curr_path = save_path / std::to_string( res );
		if( std::filesystem::exists( curr_path ))
			std::filesystem::remove_all( curr_path );
		std::filesystem::create_directory( curr_path );

		const size_t tiles = std::pow( compression_per_run, layers - res - 1 );
		const size_t tile_size = size / tiles;
		const size_t pixels_to_compress = std::pow( compression_per_run, res );

		// std::cout << size << " " << pixels_to_compress << " " << tile_size / pixels_to_compress << "\n\n";

		for( size_t y = 0; y < tiles; ++y ){
			for( size_t x = 0; x < tiles; ++x ){
				auto output = TerrainGen::compress(
						testimage,
						size,
						pixels_to_compress,
						tile_size / pixels_to_compress,
						x,
						y );

				++counter;

				if( !(counter % 1)){
					printf( "\r%6.2f%%", double( counter ) / double( total_iterations ) * 100.0);
					fflush( stdout );
				}

				/*
				for( auto i: output )
					std::cout << (unsigned)i << " ";
				std::cout << std::endl;
				*/

				stbi_write_png(( curr_path / ( std::to_string( x ) + "_" + std::to_string( y ) + ".png" )).c_str(), tile_size / pixels_to_compress, tile_size / pixels_to_compress, 1, output.data(), tile_size / pixels_to_compress );
			}
		}
		printf( "\n" );
	}
}
