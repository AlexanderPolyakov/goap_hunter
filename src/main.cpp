//
#include <algorithm>
#include "goapPlanner.h"

static void debug_hunter_planner()
{
  goap::Planner pl = goap::create_planner();

  // DECLARE STATES
  goap::add_states_to_planner(pl,
      {"enemy_vis",
       "has_comms",
       "has_operator",
       "perm_req",
       "has_perm",
       "num_destr"});

  // ACTIONS
  goap::add_action_to_planner(pl, "patrol", 1,
      {{"enemy_vis", 0}},
      {{"enemy_vis", 1}, {"has_perm", 0}},
      {});

  goap::add_action_to_planner(pl, "req_permission", 1,
      {{"enemy_vis", 1}, {"has_comms", 1}, {"has_operator", 1}},
      {{"has_perm", 1}},
      {});

  goap::add_action_to_planner(pl, "destroy_sam", 1,
      {{"enemy_vis", 1}, {"has_perm", 1}},
      {{"enemy_vis", 0}},
      {{"num_destr", 1}});

  goap::add_action_to_planner(pl, "destroy_operator", 1,
      {{"has_operator", 1}},
      {{"has_operator", 0}},
      {});

  goap::add_action_to_planner(pl, "destroy_comms", 1,
      {{"has_comms", 1}},
      {{"has_comms", 0}},
      {});

  goap::add_action_to_planner(pl, "destroy_no_comms", 1,
      {{"enemy_vis", 1}, {"has_comms", 0}},
      {{"enemy_vis", 0}},
      {{"num_destr", 1}});

  goap::add_action_to_planner(pl, "destroy_no_operator", 1,
      {{"enemy_vis", 1}, {"has_operator", 0}},
      {{"enemy_vis", 0}},
      {{"num_destr", 1}});

  // INITIAL STATE
  goap::WorldState ws = goap::produce_planner_worldstate(pl,
      {{"enemy_vis", 0},
       {"has_comms", 1},
       {"has_operator", 1},
       {"perm_req", 0},
       {"has_perm", 0},
       {"num_destr", 0}});

  // TARGET STATE
  goap::WorldState goal = goap::produce_planner_worldstate(pl,
      {{"num_destr", 5}});

  std::vector<goap::PlanStep> plan;
  goap::make_plan(pl, ws, goal, plan);
  goap::print_plan(pl, ws, plan);
}


int main(int /*argc*/, const char ** /*argv*/)
{
  debug_hunter_planner();

  return 0;
}

