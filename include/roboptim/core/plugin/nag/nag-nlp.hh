// Copyright (C) 2013 by Thomas Moulard, AIST, CNRS.
//
// This file is part of the roboptim.
//
// roboptim is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// roboptim is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with roboptim.  If not, see <http://www.gnu.org/licenses/>.

#ifndef ROBOPTIM_CORE_PLUGING_NAG_NAG_NLP_HH
# define ROBOPTIM_CORE_PLUGING_NAG_NAG_NLP_HH
# include <vector>

# include <roboptim/core/portability.hh>
# include <roboptim/core/function.hh>
# include <roboptim/core/differentiable-function.hh>
# include <roboptim/core/twice-differentiable-function.hh>

# include "roboptim/core/plugin/nag/nag-common.hh"

namespace roboptim
{
  /// \addtogroup roboptim_solver
  /// @{

  /// \brief Nonlinear solver.
  ///
  /// Minimize an arbitrary smooth function subject to constraints
  /// (which may include simple bounds on the variables, linear
  /// constraints and smooth nonlinear constraints) using a sequential
  /// quadratic programming (SQP) method. As many first derivatives as
  /// possible should be supplied by you; any unspecified derivatives
  /// are approximated by finite differences. It is not intended for
  /// large sparse problems.
  ///
  /// \see http://www.nag.com/numeric/CL/nagdoc_cl23/html/E04/e04wdc.html
  class ROBOPTIM_DLLEXPORT NagSolverNlp
    : public NagSolverCommon<EigenMatrixDense>
  {
  public:
    typedef NagSolverCommon<EigenMatrixDense>
      parent_t;

    explicit NagSolverNlp (const problem_t& pb);
    virtual ~NagSolverNlp ();

    /// \brief Solve the problem.
    void solve ();

    void
    setIterationCallback (callback_t callback)
    {
      callback_ = callback;
    }

    const callback_t& callback () const
    {
      return callback_;
    }

    solverState_t& solverState ()
    {
      return solverState_;
    }

  private:
    Integer n_;
    Integer nclin_;
    Integer ncnln_;
    Integer tda_;
    Integer tdcj_;
    Integer tdh_;
    Function::result_t objf_;

    Function::matrix_t a_;
    Function::vector_t bl_;
    Function::vector_t bu_;

    Function::vector_t ccon_;
    DifferentiableFunction::jacobian_t cjac_;
    Function::vector_t clamda_;

    DifferentiableFunction::gradient_t grad_;
    TwiceDifferentiableFunction::hessian_t h_;
    Function::argument_t x_;

    callback_t callback_;

    solverState_t solverState_;
  };

  /// @}
} // end of namespace roboptim

#endif //! ROBOPTIM_CORE_PLUGING_NAG_NAG_NLP_HH
