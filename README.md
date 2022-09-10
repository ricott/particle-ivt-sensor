# Virtual IVT temperature sensor using OHMIGO
A virtual temperature sensor for a IVT heatpump.
Built using and [OHMIGO TTL](https://www.ohmigo.io/en) using a [Particle Photon](https://particle.io).

## Hardware connections
* Photon Vcc -> OHMIGO Vcc
* Photon GND -> OHMIGO GND
* Photon Serial1 RX -> OHMIGO TxData
* Photon Serial1 TX -> OHMIGO RxData
* OHMIGO Rout -> IVT
* OHMIGO GND -> IVT Gnd