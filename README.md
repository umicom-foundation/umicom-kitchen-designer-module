# umicom-kitchen-designer-module
Thin C23 Umicom Kitchen Designer application composition over Umicom Framework

## Review linked context values

Kitchen Designer exposes Framework's reviewed context changes through
`umi_kitchen_designer_workspace_context_review`, `umi_kitchen_designer_workspace_context_apply`
and `umi_kitchen_designer_workspace_clear_context` in
`umicom/kitchen_designer/workspace_commands.h`. A context group is a named value that
related panels can share; for example, a host could use `design.room` with the sample
value `sample-kitchen`. The host must connect that name to its panel consumers.

1. Use a runtime initialised with this product's canonical experience. Prepare
   the requested changes with the review function; preparation changes no live state.
2. Display the copied Framework summary and rows. Keep the runtime and its
   workbench alive while the user reviews the proposed values. If the summary
   reports UI differences, show the captured UI value beside the cached value.
3. Apply only after acceptance, then destroy the review. If the workspace changed,
   prepare a fresh review. Cancelling only destroys the review.

This is a module API; native review screens are separate host work. Context edits
do not execute product commands or external operations. The shared guide at
`framework/docs/guides/REVIEWING_LINKED_CONTEXTS.html` in the Applications checkout
explains capacity, ownership, thread coordination and recovery in more detail.

Keep room photographs, measurements and supplier documents together. The **Creative workbench → Asset library** page imports complete files, reorders them, saves and reopens a portable collection, and exports selected assets. It is separate from the scene project and never uploads files. See the [shared asset library guide](../../framework/docs/learning/creative-asset-libraries.html) for limits, save steps and recovery.
