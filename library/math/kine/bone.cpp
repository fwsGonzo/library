#include "bone.hpp"

#include "../quaternion.hpp"

namespace library
{
	Bone::Bone(Bone& parent, const vec3& position, const vec3& orientation)
		: Bone(position, orientation)
	{
		this->parent = &parent;
		this->parent->children.push_back(this);
	}
	Bone::Bone(const vec3& position, const vec3& orientation)
	{
		this->parent = nullptr;
		this->position = position;
		this->orientation = orientation;
	}
	Bone::~Bone()
	{
		// delete all children
		for (auto c : this->children)
			if (c) delete c;
	}
	
	// clones a bone, without copying parents OR children
	Bone::Bone(const Bone& bone)
	{
		this->parent = nullptr;
		this->orientation = bone.orientation;
		this->position = bone.position;
	}
	
	void Bone::addChild(const Bone& child)
	{
		// clone bone
		Bone* bone = new Bone(child);
		// set bone parent to this
		bone->parent = this;
		// add bone to children
		this->children.push_back(bone);
	}
	
	Bone& Bone::operator [] (int child) const
	{
		return this->children[child][0];
	}
	
	const mat4& Bone::getComposite()
	{
		if (dirty)
		{
			if (this->parent)
			{
				this->composite = mat4(this->parent->getComposite());
			}
			else this->composite.identity();
			
			mat4 orient = translationMatrix(this->position);
			orient *= directionMatrix(this->orientation, vec3(0.0, 1.0, 0.0));
			
			this->composite *= orient;
			
			dirty = false;
		}
		return this->composite;
	}
	
	vec3 Bone::getPosition()
	{
		return (getComposite() * vec4(0.0, 0.0, 0.0, 1.0)).xyz();
	}
	
	void Bone::propagate()
	{
		this->dirty = true;
		for (auto c : children)
			if (c) c->dirty = true;
	}
}
