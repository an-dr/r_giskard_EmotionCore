# The Emotion Core

Part of the [R.Giskard project](https://github.com/an-dr/r_giskard)

The aim of this library is to implement an emotion model that could be used by other applications implementing a behavior modifications (emotions) based on changing of input data.

## Structure

The core consists of:

- Input Data Descriptors - describes data from sensors and how it should affect the core
- Emotional States Descriptors - named states of the core described by specific values of core parameters.
- Sensor values
- Parameters: base, temporary, sensorial (calculated from values and input data descriptors) and total (a sum of others)

Detailed structure:

<img src="docs/pics/EmotionCore_ops.svg" width="550">

## Example of data

Example of core parameters:

```json
[   "cortisol",
    "dopamine",
    "adrenaline",
    "serotonin" ]
```

Example of a core's Emotional state:

```json
{
    "name": "happiness",
    "conditions": [
            {
                "param":  "cortisol",
                "op":     LESS_THAN,
                "value":  10
            },
            {
                "param":  "serotonin",
                "op":     GREATER_THAN,
                "value":  100
            }
        ]
}
```

Example of input data descriptor:

```json
{
    "sensor_name": "temperature sensor",
    "val_min": 0,
    "val_max": 255,
    "weights": [
        {
            "core_param_name": "serotonin",
            "weight": 0.5
        },
        {
            "core_param_name": "cortisol",
            "weight": -0.5
        }
    ]
}
```

Input data example:

```json
{
    "sensor_name": "temperature sensor",
    "value": 120
}
```

Temporary impact example (say, something like a "bad thought"):

```json
{
    "change_per_sec" : 5,
    "param_name" : "cortisol",
    "delta_value" : 50
}
```

## Writing new data

When you write the data, the core does the following:

- updates saved sensor value
- updates core parameter: param += (new_sens_val - old_sens_val) * weight
- updates the current core state based on updated parameters
