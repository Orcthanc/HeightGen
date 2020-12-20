#include "Generator.hpp"

#include <assert.h>
#include <iostream>

std::vector<uint8_t> TerrainGen::compress(
		const std::vector<uint8_t>& input,
		size_t inp_size,
		size_t pixels_to_compress,
		size_t out_size,
		size_t patch_offset_x,
		size_t patch_offset_y )
{
	assert( pixels_to_compress && "Compression must be larger than 0" );

	std::vector<uint8_t> res( out_size * out_size );

	// std::cout << inp_size << " " << pixels_to_compress << " " << out_size << " " << patch_offset_x << " " << patch_offset_y << std::endl;

	const size_t patch_size = out_size * pixels_to_compress;

	for( size_t y = 0; y < out_size; ++y ){
		for( size_t x = 0; x < out_size; ++x ){
			size_t counter = 0;
			const size_t xindex = patch_offset_x * patch_size + pixels_to_compress * x;
			const size_t yindex = patch_offset_y * patch_size + pixels_to_compress * y;
			for( size_t yi = 0; yi < pixels_to_compress; ++yi ){
				for( size_t xi = 0; xi < pixels_to_compress; ++xi ){
					counter += input[xindex + xi + (yindex + yi) * inp_size];
				}
			}
			res[x + y * out_size] = counter / ( pixels_to_compress * pixels_to_compress );
			// std::cout << "(" << xindex << " " << yindex << " " << counter / (pixels_to_compress * pixels_to_compress) << std::endl;
		}
	}

	// std::cout << std::endl;

	return res;
}
