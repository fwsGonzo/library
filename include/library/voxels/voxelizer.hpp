#ifndef VOXELIZER_HPP
#define VOXELIZER_HPP

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

    const xvertex_t* data() const noexcept { return vdata.data(); }
    size_t vertices() const noexcept { return vdata.size(); };

    void extrude(const Bitmap& fromImage, const glm::vec3& offset, const glm::vec3& scale);

    static void initVoxelizer();

private:
    short cull2D(const Bitmap& img, int x, int y);
    void putv2D(const glm::vec3& offset, const glm::vec3& scale, int x, int y, int fid, int vid,
                xcolor_t vcolor);

    std::vector<xvertex_t> vdata;
};
} // namespace library
#endif
