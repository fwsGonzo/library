#include <library/bitmap/colortools.hpp>

using namespace glm;

namespace library
{
Color Color::mixColor(const Color& a, const Color& b, float mixlevel)
{
    return Color((int) ((float) a.r * (1.0 - mixlevel) + (float) b.r * mixlevel),
                 (int) ((float) a.g * (1.0 - mixlevel) + (float) b.g * mixlevel),
                 (int) ((float) a.b * (1.0 - mixlevel) + (float) b.b * mixlevel),
                 (int) ((float) a.a * (1.0 - mixlevel) + (float) b.a * mixlevel));
}

void Color::addRGB(const Color& color, float level)
{
    const int R = this->r + (int) ((float) color.r * level);
    const int G = this->g + (int) ((float) color.g * level);
    const int B = this->b + (int) ((float) color.b * level);
	this->r = (R < 256) ? R : 255;
	this->g = (G < 256) ? G : 255;
	this->b = (B < 256) ? B : 255;
}
void Color::addRGBA(const Color& color, float level)
{
	this->addRGB(color, level);
    const int A = this->a + (int) ((float) color.a * level);
	this->a = (A < 256) ? A : 255;
}

Color Color::getGradientColor(float v, const Color* array, int size)
{
    int vint = (int) v, vnxt;
    float vfrac = v - vint;

    // find color gradient values
    if (vfrac < 0.5)
        vnxt = vint - 1;
    else
        vnxt = vint + 1;

    // clamp
    if (vnxt < 0) vnxt = 0;
    if (vnxt >= size) vnxt = size - 1;

    // get gradient array colors
    const Color& cl1 = array[vint];
    const Color& cl2 = array[vnxt];

    // convert fractional to interpolator
    if (vfrac < 0.5)
        vfrac = (0.5 - vfrac) / 0.5;
    else
        vfrac = (vfrac - 0.5) / 0.5;
    // S-curve the interpolator
    vfrac = quintic(vfrac);

    return mixColor(cl1, cl2, vfrac * 0.5);
}

glm::vec4 colorToVector(rgba8_t color)
{
    return glm::vec4((color & 255) / 255.0f, ((color >> 8) & 255) / 255.0f,
                     ((color >> 16) & 255) / 255.0f, (color >> 24) / 255.0f);
}

rgba8_t vectorToColor(const glm::vec4& vector)
{
    int r = int(vector.x * 255);
    int g = int(vector.y * 255) << 8;
    int b = int(vector.y * 255) << 16;
    int a = int(vector.y * 255) << 24;
    return BGRA8(r, g, b, a);
}

} // namespace library
