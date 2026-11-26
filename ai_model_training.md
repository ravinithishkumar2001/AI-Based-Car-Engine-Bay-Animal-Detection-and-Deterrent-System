# Edge Impulse model

Create five image classes: `rat`, `mouse`, `squirrel`, `insect`, `background`. Capture from the installed camera position in daylight, darkness/IR, shadows, partial views, engine components, empty bays and motion blur. Split by capture session to prevent near-duplicate leakage.

Use an image block with consistent resize/crop. Train an INT8-compatible classifier and export an Arduino library/TFLite Micro model without EON Compiler. Place the generated library under `lib/AnimalModel/`, then replace `classifyAnimal()` with the generated `run_classifier()` adapter and an image callback that converts each captured image to the model's expected RGB input. DFRobot documents this Edge Impulse flow in its DFR1154 examples.

The placeholder returns `UNKNOWN`; never lower the confidence threshold to force triggering. Validate on held-out engine-bay images and retain repeated detection filtering.

