#pragma once
#include <utility>

// Forward declarations
class Match;

class PointCalculator {
public:
  ///
  /// Enum type for the different score calculation models
  ///
  enum TableType { t210=1, t310, t3210};

  ///
  /// Constructor, default
  ///
  PointCalculator();

  ///
  /// Destructor
  ///
  virtual ~PointCalculator();

  ///
  /// Returns a calculator based on the TableType provided
  ///
  static PointCalculator* GetCalculator(TableType type);

  ///
  /// Declases abstract function for calculation points
  ///
  virtual std::pair<int, int> Calculate(const Match& match) const =0;

private:
  // abstract functions that returns the points awarded for each condition,
  // these must be implemented by all inheriting classes.
  virtual int Win() const =0;
  virtual int Draw() const =0;
  virtual int Loss() const =0;
  virtual int Extended() const =0;
};