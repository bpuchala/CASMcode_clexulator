#ifndef CASM_clexulator_LocalClusterExpansion
#define CASM_clexulator_LocalClusterExpansion

#include <set>
#include <vector>

#include "casm/clexulator/Clexulator.hh"
#include "casm/clexulator/LocalCorrelations.hh"
#include "casm/clexulator/SparseCoefficients.hh"
#include "casm/crystallography/UnitCellCoord.hh"

namespace CASM {
namespace clexulator {

/// \brief A local cluster expansion calculator
class LocalClusterExpansion {
 public:
  LocalClusterExpansion(
      std::shared_ptr<SuperNeighborList const> const &_supercell_neighbor_list,
      std::shared_ptr<std::vector<Clexulator> const> const &_clexulator,
      SparseCoefficients const &_coefficients,
      ConfigDoFValues const *_dof_values = nullptr);

  /// \brief Reset pointer to configuration currently being calculated
  void set(ConfigDoFValues const *dof_values);

  /// \brief Pointer to configuration currently being calculated
  ConfigDoFValues const *get() const;

  /// \brief Get internal LocalCorrelations calculator
  LocalCorrelations &correlations();

  /// \brief Get internal LocalCorrelations calculator
  LocalCorrelations const &correlations() const;

  /// \brief Get internal SparseCoefficients
  SparseCoefficients &coefficients();

  /// \brief Get internal SparseCoefficients
  SparseCoefficients const &coefficients() const;

  /// \brief Value at particular unit cell and phenomenal cluster
  double value(Index unitcell_index, Index equivalent_index);

  /// \brief Return the coordinates of sites (relative to the origin unit cell)
  ///     where a change in DoF values requires this calculators values to be
  ///     re-calculated.
  std::set<xtal::UnitCellCoord> required_update_neighborhood(
      Index equivalent_index) const;

 private:
  /// \brief Used to evaluate local correlations
  LocalCorrelations m_correlations;

  /// \brief Non-zero expansion coefficients
  SparseCoefficients m_coefficients;
};

}  // namespace clexulator
}  // namespace CASM

#endif
