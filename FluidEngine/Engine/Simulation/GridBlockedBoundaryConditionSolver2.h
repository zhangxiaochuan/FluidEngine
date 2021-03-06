#pragma once

#include <memory>

#include "GridFractionalBoundaryConditionSolver2.h"

namespace Engine
{
	//!
	//! \brief Blocked 2-D boundary condition solver for grids.
	//!
	//! This class constrains the velocity field by projecting the flow to the
	//! blocked representation of the collider. A collider is rasterized into voxels
	//! and each face of the collider voxels projects the velocity field onto its
	//! face. This implementation should pair up with GridSinglePhasePressureSolver3
	//! since the pressure solver assumes blocked boundary representation as well.
	//!
	class GridBlockedBoundaryConditionSolver2 final : public GridFractionalBoundaryConditionSolver2
	{
	public:
		//! Default constructor.
		GridBlockedBoundaryConditionSolver2();

		//!
		//! Constrains the velocity field to conform the collider boundary.
		//!
		//! \param velocity Input and output velocity grid.
		//! \param extrapolationDepth Number of inner-collider grid cells that
		//!     velocity will get extrapolated.
		//!
		void constrainVelocity(FaceCenteredGrid2* velocity, unsigned int extrapolationDepth = 5) override;

		//! Returns the marker which is 1 if occupied by the collider.
		const Array2<char>& marker() const;

	protected:
		//! Invoked when a new collider is set.
		void onColliderUpdated(
			const Size2& gridSize,
			const Vector2D& gridSpacing,
			const Vector2D& gridOrigin) override;

	private:
		Array2<char> _marker;

	};

	//! Shared pointer type for the GridBlockedBoundaryConditionSolver2.
	typedef std::shared_ptr<GridBlockedBoundaryConditionSolver2> GridBlockedBoundaryConditionSolver2Ptr;

}

