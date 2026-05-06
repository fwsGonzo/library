#include <library/opengl/texture_binding.hpp>
#include <library/opengl/texture.hpp>

namespace library
{

void TextureBindingTable::bind(TextureSlot slot, Texture& texture)
{
	texture.bind(slot_unit(slot));
}

void TextureBindingTable::unbind(TextureSlot slot)
{
	Texture::unbind(slot_unit(slot));
}

} // namespace library
