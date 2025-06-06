# How to contribute to this project?

[DataTome Docs](https://alexandrehiroyuki.github.io/DataTomeDocs/)

## Reporting issues

Open an issue on the repository and provide the following information:

1. What version of the library are you using?
2. What board and/or framework are you using?
3. How can the issue be reproduced? Provide a minimal code snippet that reproduces the issue if possible.

## Code Convention

- Don't include C++ standard library functions, because it does not compile for AVR boards (C std libs still works).

- **Note:** All commits and pull requests must follow the [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/). Please ensure your messages are properly formatted.

## Testing

The library comes with a set of automated tests. Contributions should include tests to cover the new functionality and ensure that no regressions are introduced.

To run the tests on all configured environments, run:

```bash
$ pio test
```

To test the library on a desktop machine, use the `desktop` environment:

```bash
$ pio test -e desktop
```

If you wish to test the library on a specific board, configure the environment in `platformio.ini` and run the tests:

```bash
$ pio test -e <environment>
```

## Publish Package on PlatformIO Registry

```bash
pio pkg publish
```
