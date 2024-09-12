
# GDS

## Are you vulnerable?

Launch the command 

```bash
lscpu
```

And check if you are vulnerable to GDS in the vulnerability section.

```bash
Vulnerabilities:         
  Gather data sampling:  Vulnerable
```

The mitigation can be disabled by setting “gather_data_sampling=off” or “mitigations=off” on the kernel command line.
Not specifying either will default to the mitigation being enabled. Specifying “gather_data_sampling=force” will use the microcode mitigation when available or disable AVX on affected systems where the microcode hasn’t been updated to include the mitigation.

## Compilation

```bash
make all
```

## Usage

On the attacker terminal:

```bash
taskset -c 5 ./gds
```

On the victim terminal:

```bash
taskset -c 5 ./victim
```

If 5 doesn't work, try a lower value.

On the attacker terminal:
Then, Press ^C once you have enough 'Incrementing...' printed to see the dumped bytes.
