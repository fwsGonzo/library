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
    };

    XModel() = default;
    XModel(XModel&) = default;

    auto& vertices() const noexcept { return vdata; };
	auto& indices() const noexcept { return index; };

    void extrude(const Bitmap& fromImage, const glm::vec3& offset, const glm::vec3& scale);

    static void initVoxelizer();

private:
    short cull2D(const Bitmap& img, int x, int y);
    void putv2D(const glm::vec3& offset, const glm::vec3& scale, int x, int y, int fid, int vid,
                xcolor_t vcolor);

    std::vector<xvertex_t> vdata;
	std::vector<uint16_t>  index;
};

} // namespace library
