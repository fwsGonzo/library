#ifndef BITMAP_HPP
#define BITMAP_HPP

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

namespace library
{
class Bitmap
{
public:
    typedef unsigned int rgba8_t;

    // supported file-formats
    enum bitmap_type
    {
        BMP,
        PNG
    };

    // constructors
    Bitmap() = default;
    Bitmap(const std::string file, bitmap_type btype);
    Bitmap(int w, int h);
    Bitmap(int w, int h, rgba8_t color);
    Bitmap(int w, int h, const rgba8_t* data, int glformat = 0x80E1);

    // assignment operator (creates new copy)
    Bitmap& operator=(const Bitmap& bmp);
    // copy constructor (creates new copy)
    Bitmap(const Bitmap& bmp) { this->operator=(bmp); }

    // getters
    int getWidth() const { return this->width; }
    int getHeight() const { return this->height; }
    int getFormat() const { return this->format; }

    // get pixel at (x, y)
    rgba8_t getPixel(int x, int y) const { return buffer[y * getWidth() + x]; }
    // set pixel at (x, y)
    void setPixel(int x, int y, rgba8_t color) { buffer[y * getWidth() + x] = color; }

    const rgba8_t* data() const { return this->buffer.data(); }
    rgba8_t* data() { return this->buffer.data(); }

    int getTilesX() const noexcept { return this->tilesX; }
    int getTilesY() const noexcept { return this->tilesY; }
    int getTileCount() const noexcept { return getTilesX() * getTilesY(); }

    // isValid: returns false if the bitmap is currently invalid
    bool isValid() const;

    // operations
    void clear(rgba8_t color);
    void replace(rgba8_t color, rgba8_t replacecolor);
	// Copy from this bitmap into dest
    void blit(Bitmap& dest, int srcX, int srcY, int width, int height, int dstX, int dstY) const;
	// Conditionally blit from here into dest, where alpha is non-zero
	void merge(const int srcX, const int srcY, const int width, const int height,
		Bitmap& dest, const int dstX, const int dstY) const;

    // tile operations
    void parse2D(int tileWidth, int tileHeight);
    void convert_to_tilesheet(int tile_size, uint32_t tile_zero_color);
    void add_tile(const Bitmap&, int tx, int ty, bool fix_transparent_areas = true);
    void add_colored_tile(uint32_t color);
	/// @brief Add a new tile from remote memory through callback
	/// @param callback Callback that provides the new tile
	void add_tile(std::function<void(rgba8_t*, size_t)> callback);

	/// @brief Get the pixel data of a tile from the bitmap
	/// @param tileID The tile ID to get the pixel data from
	/// @return Returns a tuple with the pixel data and the size of the tile
	std::tuple<const rgba8_t*, size_t> get_tile(int tileID) const;

	// Conditionally blit tile at srcTileID into dest at destTileID
	void merge_tile(const int tileID, const Bitmap& src, unsigned tileSize, int tx, int ty,
		rgba8_t tone = 0, bool keepMergedAlpha = false);
	void merge_tilemask(const int tileID, const Bitmap& src, unsigned tileSize, int tx, int ty, rgba8_t color);
	// Rotate a tile 90 degrees
	void rotate_tile(const int tileID, int times = 1);

	/// @brief Replace color in a tile with another color
	/// @param tileID The tile ID to replace the color in
	/// @param color The color to replace
	/// @param replaceColor The color to replace with
	/// @param alsoReplace If not null, if a pixel in this bitmap matches, it will also replace the same pixel in the alsoReplace bitmap
	void replace_tile_color(int tileID, rgba8_t color, rgba8_t replaceColor, Bitmap* alsoReplace = nullptr);

	/// @brief Add non-zero alpha from a tile to another tile
	/// @param tileID The tile ID to add alpha to
	/// @param src The source bitmap to add alpha from
	/// @param src_tileID The source tile ID to add alpha from
	void add_tile_alpha(int tileID, const Bitmap& src, int src_tileID);

    Bitmap rotate90() const;
    Bitmap flipX() const;
    Bitmap flipY() const;

private:
    void loadBMP(const std::string& file);
    void loadPNG(const std::string& file);

    std::vector<rgba8_t> buffer;
    int width = 0, height = 0;
    int format;
    int tilesX = 0;
    int tilesY = 0;
};

} // namespace library

#endif
