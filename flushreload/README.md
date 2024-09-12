# Flush & Reload

Here are some test that we made when we discover and learn flush & reload.

## Calibration

First, you should find your threshold by compiling and executing the binary in the calibration directory (from https://github.com/nepoche/Flush-Reload). Then, use the adapted threshold for the macro definition in the fr.c you are using.

## Normal

Here we just try a simple example on a function of a shared library. To use it :

```bash
make all
export LD_LIBRARY_PATH="./"

# attacker terminal
./spy.out

# victim terminal
./victim.out
```

The spy should stop when it detects a flush and reload. 

## RSA

Here we tried to implement the exponent detection of the RSA algorithm, but we didn't manage to do it because our function were on the same cache entry so the flush and reload was not accurate. We didn't correct the bug at this moment and moved forward on the GDS attack.