#include <library/opengl/render_state.hpp>
#include <library/opengl/opengl.hpp>

namespace library
{
	static GLenum toGL(BlendFactor f)
	{
		switch (f) {
		case BlendFactor::Zero:                return GL_ZERO;
		case BlendFactor::One:                 return GL_ONE;
		case BlendFactor::SrcAlpha:            return GL_SRC_ALPHA;
		case BlendFactor::OneMinusSrcAlpha:    return GL_ONE_MINUS_SRC_ALPHA;
		case BlendFactor::DstAlpha:            return GL_DST_ALPHA;
		case BlendFactor::OneMinusDstAlpha:    return GL_ONE_MINUS_DST_ALPHA;
		}
		return GL_ZERO;
	}

	void RenderStateTracker::init()
	{
		RenderState s;
		// Force all state on first apply
		if (s.depth_test) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
		glDepthMask(s.depth_write ? GL_TRUE : GL_FALSE);

		if (s.cull_enable) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);
		glCullFace(s.cull_face == CullFace::Front ? GL_FRONT : GL_BACK);

		if (s.blend_enable) glEnable(GL_BLEND); else glDisable(GL_BLEND);
		glBlendFunc(toGL(s.src_factor), toGL(s.dst_factor));

		if (s.multisample) glEnable(GL_MULTISAMPLE); else glDisable(GL_MULTISAMPLE);

		glColorMask(s.color_mask_r, s.color_mask_g, s.color_mask_b, s.color_mask_a);

		if (s.polygon_offset) {
			glEnable(GL_POLYGON_OFFSET_FILL);
			glPolygonOffset(s.polygon_offset_factor, s.polygon_offset_units);
		} else {
			glDisable(GL_POLYGON_OFFSET_FILL);
		}

		if (s.clip_distance0) glEnable(GL_CLIP_DISTANCE0); else glDisable(GL_CLIP_DISTANCE0);

		if (s.viewport.width > 0)
			glViewport(s.viewport.x, s.viewport.y, s.viewport.width, s.viewport.height);

		m_current = s;
		m_initialized = true;
	}

	void RenderStateTracker::apply(const RenderState& s)
	{
		const bool force = !m_initialized;
		if (force)
			m_initialized = true;

		if (force || s.depth_test != m_current.depth_test) {
			if (s.depth_test) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
		}
		if (force || s.depth_write != m_current.depth_write) {
			glDepthMask(s.depth_write ? GL_TRUE : GL_FALSE);
		}

		if (force || s.cull_enable != m_current.cull_enable) {
			if (s.cull_enable) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);
		}
		if (force || s.cull_face != m_current.cull_face) {
			glCullFace(s.cull_face == CullFace::Front ? GL_FRONT : GL_BACK);
		}

		if (force || s.blend_enable != m_current.blend_enable) {
			if (s.blend_enable) glEnable(GL_BLEND); else glDisable(GL_BLEND);
		}
		if (force || s.src_factor != m_current.src_factor || s.dst_factor != m_current.dst_factor) {
			glBlendFunc(toGL(s.src_factor), toGL(s.dst_factor));
		}

		if (force || s.multisample != m_current.multisample) {
			if (s.multisample) glEnable(GL_MULTISAMPLE); else glDisable(GL_MULTISAMPLE);
		}

		if (force || s.color_mask_r != m_current.color_mask_r || s.color_mask_g != m_current.color_mask_g ||
		    s.color_mask_b != m_current.color_mask_b || s.color_mask_a != m_current.color_mask_a) {
			glColorMask(s.color_mask_r, s.color_mask_g, s.color_mask_b, s.color_mask_a);
		}

		if (force || s.polygon_offset != m_current.polygon_offset) {
			if (s.polygon_offset) glEnable(GL_POLYGON_OFFSET_FILL); else glDisable(GL_POLYGON_OFFSET_FILL);
		}
		if (s.polygon_offset &&
		    (force || s.polygon_offset_factor != m_current.polygon_offset_factor ||
		     s.polygon_offset_units != m_current.polygon_offset_units)) {
			glPolygonOffset(s.polygon_offset_factor, s.polygon_offset_units);
		}

		if (force || s.clip_distance0 != m_current.clip_distance0) {
			if (s.clip_distance0) glEnable(GL_CLIP_DISTANCE0); else glDisable(GL_CLIP_DISTANCE0);
		}

		if ((force || s.viewport != m_current.viewport) && s.viewport.width > 0) {
			glViewport(s.viewport.x, s.viewport.y, s.viewport.width, s.viewport.height);
		}

		m_current = s;
	}

	void RenderStateTracker::applyViewport(const Viewport& vp)
	{
		if (vp != m_current.viewport) {
			glViewport(vp.x, vp.y, vp.width, vp.height);
			m_current.viewport = vp;
		}
	}

	void RenderStateTracker::applyViewport(int x, int y, int w, int h)
	{
		applyViewport({x, y, w, h});
	}

	void RenderStateTracker::invalidate()
	{
		m_initialized = false;
	}

} // namespace library
