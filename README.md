# Resistor Color Code Calculator

This is a command-line tool to calculate the resistance value of a resistor based on its color bands. It supports both 4-band and 5-band resistors.

## Getting Started

### Prerequisites

- GCC (GNU Compiler Collection)
- `make` utility

### Building the Project

To build the project, clone the repository and run `make` in the project directory:

```sh
git clone https://github.com/sid115/rccc.git
cd rccc
make
```

### Installing

To install the executable to a directory in your system's PATH (e.g., `/usr/local/bin` on Linux or MacOS), use:

```sh
sudo make install
```

For Windows, the executable will be installed in `C:\Program Files\rccc`:

```sh
make install
```

### Usage

The program accepts either 4 or 5 color bands as arguments.

#### 4-Band Resistor

```sh
./rccc <color1> <color2> <multiplier> <tolerance>
```

Example:

```sh
./rccc red violet yellow gold
```

Output:

```plaintext
Resistance: 270000 Ω ±5.00%
```

#### 5-Band Resistor

```sh
./rccc <color1> <color2> <color3> <multiplier> <tolerance>
```

Example:

```sh
./rccc brown black black red brown
```

Output:

```plaintext
Resistance: 10000 Ω ±1.00%
```

### Cleaning Up

To remove the built executable:

```sh
make clean
```

## Contributing

Contributions are welcome! Please fork the repository and create a pull request.

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/your-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin feature/your-feature`)
5. Create a new Pull Request
