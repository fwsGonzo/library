#include <library/voxels/voxelizer.hpp>

#include <cstring>
#include <library/bitmap/bitmap.hpp>
#include <library/bitmap/colortools.hpp>

using namespace glm;

namespace library
{
float xm_vertex[6][12] = {
    {0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0}, // front
    {0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0}, // back
    {0.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0}, // top
    {0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0}, // bottom
    {1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 1.0}, // right
    {0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0}  // left
};

char xm_normal[6][3] = {
    {0, 0, 127}, {0, 0, -128}, // front back
    {0, 127, 0}, {0, -128, 0}, // top   bottom
    {127, 0, 0}, {-128, 0, 0}  // right left
};

char xm_tangent[6][3] = {
    {127, 0, 0},  {-128, 0, 0}, // front back
    {127, 0, 0},  {-128, 0, 0}, // top   bottom
    {0, 0, -128}, {0, 0, 127}   // right left
};

inline bool culltest(XModel::xcolor_t value)
{
    // returns true if the alpha-channel value is 0
    return ((value >> 24) == 0);
}

short XModel::cull2D(const Bitmap& img, int x, int y)
{
    int w = img.getWidth();
    int h = img.getHeight();

    short facing = 1 + 2; // always add +z and -z

    if (y == h - 1)
    {
        facing |= 4; // add top when at top
    }
    else
    {
        if (culltest(img.data()[x + (y + 1) * w])) facing |= 4;
    }
    if (y == 0)
    {
        facing |= 8; // add bottom when at bottom
    }
    else
    {
        if (culltest(img.data()[x + (y - 1) * w])) facing |= 8;
    }

    if (x == w - 1)
    {
        facing |= 16; // add front when on right side
    }
    else
    {
        if (culltest(img.data()[(x + 1) + y * w])) facing |= 16;
    }
    if (x == 0)
    {
        facing |= 32; // add back when on left side
    }
    else
    {
        if (culltest(img.data()[(x - 1) + y * w])) facing |= 32;
    }

    return facing;
}

void XModel::putv2D(const vec3& offset, const vec3& scale, int x, int y, int fid, int vid,
                    xcolor_t vcolor)
{
	xvertex_t v;

    // position
    v.x = offset.x + (x + xm_vertex[fid][vid * 3 + 0]) * scale.x;
    v.y = offset.y + (y + xm_vertex[fid][vid * 3 + 1]) * scale.y;
    v.z = offset.z + (0 + xm_vertex[fid][vid * 3 + 2]) * scale.z;
    // normal
    v.nx = xm_normal[fid][0];
    v.ny = xm_normal[fid][1];
    v.nz = xm_normal[fid][2];
    // color
    v.c = vcolor;

    this->vdata.push_back(v);
}

void XModel::extrude(const Bitmap& fromImage, const vec3& offset, const vec3& scale)
{
    int w = fromImage.getWidth();
    int h = fromImage.getHeight();

    xvertex_t* lastpz;
    xvertex_t* lastnz;
    short facing;

    for (int y = 0; y < h; y++)
    {
        const xcolor_t* cv = fromImage.data() + (y * w);
        lastpz = nullptr;
        lastnz = nullptr;

        for (int x = 0; x < w; x++)
        {
            // if this pixel has alpha
            if (cv[0] >> 24)
            {
                xcolor_t c = cv[0];
                // cull from bottoms up (different coordinate system)
                facing = cull2D(fromImage, x, y);

                // unrolled loop of each face
                if (facing & 1) // +z
                {
                    if (lastpz != nullptr && lastpz->c == c)
                    {
                        lastpz[0].x -= scale.x;
                        lastpz[3].x -= scale.x;
                    }
                    else
                    {
                        // lastpz = v
                        putv2D(offset, scale, x, y, 0, 0, c);
                        putv2D(offset, scale, x, y, 0, 1, c);
                        putv2D(offset, scale, x, y, 0, 2, c);
                        putv2D(offset, scale, x, y, 0, 3, c);
                    }
                }
                else
                {
                    lastpz = nullptr;
                }
                if (facing & 2) // -z
                {
                    if (lastnz != nullptr && lastnz->c == c)
                    {
                        lastnz[0].x -= scale.x;
                        lastnz[1].x -= scale.x;
                    }
                    else
                    {
                        // lastnz = v
                        putv2D(offset, scale, x, y, 1, 0, c);
                        putv2D(offset, scale, x, y, 1, 1, c);
                        putv2D(offset, scale, x, y, 1, 2, c);
                        putv2D(offset, scale, x, y, 1, 3, c);
                    }
                }
                else
                {
                    lastnz = nullptr;
                }
                if (facing & 4) // +y
                {
                    putv2D(offset, scale, x, y, 2, 0, c);
                    putv2D(offset, scale, x, y, 2, 1, c);
                    putv2D(offset, scale, x, y, 2, 2, c);
                    putv2D(offset, scale, x, y, 2, 3, c);
                }
                if (facing & 8) // -y
                {
                    putv2D(offset, scale, x, y, 3, 0, c);
                    putv2D(offset, scale, x, y, 3, 1, c);
                    putv2D(offset, scale, x, y, 3, 2, c);
                    putv2D(offset, scale, x, y, 3, 3, c);
                }
                if (facing & 16) // +x
                {
                    putv2D(offset, scale, x, y, 4, 0, c);
                    putv2D(offset, scale, x, y, 4, 1, c);
                    putv2D(offset, scale, x, y, 4, 2, c);
                    putv2D(offset, scale, x, y, 4, 3, c);
                }
                if (facing & 32) // -x
                {
                    putv2D(offset, scale, x, y, 5, 0, c);
                    putv2D(offset, scale, x, y, 5, 1, c);
                    putv2D(offset, scale, x, y, 5, 2, c);
                    putv2D(offset, scale, x, y, 5, 3, c);
                }
            }
            else
            {
                lastpz = nullptr;
                lastnz = nullptr;
            }

            cv += 1;
        } // x
    }     // y
}

} // namespace library
