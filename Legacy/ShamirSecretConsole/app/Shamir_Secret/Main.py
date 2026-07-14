from pathlib import Path

from matplotlib import pyplot as plt


def read_series(filename: Path) -> list[list[float]]:
    with filename.open(encoding="utf-8") as source:
        return [[float(value) for value in line.split()] for line in source if line.strip()]


def plot_series(matrix: list[list[float]], title: str) -> None:
    if len(matrix) % 2 != 0:
        raise ValueError("data.txt must contain alternating X and Y rows")

    plt.figure()
    for index in range(0, len(matrix), 2):
        x_values = matrix[index]
        y_values = matrix[index + 1]
        if len(x_values) != len(y_values):
            raise ValueError(f"series {index // 2} has different X and Y lengths")
        plt.plot(x_values, y_values, label=f"Polynomial {index // 2}")

    plt.title(title)
    plt.legend()


if __name__ == "__main__":
    plot_series(read_series(Path("data.txt")), "Shamir polynomial candidates")
    plt.show()
