/*-----------------------------------------------------------------------------
 * Umicom Kitchen Designer Module
 * File: src/workspace.c
 *
 * PURPOSE:
 *   Project canonical Framework layouts and next-feature planning through the thin application boundary.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/kitchen_designer/workspace.h"

#include "umicom/kitchen_designer/application.h"
#include "umicom/application/experience_plan.h"

/*
 * Return the number of records represented by kitchen designer workspace layout without
 * changing their state.
 */
size_t umi_kitchen_designer_workspace_layout_count(void)
{
    const UmiApplicationExperienceDefinition *definition =
        umi_kitchen_designer_application_experience();
    return definition != NULL ? definition->layout_count : 0U;
}

/*
 * Find kitchen designer workspace layout while leaving the underlying catalogue or model
 * owned by this module.
 */
const UmiExperienceLayoutDefinition *umi_kitchen_designer_workspace_layout_at(
    size_t index)
{
    const UmiApplicationExperienceDefinition *definition =
        umi_kitchen_designer_application_experience();
    return definition != NULL && index < definition->layout_count
        ? &definition->layouts[index] : NULL;
}

/*
 * Provide the kitchen designer workspace default operation used by this module and its
 * client applications.
 */
const UmiExperienceLayoutDefinition *umi_kitchen_designer_workspace_default(void)
{
    const UmiApplicationExperienceDefinition *definition =
        umi_kitchen_designer_application_experience();
    return definition != NULL
        ? umi_application_experience_layout_find(
            definition, definition->default_layout_id)
        : NULL;
}

/*
 * Provide the kitchen designer workspace next feature operation used by this module and
 * its client applications.
 */
const UmiExperienceFeatureDefinition *umi_kitchen_designer_workspace_next_feature(
    void)
{
    return umi_application_experience_next_feature(
        umi_kitchen_designer_application_experience());
}
