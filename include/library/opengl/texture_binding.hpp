#pragma once
#include <cstdint>

namespace library
{
class Texture;

enum class TextureSlot : uint8_t
{
	// Units 0-2: Tilesheet diffuse/tone/normalspec (terrain rendering)
	// Also reused for scene composition in post-processing passes
	Tilesheet0      = 0,
	Tilesheet1      = 1,
	Tilesheet2      = 2,

	// Unit 3: Skybox during terrain, sky buffer during water, custom shader textures
	Skybox          = 3,

	// Units 4-5: Additional tilesheets or reflection textures
	TilesheetAlt0   = 4,
	TilesheetAlt1   = 5,

	// Units 6-7: Water effect textures
	WaterNormals    = 6,
	WaterDuDv       = 7,

	// Unit 8: Column position buffer (TBO)
	PositionBuffer  = 8,

	// Unit 9: Shadow map
	ShadowMap       = 9,

	MAX_SLOTS
};

inline constexpr uint32_t slot_unit(TextureSlot slot) noexcept
{
	return static_cast<uint32_t>(slot);
}

class TextureBindingTable
{
public:
	void bind(TextureSlot slot, Texture& texture);
	void unbind(TextureSlot slot);
};

} // namespace library
