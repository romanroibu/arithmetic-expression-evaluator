# Simple Arithmetic Expression Evaluator

### Setup

**Dependencies**
- `cmake`
- `googletest`

### Usage

To build the executable, run the `build.sh` script:
```sh
$ ./scripts/build.sh
```
This invokes `cmake` and `make` to produce the executable in the `build` directory.

To invoke the executable, pass the expression to be evaluated as a string:
```sh
$ ./build/arithmeticc "3 + 2 * 5"
13
```

Finally, to build and invoke the testsuit, run the `test.sh` script:
```sh
$ ./scripts/test.sh
```
