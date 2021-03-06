#include "Vertex.h"

namespace Engine
{
	size_t VertexHelper::getNumberOfFloats(VertexFormat format) 
	{
		size_t size = 0;

		if (static_cast<int>(format & VertexFormat::Position3)) 
			size += 3;

		if (static_cast<int>(format & VertexFormat::Normal3)) 
			size += 3;

		if (static_cast<int>(format & VertexFormat::TexCoord2)) 
			size += 2;

		if (static_cast<int>(format & VertexFormat::TexCoord3)) 
			size += 3;

		if (static_cast<int>(format & VertexFormat::Color4)) 
			size += 4;

		return size;
	}

	size_t VertexHelper::getSizeInBytes(VertexFormat format) 
	{
		return sizeof(float) * getNumberOfFloats(format);
	}

}