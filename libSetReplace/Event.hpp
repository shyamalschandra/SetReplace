#ifndef LIBSETREPLACE_EVENT_HPP_
#define LIBSETREPLACE_EVENT_HPP_

#include <memory>
#include <vector>

#include "IDTypes.hpp"

namespace SetReplace {
/** @brief Event is an instantiated replacement that has taken place in the system.
 */
struct Event {
  /** @brief ID for the rule this match corresponds to.
   */
  const RuleID rule;

  /** @brief Expressions matching the rule inputs.
   */
  const std::vector<ExpressionID> inputExpressions;

  /** @brief Expressions created from the rule outputs.
   */
  const std::vector<ExpressionID> outputExpressions;

  /** @brief Layer of the causal network this event belongs to.
   */
  const Generation generation;
};

class CausalGraph {
 public:
  /** @brief Constructs a CausalGraph with an initial condition represented by initialExpressions.
   */
  explicit CausalGraph(int initialExpressionsCount);

  /** @brief Adds new event, names its output expressions, and returns their IDs.
   */
  std::vector<ExpressionID> addEvent(RuleID ruleID,
                                     const std::vector<ExpressionID>& inputExpressions,
                                     int outputExpressionsCount);

  /** @brief Yields a vector of all events throughout history.
   */
  std::vector<Event> events() const;

  /** @brief Total number of events.
   */
  size_t eventsCount() const;

  /** @brief Yields a vector of IDs for all expressions in the causal graph.
   */
  std::vector<ExpressionID> allExpressionIDs() const;

  /** @brief Total number of expressions.
   */
  size_t expressionsCount() const;

  /** @brief Generation for a given expression.
   * @details This is the same as the generation of its creator event.
   */
  Generation expressionGeneration(ExpressionID id) const;

  /** @brief Largest generation of any event.
   */
  Generation largestGeneration() const;

 private:
  class Implementation;
  std::shared_ptr<Implementation> implementation_;
};
}  // namespace SetReplace

#endif  // LIBSETREPLACE_EVENT_HPP_