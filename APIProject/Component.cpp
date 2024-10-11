#include "pch.h"
#include "Component.h"

#include "GameObject.h"

bool Component::CompareTag(const Tag tag) const
{
	return mOwner->CompareTag(tag);
}

Transform* Component::GetTransform() const
{
	return mOwner->GetTransform();
}

Tag Component::GetTag() const
{
	return mOwner->GetTag();
}
