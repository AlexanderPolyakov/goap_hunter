//
#include <algorithm>
#include "goapPlanner.h"

static void debug_hunter_planner()
{
  goap::Planner pl = goap::create_planner();

  goap::add_states_to_planner(pl,
      {"enemy_vis",
       "has_comms",
       "has_operator",
       "perm_req",
       "num_destr"});

  goap::add_action_to_planner(pl, "patrol", 1,
      {{"enemy_vis", 0}},
      {{"enemy_vis", 1}},
      {});

  goap::add_action_to_planner(pl, "req_permission", 1,
      {{"enemy_vis", 1}, {"has_comms", 1}, {"has_operator", 1}},
      {{"enemy_vis", 1}},
      {});

  /*
  goap::add_action_to_planner(pl, "open_room", 1,
      {{"health_state", Healthy}},
      {{"enemy_vis", 1}, {"loot_vis", 1}, {"enemy_dist", 2}},
      {});

  goap::add_action_to_planner(pl, "loot", 1,
      {{"health_state", Healthy}, {"loot_vis", 1}, {"enemy_vis", 0}},
      {{"loot_vis", 0}},
      {{"num_loot", +1}});

  goap::add_action_to_planner(pl, "approach_enemy", 1,
      {{"health_state", Healthy}, {"enemy_vis", 1}},
      {},
      {{"enemy_dist", -1}});

  goap::add_action_to_planner(pl, "flee_enemy", 1,
      {{"health_state", Healthy}, {"enemy_vis", 1}},
      {},
      {{"enemy_dist", +1}});

  goap::add_action_to_planner(pl, "find_melee", 1,
      {{"have_melee", 0}, {"health_state", Healthy}},
      {{"have_melee", 1}},
      {});

  goap::add_action_to_planner(pl, "find_ranged", 1,
      {{"have_ranged", 0}, {"health_state", Healthy}},
      {{"have_ranged", 1}},
      {});

  goap::add_action_to_planner(pl, "patch_up", 1,
      {{"health_state", Injured}},
      {},
      {{"health_state", +1}});

  goap::add_action_to_planner(pl, "attack_enemy", 1,
      {{"enemy_vis", 1}, {"have_melee", 1}, {"enemy_dist", DistMelee}, {"health_state", Healthy}},
      {{"enemy_vis", 0}},
      {{"health_state", -1}});

  goap::add_action_to_planner(pl, "shoot_enemy", 5,
      {{"enemy_vis", 1}, {"have_ranged", 1}, {"enemy_dist", DistRanged}, {"health_state", Healthy}},
      {{"enemy_vis", 0}},
      {{"health_state", -1}});

  goap::add_action_to_planner(pl, "escape", 1,
      {{"health_state", Healthy}, {"num_loot", 5}},
      {{"escaped", 1}},
      {});
      */

  goap::WorldState ws = goap::produce_planner_worldstate(pl,
      {{"enemy_vis", 0},
       {"has_comms", 1},
       {"has_operator", 0},
       {"perm_req", 0},
       {"num_destr", 0}});

  goap::WorldState goal = goap::produce_planner_worldstate(pl,
      {{"num_destr", 5}});

  std::vector<goap::PlanStep> plan;
  goap::make_plan(pl, ws, goal, plan);
  goap::print_plan(pl, ws, plan);
}


int main(int /*argc*/, const char ** /*argv*/)
{
  debug_looter_planner();

  return 0;
}

