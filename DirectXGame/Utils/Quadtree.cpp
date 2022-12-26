#include "Quadtree.h"

Quadtree::Quadtree()
{
}

Quadtree::Quadtree(int level, Box region)
{
	this->_level = level;
	this->_region = region;
}

Quadtree::~Quadtree()
{
	if (this->_topLeft)
	{
		delete this->_topLeft;
	}
	if (this->_topRight)
	{
		delete this->_topRight;
	}
	if (this->_bottomLeft)
	{
		delete this->_bottomLeft;
	}
	if (this->_bottomRight)
	{
		delete this->_bottomRight;
	}
}

void Quadtree::Clear()
{
	if (this->_topLeft)
	{
		delete this->_topLeft;
	}
	if (this->_topRight)
	{
		delete this->_topRight;
	}
	if (this->_bottomLeft)
	{
		delete this->_bottomLeft;
	}
	if (this->_bottomRight)
	{
		delete this->_bottomRight;
	}
	this->_objs.clear();
	this->_region = Box();
}

void Quadtree::Insert(GameObject* obj)
{
	if (this->_topLeft != nullptr)
	{
		if (this->_topLeft->IsContain(obj))
		{
			this->_topLeft->Insert(obj);
		}

		if (this->_topRight->IsContain(obj))
		{
			this->_topRight->Insert(obj);
		}

		if (this->_bottomLeft->IsContain(obj))
		{
			this->_bottomLeft->Insert(obj);
		}

		if (this->_bottomLeft->IsContain(obj))
		{
			this->_bottomLeft->Insert(obj);
		}
		return;
	}

	if (this->IsContain(obj))
	{
		this->_objs.push_back(obj);
	}

	if (this->_objs.size() > MAX_OBJECT_IN_REGION && this->_level < MAX_LEVEL)
	{
		Split();

		while (!this->_objs.empty())
		{
			GameObject* temp = this->_objs.back();
			if (this->_topLeft->IsContain(temp))
			{
				this->_topLeft->Insert(temp);
			}

			if (this->_topRight->IsContain(temp))
			{
				this->_topRight->Insert(temp);
			}

			if (this->_bottomLeft->IsContain(temp))
			{
				this->_bottomLeft->Insert(temp);
			}

			if (this->_bottomLeft->IsContain(temp))
			{
				this->_bottomLeft->Insert(temp);
			}
			this->_objs.pop_back();
		}
	}
}

vector<GameObject*> Quadtree::Retrieve(GameObject* obj)
{
	vector<GameObject*> result;
	if (this->_topLeft)
	{
		vector<GameObject*> temp;
		if (this->_topLeft->IsContain(obj))
		{
			temp = this->_topLeft->Retrieve(obj);
			if (!temp.empty())
			{
				result.insert(result.end(), temp.begin(), temp.end());
			}
		}

		if (this->_topRight->IsContain(obj))
		{
			temp = this->_topRight->Retrieve(obj);
			if (!temp.empty())
			{
				result.insert(result.end(), temp.begin(), temp.end());
			}
		}

		if (this->_bottomLeft->IsContain(obj))
		{
			temp = this->_bottomLeft->Retrieve(obj);
			if (!temp.empty())
			{
				result.insert(result.end(), temp.begin(), temp.end());
			}
		}

		if (this->_bottomLeft->IsContain(obj))
		{
			temp = this->_bottomLeft->Retrieve(obj);
			if (!temp.empty())
			{
				result.insert(result.end(), temp.begin(), temp.end());
			}
		}
		return result;
	}

	if (this->IsContain(obj))
	{
		for (GameObject* obj : this->_objs)
		{
			result.push_back(obj);
		}
	}
	return result;
}

vector<GameObject*> Quadtree::GetAllGameObject()
{
	return this->_objs;
}

Quadtree* Quadtree::CreateQuadtree(std::vector<GameObject*> objs)
{
	return nullptr;
}

bool Quadtree::IsContain(GameObject* obj)
{
	Box box = obj->GetBoundingBox();

	return !(box.x + box.width < this->_region.x ||
		box.y + box.height < this->_region.y ||
		box.x > this->_region.x + this->_region.width ||
		box.y > this->_region.y + this->_region.height);
}

void Quadtree::Split()
{
	this->_bottomLeft = new Quadtree(this->_level + 1, 
		Box(this->_region.x, this->_region.y, this->_region.width / 2, this->_region.height / 2));

	this->_bottomRight = new Quadtree(this->_level + 1,
		Box(this->_region.x + this->_region.width / 2, this->_region.y, this->_region.width / 2, this->_region.height / 2));

	this->_topLeft = new Quadtree(this->_level + 1,
		Box(this->_region.x, this->_region.y + this->_region.height / 2, this->_region.width / 2, this->_region.height / 2));

	this->_topRight = new Quadtree(this->_level + 1,
		Box(this->_region.x + this->_region.width / 2, this->_region.y + this->_region.height / 2, this->_region.width / 2, this->_region.height / 2));
}