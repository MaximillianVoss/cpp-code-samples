from matplotlib import pyplot as plt


def GetMatrix(filename):
    matrix = []
    try:
        file = open(filename)
        for line in file:
            matrix.append([float(x) for x in line.split()])
    except FileNotFoundError:
        print("file {0} not found!".format(filename))
    for i in range(0, len(matrix)):
        for j in range(0, len(matrix[i])):
            matrix[i][j] = float(matrix[i][j])
    return matrix


# матрица со значениями по две строки: значения первая строка: X и вторая строка: Y
def GetChart(matrix, scale, title):
    plt.figure()
    for i in range(0, len(matrix) - 1, 2):
        plt.plot(range(0, len(matrix[i]) * scale, scale), matrix[i + 1], label="График {0}".format(i / 2))
    plt.title(title)
    plt.legend()


GetChart(GetMatrix("data.txt"), 1, "lol")
plt.show()
