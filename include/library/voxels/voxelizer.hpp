#pragma once
#include <cstdint>
#include <library/math/vector.hpp>
#include <vector>

namespace library
{
class Bitmap;

class XModel
{
public:
    typedef unsigned int xcolor_t;

    struct alignas(16) xvertex_t
    {
        float x, y, z;
        char nx, ny, nz, p1;
        xcolor_t c;
        xcolor_t c2; // secondary (tone) color
    };

    XModel() = default;
    XModel(XModel&) = default;

    auto& vertices() const noexcept { return vdata; };
	auto& indices() const noexcept { return index; };

    /// @brief Extrude a 2D image into a voxel model
    /// @param fromImage The source image (diffuse colors)
    /// @param offset World-space offset
    /// @param scale World-space scale per pixel
    /// @param fallbackTone Color to assign to c2 for all vertices (default: opaque white)
    void extrude(const Bitmap& fromImage, const glm::vec3& offset, const glm::vec3& scale,
                 xcolor_t fallbackTone = 0xFFFFFFFF);

    /// @brief Extrude a 2D image into a voxel model with per-pixel tone colors from a second bitmap
    /// @param fromImage The source image (diffuse colors)
    /// @param tonemapImage The tonemap image (per-pixel secondary colors, stored in c2)
    /// @param offset World-space offset
    /// @param scale World-space scale per pixel
    void extrude(const Bitmap& fromImage, const Bitmap& tonemapImage,
                 const glm::vec3& offset, const glm::vec3& scale);

    static void initVoxelizer();

private:
    short cull2D(const Bitmap& img, int x, int y);
    void putv2D(const glm::vec3& offset, const glm::vec3& scale, int x, int y, int fid, int vid,
                xcolor_t vcolor, xcolor_t vcolor2);

    std::vector<xvertex_t> vdata;
	std::vector<uint16_t>  index;
};

} // namespace library
