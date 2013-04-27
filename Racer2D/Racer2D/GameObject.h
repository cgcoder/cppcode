#pragma once

#include <d2d1.h>
#include <collection.h>

#include "IUpdatable.h"

using namespace D2D1;
using namespace Platform::Collections;
using namespace Microsoft::WRL;

namespace GameEngine
{

ref class AnimationStoryBoard;

ref class GameObject : IUpdatable
{
internal:
	GameObject();

	property D2D1_POINT_2F Position
	{
		D2D1_POINT_2F get()
		{
			return m_position;
		}

		void set(D2D1_POINT_2F position)
		{
			m_position = position;
		}
	}

	property Matrix3x2F TransformationMatrix
	{
		Matrix3x2F get()
		{
			return m_transformationMatrix;
		}

		void set(Matrix3x2F transfomrationMatrix)
		{
			m_transformationMatrix = transfomrationMatrix;
		}
	}

	property float Width
	{
		float get()
		{
			return m_width;
		}
	}

	property float Height
	{
		float get()
		{
			return m_height;
		}
	}

	property float UnscaledWidth
	{
		float get()
		{
			return m_originalWidth;
		}
	}

	property float UnscaledHeight
	{
		float get()
		{
			return m_originalHeight;
		}
	}

	property float Rotation
	{
		float get()
		{
			return m_rotation;
		}

		void set(float angle)
		{
			m_rotation = angle;
			UpdateTransformationMatrix();
		}
	}

	property float Scale
	{
		float  get()
		{
			return m_scale;
		}

		void set(float scale)
		{
			m_scale = scale;
			UpdateTransformationMatrix();
		}
	}

	void MarkForDelete()
	{
		m_markForDelete = true;
	}

	property bool MarkedForDelete
	{
		bool get()
		{
			return m_markForDelete;
		}
	}

	property ID2D1Bitmap* Bitmap
	{
		ID2D1Bitmap* get()
		{
			return m_pBitmap.Get();
		}

		void set(ID2D1Bitmap* pBitmap)
		{
			m_pBitmap = pBitmap;
		}
	}

	property AnimationStoryBoard^ StoryBoard
	{
		AnimationStoryBoard^ get();
	}

public:
	virtual ~GameObject();

	virtual void Update(float timeTotal, float timeDelta);
	virtual void Render(DirectXBase^ renderer);

	property bool IsReady
	{
		bool get()
		{
			return m_ready;
		}

		void set(bool ready)
		{
			m_ready = ready;
		}
	}

protected private:
	void UpdateTransformationMatrix();

	bool m_ready;

private:
	D2D1_POINT_2F m_position;
	Matrix3x2F m_transformationMatrix;

	float m_width;
	float m_height;

	float m_originalWidth;
	float m_originalHeight;

	float m_rotation;
	float m_scale;

	bool m_markForDelete;

	Vector<IUpdatable ^>^ m_updatables;
	ComPtr<ID2D1Bitmap> m_pBitmap;

	AnimationStoryBoard^ m_storyBoard;
};

};