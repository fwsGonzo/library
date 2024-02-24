#include <library/voxels/voxelizer.hpp>

#include <cstring>
#include <library/bitmap/bitmap.hpp>
#include <library/bitmap/colortools.hpp>

using namespace glm;

namespace library
{
static const float xm_vertex[6][12] = {
    {0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0}, // front
    {0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0}, // back
    {0.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0}, // top
    {0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0}, // bottom
    {1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 1.0}, // right
    {0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0}  // left
};

static const char xm_normal[6][3] = {
    {0, 0, 127}, {0, 0, -128}, // front back
    {0, 127, 0}, {0, -128, 0}, // top   bottom
    {127, 0, 0}, {-128, 0, 0}  // right left
};

static const char xm_tangent[6][3] = {
    {127, 0, 0},  {-128, 0, 0}, // front back
    {127, 0, 0},  {-128, 0, 0}, // top   bottom
    {0, 0, -128}, {0, 0, 127}   // right left
};

static inline bool culltest(XModel::xcolor_t value)
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

	for (size_t i = 0; i < vdata.size(); i++) {
		if (memcmp(&v, &vdata[i], sizeof(xvertex_t)) == 0) {
			this->index.push_back(i);
			return;
		}
	}

	this->index.push_back(vdata.size());
    this->vdata.push_back(v);
}

void XModel::extrude(const Bitmap& fromImage, const vec3& offset, const vec3& scale)
{
    int w = fromImage.getWidth();
    int h = fromImage.getHeight();
    short facing;

    for (int y = 0; y < h; y++)
    {
        const xcolor_t* cv = fromImage.data() + (y * w);

        for (int x = 0; x < w; x++)
        {
            // if this pixel has alpha
            if (cv[0] >> 24)
            {
                xcolor_t c = cv[0];
                // cull from bottoms up (different coordinate system)
                facing = cull2D(fromImage, x, y);

				for (int i = 0; i < 6; i++) {
					if (facing & (1 << i)) {
						// 6 vertices in two triangles
						putv2D(offset, scale, x, y, i, 0, c);
						putv2D(offset, scale, x, y, i, 1, c);
						putv2D(offset, scale, x, y, i, 2, c);

						putv2D(offset, scale, x, y, i, 2, c);
						putv2D(offset, scale, x, y, i, 3, c);
						putv2D(offset, scale, x, y, i, 0, c);
					}
				}
            }

            cv += 1;
        } // x
    }     // y
}

} // namespace library
