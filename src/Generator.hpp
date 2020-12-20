#include <vector>
#include <inttypes.h>

namespace TerrainGen {
	extern std::vector<uint8_t> compress(
			const std::vector<uint8_t>& input,
			size_t inp_size,
			size_t pixels_to_compress,
			size_t out_size,
			size_t patch_offset_x,
			size_t patch_offset_y );
};
