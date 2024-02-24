#include <library/voxels/voxelmodel.hpp>
#include <library/voxels/voxelizer.hpp>

#include <library/opengl/opengl.hpp>
#include <library/voxels/voxelizer.hpp>

namespace library
{
VoxelModel::VoxelModel(const VoxelModel& vx)
{
	this->vao = vx.vao;
}
VoxelModel::VoxelModel(const XModel& xm)
{
	// Create VAO directly from XModel data
	vao.begin(sizeof(XModel::xvertex_t), xm.vertices().size(), xm.vertices().data());
	vao.attrib(0, 3, GL_FLOAT, false, 0);
	vao.attrib(1, 4, GL_UNSIGNED_BYTE, true, 12);
	vao.attrib(2, 4, GL_UNSIGNED_BYTE, true, 16);
	vao.indexes(xm.indices().data(), xm.indices().size());
}

void VoxelModel::render() { vao.renderIndexed(GL_TRIANGLES); }
void VoxelModel::render(GLint mode) { vao.renderIndexed(mode); }

} // namespace library
