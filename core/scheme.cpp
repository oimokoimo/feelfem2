// feelfem2/core/scheme.hpp
#pragma once
#include <string>
#include <vector>
#include <memory>

namespace feelfem2 {

// A tiny "implementation-oriented pseudo code" skeleton.
// The point is: algorithmic steps are explicit, and concrete backends are pluggable.

struct SolveContext {
  std::string name;
  // later: parsed DSL, mesh, dof map, matrices, vectors, bc tables, etc.
};

class SolveScheme {
public:
  virtual ~SolveScheme() = default;

  void NormalLinearProblem(SolveContext& ctx) {
    RoutineInitialize(ctx);
    RoutineHeader(ctx);
    SolveParameters(ctx);
    VariableDefinitions(ctx);
    SolveInitializer(ctx);
    SolveDegreeOfFreedom(ctx);
    SolveBoundaryDataPrepare(ctx);
    SolveMatrixAllocate(ctx);
    SolveCallAssemblyRoutine(ctx);
    SolveUncommonConditions(ctx);
    SolveDirichletConditions(ctx);
    SolveCallSolverRoutine(ctx);
    SolvePostProcess(ctx);
    SolveTerminateSequence(ctx);
    RoutineTerminate(ctx);
  }

protected:
  // These are intentionally fine-grained.
  // Each can be overridden by a backend / program model.
  virtual void RoutineInitialize(SolveContext&) {}
  virtual void RoutineHeader(SolveContext&) {}
  virtual void SolveParameters(SolveContext&) {}
  virtual void VariableDefinitions(SolveContext&) {}
  virtual void SolveInitializer(SolveContext&) {}
  virtual void SolveDegreeOfFreedom(SolveContext&) {}
  virtual void SolveBoundaryDataPrepare(SolveContext&) {}
  virtual void SolveMatrixAllocate(SolveContext&) {}
  virtual void SolveCallAssemblyRoutine(SolveContext&) {}
  virtual void SolveUncommonConditions(SolveContext&) {}
  virtual void SolveDirichletConditions(SolveContext&) {}
  virtual void SolveCallSolverRoutine(SolveContext&) {}
  virtual void SolvePostProcess(SolveContext&) {}
  virtual void SolveTerminateSequence(SolveContext&) {}
  virtual void RoutineTerminate(SolveContext&) {}
};

} // namespace feelfem2

