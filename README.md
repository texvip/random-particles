## Simulator for randomly placed particles in 2D

### Description

* Obtain the distribution of the local particle density.

### Usage

```bash
  ./main.out <number of system divisions> <number of particles> <number of trials>
```

This program takes three command-line arguments.
The first argument sets the division number of the system.
If we set the value *N*, the system is divided into *N*<sup>2</sup> subsystems.
The second argument sets the number of particles.
The third argument sets the number of trials to place particles.

The program output the distribution of the local particle density, i.e. the distribution of the number of particles in each subsystem.
