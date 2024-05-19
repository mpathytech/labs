* Program for parsing command line options using argp

* Compile the code using gcc
```bash
# On Linux
gcc argp_simple.c -o argp_simple

# On Mac
brew install argp-standalone
gcc -I /opt/homebrew/include -L /opt/homebrew/lib -largp argp_simple.c -o argp_simple
```

* Run examples using the run.sh script
```bash
./run.sh
```
