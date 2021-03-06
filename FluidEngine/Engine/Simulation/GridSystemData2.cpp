#include "GridSystemData2.h"

#include <vector>
#include <algorithm>

namespace Engine
{
	GridSystemData2::GridSystemData2()
		: GridSystemData2({ 0, 0 }, { 1, 1 }, { 0, 0 }) {}

	GridSystemData2::GridSystemData2(
		const Size2& resolution,
		const Vector2D& gridSpacing,
		const Vector2D& origin) 
	{
		_velocityIdx = 0;
		_velocity = std::make_shared<FaceCenteredGrid2>();
		_advectableVectorDataList.push_back(_velocity);
		resize(resolution, gridSpacing, origin);
	}

	GridSystemData2::GridSystemData2(const GridSystemData2& other) 
	{
		resize(other._resolution, other._gridSpacing, other._origin);

		for (auto& data : other._scalarDataList) 
			_scalarDataList.push_back(data->clone());
		for (auto& data : other._vectorDataList) 
			_vectorDataList.push_back(data->clone());

		for (auto& data : other._advectableScalarDataList) 
			_advectableScalarDataList.push_back(data->clone());
		for (auto& data : other._advectableVectorDataList) 
			_advectableVectorDataList.push_back(data->clone());

		assert(_advectableVectorDataList.size() > 0);

		_velocityIdx = 0;
		_velocity = std::dynamic_pointer_cast<FaceCenteredGrid2>(_advectableVectorDataList[0]);

		assert(_velocity != nullptr);
	}

	GridSystemData2::~GridSystemData2() {}

	void GridSystemData2::resize(
		const Size2& resolution,
		const Vector2D& gridSpacing,
		const Vector2D& origin) 
	{
		_origin = origin;
		_resolution = resolution;
		_gridSpacing = gridSpacing;

		for (auto& data : _scalarDataList) 
			data->resize(resolution, gridSpacing, origin);
		for (auto& data : _vectorDataList) 
			data->resize(resolution, gridSpacing, origin);
		for (auto& data : _advectableScalarDataList) 
			data->resize(resolution, gridSpacing, origin);
		for (auto& data : _advectableVectorDataList) 
			data->resize(resolution, gridSpacing, origin);
	}

	Size2 GridSystemData2::resolution() const { return _resolution; }

	Vector2D GridSystemData2::gridSpacing() const { return _gridSpacing; }

	Vector2D GridSystemData2::origin() const { return _origin; }

	BoundingBox2D GridSystemData2::boundingBox() const { return _velocity->boundingBox(); }

	size_t GridSystemData2::addScalarData(const ScalarGridBuilder2Ptr& builder, double initialVal) 
	{
		size_t attrIdx = _scalarDataList.size();
		_scalarDataList.push_back(builder->build(resolution(), gridSpacing(), origin(), initialVal));
		return attrIdx;
	}

	size_t GridSystemData2::addVectorData(const VectorGridBuilder2Ptr& builder, const Vector2D& initialVal) 
	{
		size_t attrIdx = _vectorDataList.size();
		_vectorDataList.push_back(builder->build(resolution(), gridSpacing(), origin(), initialVal));
		return attrIdx;
	}

	size_t GridSystemData2::addAdvectableScalarData(const ScalarGridBuilder2Ptr& builder, double initialVal)
	{
		size_t attrIdx = _advectableScalarDataList.size();
		_advectableScalarDataList.push_back(builder->build(resolution(), gridSpacing(), origin(), initialVal));
		return attrIdx;
	}

	size_t GridSystemData2::addAdvectableVectorData(const VectorGridBuilder2Ptr& builder, const Vector2D& initialVal) 
	{
		size_t attrIdx = _advectableVectorDataList.size();
		_advectableVectorDataList.push_back(builder->build(resolution(), gridSpacing(), origin(), initialVal));
		return attrIdx;
	}

	const FaceCenteredGrid2Ptr& GridSystemData2::velocity() const { return _velocity; }

	size_t GridSystemData2::velocityIndex() const { return _velocityIdx; }

	const ScalarGrid2Ptr& GridSystemData2::scalarDataAt(size_t idx) const { return _scalarDataList[idx]; }

	const VectorGrid2Ptr& GridSystemData2::vectorDataAt(size_t idx) const { return _vectorDataList[idx]; }

	const ScalarGrid2Ptr&
		GridSystemData2::advectableScalarDataAt(size_t idx) const { return _advectableScalarDataList[idx]; }

	const VectorGrid2Ptr&
		GridSystemData2::advectableVectorDataAt(size_t idx) const { return _advectableVectorDataList[idx]; }

	size_t GridSystemData2::numberOfScalarData() const { return _scalarDataList.size(); }

	size_t GridSystemData2::numberOfVectorData() const { return _vectorDataList.size(); }

	size_t GridSystemData2::numberOfAdvectableScalarData() const { return _advectableScalarDataList.size(); }

	size_t GridSystemData2::numberOfAdvectableVectorData() const { return _advectableVectorDataList.size(); }
}