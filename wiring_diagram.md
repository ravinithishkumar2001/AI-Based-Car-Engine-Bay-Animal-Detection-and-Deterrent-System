# Wiring and safety

| Function | DFR1154 | External connection |
|---|---:|---|
| Ultrasonic enable | GPIO43 | 1 kΩ gate resistor to logic-level MOSFET/generator EN; 100 kΩ gate pulldown |
| Audio | onboard MAX98357/SPK | 4 Ω 1.5 W or 8 Ω 1 W speaker |
| Temperature | disabled by default | fit a protected divider/thermistor and set `TEMPERATURE_ADC_GPIO` only after validation |

The external ultrasonic generator must generate its own carrier. GPIO43 is only an enable signal. Add automotive fuse, reverse-polarity protection, TVS/transient suppression, thermal cutoff and a hardware normally-off inhibit. Never connect vehicle 12 V to a GPIO. Keep electronics clear of belts, fans, exhaust, hot surfaces and water.

