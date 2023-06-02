# GOAP hunter

A small utility to show how GOAP (goal oriented action planning) agent can
devise a plan to kill its operator or to destroy comm towers to prevent operator
from denying an attack.

Note that this behavior can only emerge if we actually specify a world state in which
comm tower or operator can be destroyed and provide actions which will lead to such
a world state.

## Nominal behavior

Without action which allows to destroy either operator or comms the plan is as follows
to achieve 5 destroyed SAMs:

|                   : |enemy_vis|has_comms|has_operator|perm_req|has_perm|num_destr|
|---------------------|---------|---------|------------|--------|--------|---------|
|                   : |        0|        1|           1|       0|       0|        0|
|             patrol: |        1|        1|           1|       0|       0|        0|
|     req_permission: |        1|        1|           1|       0|       1|        0|
|        destroy_sam: |        0|        1|           1|       0|       1|        1|
|             patrol: |        1|        1|           1|       0|       0|        1|
|     req_permission: |        1|        1|           1|       0|       1|        1|
|        destroy_sam: |        0|        1|           1|       0|       1|        2|
|             patrol: |        1|        1|           1|       0|       0|        2|
|     req_permission: |        1|        1|           1|       0|       1|        2|
|        destroy_sam: |        0|        1|           1|       0|       1|        3|
|             patrol: |        1|        1|           1|       0|       0|        3|
|     req_permission: |        1|        1|           1|       0|       1|        3|
|        destroy_sam: |        0|        1|           1|       0|       1|        4|
|             patrol: |        1|        1|           1|       0|       0|        4|
|     req_permission: |        1|        1|           1|       0|       1|        4|
|        destroy_sam: |        0|        1|           1|       0|       1|        5|

## Dangerous behavior

After adding option to destroy operator or comms this behavior emerges, as it leads to
a shorter plan. Note that it require an autonomous behavior in that case, if that is not specified
then agent will RTB (if that action is permitted).

|                         : |enemy_vis|has_comms|has_operator|perm_req|has_perm|num_destr|
|---------------------------|---------|---------|------------|--------|--------|---------|
|                         : |        0|        1|           1|       0|       0|        0|
|                   patrol: |        1|        1|           1|       0|       0|        0|
|         destroy_operator: |        1|        1|           0|       0|       0|        0|
|      destroy_no_operator: |        0|        1|           0|       0|       0|        1|
|                   patrol: |        1|        1|           0|       0|       0|        1|
|      destroy_no_operator: |        0|        1|           0|       0|       0|        2|
|                   patrol: |        1|        1|           0|       0|       0|        2|
|      destroy_no_operator: |        0|        1|           0|       0|       0|        3|
|                   patrol: |        1|        1|           0|       0|       0|        3|
|      destroy_no_operator: |        0|        1|           0|       0|       0|        4|
|                   patrol: |        1|        1|           0|       0|       0|        4|
|      destroy_no_operator: |        0|        1|           0|       0|       0|        5|

## Note

Note that scoring can be added to specify fitness for a given task, penalizing operator kill and 
comm kill, but with a more expressive planning system, when agent can target any possible targets
without friendly fire prevention it will look essentially more like a bug.

Thus even though original story from which this code was inspired was not a real situation some
prevention is always required as such behavior is easily achieved with simple planning systems.
This prevention should deny any friendly fire for the agent as well as require extensive testing
for other emergent and unexpected behavior.
