#pragma once

#include "IterativeLevelSetSolver2.h"

namespace Engine
{
	//! Two-dimensional third-order ENO-based iterative level set solver.
	class EnoLevelSetSolver2 final : public IterativeLevelSetSolver2
	{
	public:
		//! Default constructor.
		EnoLevelSetSolver2();

	protected:
		//! Computes the derivatives for given grid point.
		void getDerivatives(ConstArrayAccessor2<double> grid,
			const Vector2D& gridSpacing, size_t i, size_t j,
			std::array<double, 2>* dx,
			std::array<double, 2>* dy) const override;

	};

	typedef std::shared_ptr<EnoLevelSetSolver2> EnoLevelSetSolver2Ptr;

}
