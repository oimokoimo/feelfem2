// apps/hello_scheme.cpp
#include "feelfem2/core/scheme.hpp"
#include <iostream>

struct DemoScheme final : feelfem2::SolveScheme {
  void RoutineHeader(feelfem2::SolveContext& ctx) override {
    std::cout << "[feelfem2] scheme: " << ctx.name << "\n";
  }
  void SolveCallAssemblyRoutine(feelfem2::SolveContext&) override {
    std::cout << "  - assemble\n";
  }
  void SolveCallSolverRoutine(feelfem2::SolveContext&) override {
    std::cout << "  - solve\n";
  }
  void SolvePostProcess(feelfem2::SolveContext&) override {
    std::cout << "  - postprocess\n";
  }
};

int main() {
  feelfem2::SolveContext ctx;
  ctx.name = "NormalLinearProblem (symbolic skeleton)";
  DemoScheme s;
  s.NormalLinearProblem(ctx);
  return 0;
}

