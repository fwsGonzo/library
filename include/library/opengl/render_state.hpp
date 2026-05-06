#pragma once
#include <array>
#include <cstdint>

namespace library
{
	enum class CullFace : uint8_t {
		Back  = 0,
		Front = 1,
	};

	enum class BlendFactor : uint8_t {
		Zero,
		One,
		SrcAlpha,
		OneMinusSrcAlpha,
		DstAlpha,
		OneMinusDstAlpha,
	};

	struct Viewport {
		int x = 0, y = 0;
		int width = 0, height = 0;

		bool operator==(const Viewport&) const = default;
	};

	struct RenderState {
		bool depth_test = true;
		bool depth_write = true;

		bool cull_enable = true;
		CullFace cull_face = CullFace::Back;

		bool blend_enable = false;
		BlendFactor src_factor = BlendFactor::SrcAlpha;
		BlendFactor dst_factor = BlendFactor::OneMinusSrcAlpha;

		bool multisample = false;

		bool color_mask_r = true;
		bool color_mask_g = true;
		bool color_mask_b = true;
		bool color_mask_a = true;

		bool polygon_offset = false;
		float polygon_offset_factor = 0.0f;
		float polygon_offset_units = 0.0f;

		bool clip_distance0 = false;

		Viewport viewport = {};
	};

	class RenderStateTracker {
	public:
		void apply(const RenderState& desired);

		void applyViewport(const Viewport& vp);
		void applyViewport(int x, int y, int w, int h);

		void invalidate();
		void init();

		const RenderState& current() const noexcept { return m_current; }

	private:
		RenderState m_current;
		bool m_initialized = false;
	};

} // namespace library
