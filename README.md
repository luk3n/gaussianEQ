# gaussianEQ
This small program solves systems of linear equations using Gauss-Jordan elimination algorithm.

Supported dimensions are: 2x2, 3x3, 4x4 and 5x5.

### Building the source
```
make
```

### Install/uninstall
```
make install
```
```
make uninstall
```

### Usage
```gaussianeq -d <dimension> -v <values>```

Example:
```
gaussianeq -d 2x2 -v 10 4 62 3 5 30
```

Once the matrix has been processed, the output will contain all the results along with the solutions of the entered system, separating each value with a semicolon.