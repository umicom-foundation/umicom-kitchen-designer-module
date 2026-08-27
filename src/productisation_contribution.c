/*-----------------------------------------------------------------------------
 * Umicom Kitchen Designer Module
 * File: src/productisation_contribution.c
 *
 * PURPOSE:
 *   Bind product identity and executable evidence to canonical Framework
 *   application definitions without copying shared implementation.
 *
 * Created by: Sammy Hegab
 * Organisation: Umicom Foundation
 * Licence: MIT
 *---------------------------------------------------------------------------*/
#include "umicom/kitchen/productisation_contribution.h"

static const UmiProductApplicationAdoption ADOPTION = {
    sizeof(UmiProductApplicationAdoption),
    "kitchen",
    "org.umicom.kitchen-designer",
    "Umicom Kitchen Designer",
    "umicom-kitchen-console",
    UMI_PRODUCT_FRONTEND_CONSOLE,
    1,
    1,
    1,
    1
};

const UmiProductApplicationAdoption *
umi_kitchen_productisation_contribution(void)
{
    return &ADOPTION;
}

UmiStatus umi_kitchen_productisation_snapshot(
    UmiProductApplicationAdoptionSnapshot *out_snapshot)
{
    return umi_product_application_adoption_snapshot(
        &ADOPTION, out_snapshot);
}
