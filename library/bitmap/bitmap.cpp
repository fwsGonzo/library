#include <library/bitmap/bitmap.hpp>

#include "lodepng.h"
#include <cassert>
#include <fstream>
#include <library/bitmap/colortools.hpp>
#include <library/log.hpp>
#include <memory>

#define GL_RGB 0x1907
#define GL_RGBA 0x1908
#define GL_BGRA 0x80E1

namespace library
{
Bitmap::Bitmap(int w, int h) : buffer(w * h), width(w), height(h), format(GL_BGRA) {}

Bitmap::Bitmap(int w, int h, rgba8_t color)
    : buffer(w * h, color), width(w), height(h), format(GL_BGRA)
{}

Bitmap::Bitmap(int w, int h, const rgba8_t* data, int glformat)
    : width(w), height(h), format(glformat)
{
    if (data)
        buffer.insert(buffer.begin(), data, data + w * h);
    else
        buffer.resize(w * h);
}

Bitmap::Bitmap(const std::string file, Bitmap::bitmap_type btype)
{
    switch (btype)
    {
    case BMP:
        loadBMP(file);
        break;
    case PNG:
        loadPNG(file);
        break;
    default:
        throw std::string("Bitmap::load(): Unsupported format");
    }
}

// assignment operator
Bitmap& Bitmap::operator=(const Bitmap& bmp)
{
    buffer = bmp.buffer;
    this->width = bmp.width;
    this->height = bmp.height;
    this->format = bmp.format;
    // extra info (in case the bitmap was linearized)
    this->tilesX = bmp.tilesX;
    this->tilesY = bmp.tilesY;
    return *this;
}

void Bitmap::loadBMP(const std::string& file)
{
#pragma pack(push, 1)
    // packed: make sure bytes are packed tight, 1-byte memory alignment
    struct bmpheader_t
    {
        char magic[2];
        int filesize;
        short res1;
        short res2;
        int pixeldata;
    };

    struct bmpdata_t
    {
        int headersize;
        int w;
        int h;
        short planes;
        short bits;
        // don't care about the rest
    };
#pragma pack(pop)

    bmpheader_t bhead;
    bmpdata_t bdata;
    std::ifstream File(file.c_str(), std::ios::in | std::ios::binary);

    if (!File)
    { // Log: could not open file
        logger << Log::ERR << "Could not open file: " << file << Log::ENDL;
        throw std::runtime_error("Missing bitmap file: " + file);
    }

    File.read((char*) &bhead, sizeof(bmpheader_t));
    File.read((char*) &bdata, sizeof(bmpdata_t));

    this->width = bdata.w;
    this->height = bdata.h;
    this->format = GL_BGRA;
    this->tilesX = 1;
    this->tilesY = 1;

    int pixels = width * height;

    // allocate 32-bits * w * h pixels
    buffer.resize(pixels);

    // seek to pixeldata relative to beginning of file
    File.seekg(bhead.pixeldata);

    if (bdata.bits == 24)
    {
        // width of image on file in bytes
        int pad = (width * 3) & 3; // 4-byte padding
        if (pad) pad = 4 - pad;
        // width of image in memory in bytes
        const int SCANLINE = width * 3 + pad; // pitch

        auto scanbuffer = std::unique_ptr<uint8_t[]>(new uint8_t[SCANLINE]);

        for (int y = 0; y < height; y++)
        {
            auto* buf = (uint8_t*) buffer.data() + (height - 1 - y) * width * sizeof(rgba8_t);
            auto* tmp = scanbuffer.get();
            // read entire scanline
            File.read((char*) tmp, SCANLINE);

            for (int x = 0; x < width; x++)
            {
                buf[0] = tmp[0];
                buf[1] = tmp[1];
                buf[2] = tmp[2];
                buf[3] = 255;
                buf += 4;
                tmp += 3;
            }
        }
    }
    else if (bdata.bits == 32)
    {
        // 32-bits (8 per channel)
        auto* scanpos = this->buffer.data() + height * width;

        while (scanpos > this->buffer.data())
        {
            scanpos -= width;
            // read entire scanline
            File.read((char*) scanpos, width * sizeof(rgba8_t));
        }
    }
    else
    {
        logger << Log::ERR << "Bitmap::loadBMP(): Invalid bits per pixel: " << bdata.bits
               << Log::ENDL;
        // throw std::string("Bitmap::loadBMP(): Invalid bits value (" + file + ")");
    }
    File.close();
}

void Bitmap::loadPNG(const std::string& file)
{
    unsigned char* out = nullptr;
	unsigned int w, h;
    // load file from disk
	lodepng_decode_file(&out, &w, &h, file.c_str(), LCT_RGBA, 8);
	if (out == nullptr)
	{
		logger << Log::ERR << "Bitmap::loadPNG(): Error loading file: " << file << Log::ENDL;
		throw std::runtime_error("Image decode error for file: " + file);
	}
    this->format = GL_RGBA;
    this->width  = w;
    this->height = h;

	try {
		this->buffer.reserve(w * h);
    	this->buffer.insert(buffer.begin(), (rgba8_t*) out, (rgba8_t*) (out + w * h * 4));
	} catch (...) {
		free(out);
		throw;
	}
	free(out);
}

void Bitmap::blit(Bitmap& dest, const int srcX, const int srcY, const int width, const int height,
                  const int dstX, const int dstY) const
{
    // copy from this at (x, y) with size (w, h) to destination at (dstX, dstY)
    for (int y = 0; y < height; y++)
    {
        auto* src = this->buffer.data() + (y + srcY) * this->width + srcX;
        auto* dst = dest.buffer.data() + (y + dstY) * dest.getWidth() + dstX;
        std::copy(src, src + width, dst);
        // memcpy (dst, src, width * sizeof(rgba8_t));
    }
    dest.format = this->format;
}

void Bitmap::merge(const int srcX, const int srcY, const int width, const int height,
    Bitmap& dest, const int dstX, const int dstY) const
{
    // Conditionally blit, where alpha is non-zero
    for (int y = 0; y < height; y++)
    {
        auto* src = this->buffer.data() + (y + srcY) * this->width + srcX;
        auto* dst = dest.buffer.data() + (y + dstY) * dest.getWidth() + dstX;
		for (int x = 0; x < width; x++)
			if (src[x] >> 24)
				dst[x] = src[x];
    }
}

// splits a bitmap in a 1d continous memory array
// of tiles used by GL_TEXTURE_2D_ARRAY (GL 3.x)
void Bitmap::parse2D(const int tw, const int th)
{
    // nearest tilew/h multiple floor
    const int maxx = int(this->width / tw) * tw;
    const int maxy = int(this->height / th) * th;

    // buffers
    std::vector<rgba8_t> newBuffer(maxx * maxy);
    auto* n = newBuffer.data();

    // for each tile
    for (int y = th - 1; y < maxy; y += th)
        for (int x = 0; x < maxx; x += tw)
        {
            auto* p = this->buffer.data() + y * this->width + x;

            // blit internal tile
            for (int ty = 0; ty < th; ty++)
            {
                for (int tx = 0; tx < tw; tx++) *n++ = *p++;

                p -= this->width + tw;
            } // ty

        } // (x, y)

    // replace with new buffer
    this->buffer = newBuffer;
    // use members for texture_2d_array data
    this->tilesX = maxx / tw;
    this->tilesY = maxy / th;
    this->width = tw;
    this->height = th;
}

// clear a bitmap with a given color
void Bitmap::clear(rgba8_t color)
{
    for (auto& value : buffer) value = color;
}

// replace a color on the bitmap with another
void Bitmap::replace(rgba8_t color, rgba8_t replacecolor)
{
    for (auto& value : buffer)
    {
        if (value == color) value = replacecolor;
    }
}

// rotate 90 degrees
Bitmap Bitmap::rotate90() const
{
    Bitmap bmp(this->height, this->width);
    for (int y = 0; y < this->height; y++)
        for (int x = 0; x < this->width; x++)
        { bmp.setPixel(this->height - 1 - y, x, getPixel(x, y)); }
    return bmp;
}
// flip x around itself
Bitmap Bitmap::flipX() const
{
    Bitmap bmp(this->width, this->height);
    for (int y = 0; y < this->height; y++)
        for (int x = 0; x < this->width; x++)
        { bmp.setPixel(this->width - 1 - x, y, getPixel(x, y)); }
    return bmp;
}
// flip y around itself
Bitmap Bitmap::flipY() const
{
    Bitmap bmp(this->width, this->height);
    for (int y = 0; y < this->height; y++)
        for (int x = 0; x < this->width; x++)
        { bmp.setPixel(x, this->height - 1 - y, getPixel(x, y)); }
    return bmp;
}

bool Bitmap::isValid() const { return this->width > 0 && this->height > 0; }

void Bitmap::convert_to_tilesheet(const int tile_size, const uint32_t color)
{
    this->width = tile_size;
    this->height = tile_size;
    // initialize buffer to a single colored tile
    buffer = std::vector<rgba8_t>(tile_size * tile_size, color);
    this->format = GL_RGBA;
    this->tilesX = 1;
    this->tilesY = 1;
}
void Bitmap::add_colored_tile(uint32_t color)
{
	// Add a single tile with a given color
	this->tilesX++;
	buffer.resize(getTileCount() * getWidth() * getHeight());
	// Resize already filled it with zeroes
	if (color != 0) {
		std::fill(buffer.end() - getWidth() * getHeight(), buffer.end(), color);
	}
}
void Bitmap::add_tile(const Bitmap& other, int tx, int ty, bool fix_transparent_areas)
{
    // we have to assume same tile size
    const int srcX = tx * this->getWidth();
    const int srcY = ty * this->getHeight();
    if (other.getTilesX() > 0) {
        assert(srcX + this->getWidth() * this->getHeight() <= other.getTilesX() * other.getHeight() * other.getWidth());
    } else {
        assert(srcX + this->getWidth() <= other.getWidth());
        assert(srcY + this->getHeight() <= other.getHeight());
    }
    // add single tile
    const size_t end = buffer.size();
    this->tilesX++;
    buffer.resize(getTileCount() * getWidth() * getHeight());

    auto* scan = this->buffer.data() + end;

    for (int y = this->getHeight() - 1; y >= 0; y--)
    {
        auto* src = other.buffer.data() + (y + srcY) * other.width + srcX;
        std::copy(src, src + this->getWidth(), scan);
        scan += this->getWidth();
    }

	if (fix_transparent_areas == false)
		return;

	scan = this->buffer.data() + end;
	auto getpixel = [&] (int x, int y) -> uint32_t&
	{
		//y = this->getHeight() - 1 - y;
		return scan[y * this->getWidth() + x];
	};
	auto search = [&] (int x, int y) -> uint32_t
	{
		// Don't look up
		for (int lx = x-1; lx >= 0; lx--) {
			const auto pixel = getpixel(lx, y);
			if (pixel >> 24) return pixel;
		}
		for (int lx = x+1; lx < this->getWidth(); lx++) {
			const auto pixel = getpixel(lx, y);
			if (pixel >> 24) return pixel;
		}
		// Look down
		for (int ly = y-1; ly >= 0; ly--) {
			const auto pixel = getpixel(x, ly);
			if (pixel >> 24) return pixel;
		}
		// Give up
		return getpixel(x, y);
	};

	// The goal is to fix mipmapping interpolation problems
	for (int y = 0; y < this->getHeight(); y++)
	for (int x = 0; x < this->getWidth(); x++)
    {
		// We only care about transparent pixels
		if (getpixel(x, y) == 0)
		{
			// Find nearest color and use that instead
			getpixel(x, y) = search(x, y) & 0xFFFFFF;
		}
    }
}
void Bitmap::add_tile(std::function<void(rgba8_t*, size_t)> callback)
{
    // add single tile
    const size_t end = buffer.size();
    this->tilesX++;
    buffer.resize(getTileCount() * getWidth() * getHeight());

    auto* scan = this->buffer.data() + end;
	callback(scan, this->buffer.size() - end);
}

std::tuple<const rgba8_t*, size_t> Bitmap::get_tile(int tileID) const
{
	const size_t offset = tileID * this->getWidth() * this->getHeight();
	const size_t size = this->getWidth() * this->getHeight();
	if (offset + size >= this->buffer.size())
		throw std::runtime_error("Bitmap::get_tile(): Invalid tile ID");

	return std::make_tuple(&this->buffer.at(offset), this->getWidth());
}

void Bitmap::merge_tile(const int tileID,
	const Bitmap& other, unsigned tileSize, int tx, int ty, rgba8_t tone, bool keepMergedAlpha)
{
    const int srcX = tx * tileSize;
    const int srcY = ty * tileSize;
    assert(srcX + tileSize <= other.getWidth());
    assert(srcY + tileSize <= other.getHeight());
    // Merge with existing tileID
    const size_t offset = tileID * this->getWidth() * this->getHeight();
	const Color toneColor(tone);

    auto* scan = this->buffer.data() + offset;

    for (int y = this->getHeight()-1; y >= 0; y--)
    {
        auto* src = other.buffer.data() + (srcY + (y % tileSize)) * other.width + srcX;

		for (int x = 0; x < this->getWidth(); x++) {
			Color original(scan[x]);
			Color merged(src[x % tileSize]);

			if (merged.a > 0)
			{
				if (tone != 0) {
					merged = Color::multiply(toneColor, merged);
					const float blend = merged.a / 255.0f;
					merged.a = original.a;

					scan[x] = Color::mixColor(original, merged, blend).whole;
				} else {
					const float blend = merged.a / 255.0f;
					scan[x] = Color::mixColor(original, merged, blend).whole;
				}
				if (keepMergedAlpha)
					scan[x] |= src[x % tileSize] & 0xFF000000;
			}
		}

        scan += this->getWidth();
    }
}
void Bitmap::merge_tilemask(const int tileID, const Bitmap& other, unsigned tileSize, int tx, int ty, rgba8_t mask_color)
{
    const int srcX = tx * tileSize;
    const int srcY = ty * tileSize;
    assert(srcX + tileSize <= other.getWidth());
    assert(srcY + tileSize <= other.getHeight());
    // Merge with existing tileID
    const size_t offset = tileID * this->getWidth() * this->getHeight();

    auto* scan = this->buffer.data() + offset;

    for (int y = this->getHeight()-1; y >= 0; y--)
    {
        auto* src = other.buffer.data() + (srcY + (y % tileSize)) * other.width + srcX;

		for (int x = 0; x < this->getWidth(); x++)
			if (src[x % tileSize] >> 24)
				scan[x] = mask_color;

        scan += this->getWidth();
    }
}

void Bitmap::rotate_tile(const int tileID, int times)
{
	const size_t offset = tileID * this->getWidth() * this->getHeight();
	auto* scan = this->buffer.data() + offset;

	std::vector<rgba8_t> temp(this->getWidth() * this->getHeight());
	auto* temp_scan = temp.data();

	for (int i = 0; i < times; i++)
	{
		// Rotate 90 degrees clockwise
		for (int x = 0; x < this->getWidth(); x++)
		for (int y = 0; y < this->getHeight(); y++)
		{
			temp_scan[y * this->getWidth() + x] = scan[x * this->getWidth() + y];
		}

		std::copy(temp_scan, temp_scan + temp.size(), scan);
	}
} // rotate_tile

void Bitmap::replace_tile_color(int tileID, rgba8_t color, rgba8_t replaceColor, Bitmap* alsoReplace)
{
	const size_t offset = tileID * this->getWidth() * this->getHeight();
	auto* scan = this->buffer.data() + offset;

	for (int p = 0; p < this->getWidth() * this->getHeight(); p++)
	{
		if (scan[p] == color) {
			scan[p] = replaceColor;

			if (alsoReplace) {
				// Replace in the other bitmap as well, at the same position
				alsoReplace->buffer[p] = replaceColor;
			}
		}
	}
} // replace_tile_color

void Bitmap::add_tile_alpha(int tileID, const Bitmap& src, int src_tileID)
{
	const size_t offset = tileID * this->getWidth() * this->getHeight();
	auto* scan = this->buffer.data() + offset;
	const size_t src_offset = src_tileID * src.getWidth() * src.getHeight();
	auto* src_scan = src.buffer.data() + src_offset;

	for (int p = 0; p < this->getWidth() * this->getHeight(); p++)
	{
		scan[p] |= src_scan[p] & 0xFF000000;
	}
} // add_tile_alpha

} // library
