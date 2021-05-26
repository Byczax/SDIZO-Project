import matplotlib.pyplot as plt
import os
import statistics

results = []


def read_text_file(filepath):
    with open(filepath, 'r') as txt_file:
        counter = 0
        number = 1
        graph_list = []
        graph_matrix = []
        round_values = []
        for line in txt_file:
            counter += 1
            splitted = line.split(",")
            graph_list.append(int(splitted[2])/1000)
            graph_matrix.append(int(splitted[3])/1000)
            if counter == 100:
                g_list = [round(q, 1) for q in statistics.quantiles(graph_list, n=10)]
                g_matrix = [round(q, 1) for q in statistics.quantiles(graph_matrix, n=10)]
                g_list_mean = statistics.mean(g_list)
                g_matrix_mean = statistics.mean(g_matrix)
                round_values.append(
                    [int(splitted[0]), int(splitted[1]), g_list_mean, g_matrix_mean])

                # print("|" +
                #       str(number) + "|" +
                #       str(splitted[0]) + "|" +
                #       str(splitted[1]) + "%|" +
                #       str(int(g_list_mean)) + "|" +
                #       str(int(g_matrix_mean)) + "|")
                number += 1
                graph_list.clear()
                graph_matrix.clear()
                counter = 0
    results.append([filepath.split(".")[0], round_values])


def draw_graph_density(data, graph_name, first_name, second_name, density):
    color_packs = [["gray", "maroon", "red", "silver"], ["darkblue", "sienna", "teal", "crimson"]]
    plt.rcParams.update({'font.size': 20})
    plt.figure(num=None, figsize=(20, 8), dpi=400, facecolor='w', edgecolor='k')

    result = calculate_data_density(data[0][1], 2, density)
    add_to_plot(result[0], result[1], color_packs[0][0], first_name + "-Lista")
    result = calculate_data_density(data[0][1], 3, 25)
    add_to_plot(result[0], result[1], color_packs[0][1], first_name + "-Macierz")
    result = calculate_data_density(data[1][1], 2, 25)
    add_to_plot(result[0], result[1], color_packs[0][2], second_name + "-Lista")
    result = calculate_data_density(data[1][1], 3, 25)
    add_to_plot(result[0], result[1], color_packs[0][3], second_name + "-Macierz")

    plt.title(graph_name + "-" + str(density) + "%")
    plt.margins(x=None, y=None, tight=True)
    plt.legend(loc="upper left")
    plt.ylabel("Time [μs]")
    plt.xlabel("Element quantity")
    plt.grid(True, color="lightgrey", alpha=0.5)
    os.chdir("../pictures")
    save_path = graph_name + "-" + str(density) + ".png"
    plt.savefig(save_path)  # save plot to file
    plt.show()  # show plots in IDE


def draw_graph(data, graph_name, first_name, second_name, type_name, select):
    plt.rcParams.update({'font.size': 20})
    plt.figure(num=None, figsize=(20, 8), dpi=400, facecolor='w', edgecolor='k')

    result = calculate_data(data[1][1], select)
    plot_data(result, first_name, 0)

    # result = calculate_data(data[1][1], 3)
    # plot_data(result, first_name, 0)

    result = calculate_data(data[0][1], select)
    plot_data(result, second_name, 1)

    # result = calculate_data(data[0][1], 3)
    # plot_data(result, second_name, 1)

    plt.title(graph_name + "-" + type_name)
    plt.margins(x=None, y=None, tight=True)
    plt.legend(loc="upper left")
    plt.ylabel("Time [μs]")
    plt.xlabel("Element quantity")
    plt.grid(True, color="lightgrey", alpha=0.5)
    os.chdir("../pictures")
    save_path = graph_name + "-" + type_name + ".png"
    plt.savefig(save_path)  # save plot to file
    plt.show()  # show plots in IDE


def calculate_data_density(data, select, density):
    result = [[], []]
    for elements in data:
        if elements[1] == density:
            result[0].append(elements[0])
            result[1].append(elements[select])
    return result


def calculate_data(data, select):
    result = [[], [], [], [], []]
    for elements in data:
        if elements[1] == 25:
            result[4].append(elements[0])
            result[0].append((elements[select]))
        elif elements[1] == 50:
            result[1].append((elements[select]))
        elif elements[1] == 75:
            result[2].append((elements[select]))
        elif elements[1] == 99:
            result[3].append((elements[select]))
    return result


def plot_data(data, name, pack_number):
    color_packs = [["gray", "maroon", "red", "silver"], ["darkblue", "sienna", "teal", "crimson"]]
    add_to_plot(data[4], data[0], color_packs[pack_number][0], name + " 25%")
    add_to_plot(data[4], data[1], color_packs[pack_number][1], name + " 50%")
    add_to_plot(data[4], data[2], color_packs[pack_number][2], name + " 75%")
    add_to_plot(data[4], data[3], color_packs[pack_number][3], name + " 99%")


def add_to_plot(data_x, data_y, color, name):
    plt.plot(data_x, data_y, marker='o', linestyle='-', color=color,
             linewidth=2, markersize=10, label=name)


def main():
    path = "results"
    os.chdir(path)
    for file in os.listdir():
        if file.endswith(".txt"):
            # print(file)
            read_text_file(file)
    # for result in results:
    #     print(result)
    draw_graph([results[3], results[2]], "Graph MST", "Prim", "Kruskal", "Macierz", 3)
    draw_graph([results[3], results[2]], "Graph MST", "Prim", "Kruskal", "Lista", 2)
    draw_graph([results[1], results[0]], "Graph SPF", "Dijkstra", "Bellman-Ford", "Macierz", 3)
    draw_graph([results[1], results[0]], "Graph SPF", "Dijkstra", "Bellman-Ford", "Lista", 2)
    draw_graph_density([results[3], results[2]], "Graph MST", "Prim", "Kruskal", 25)
    draw_graph_density([results[3], results[2]], "Graph MST", "Prim", "Kruskal", 50)
    draw_graph_density([results[3], results[2]], "Graph MST", "Prim", "Kruskal", 75)
    draw_graph_density([results[3], results[2]], "Graph MST", "Prim", "Kruskal", 99)

    draw_graph_density([results[1], results[0]], "Graph SPF", "Dijkstra", "Bellman-Ford", 25)
    draw_graph_density([results[1], results[0]], "Graph SPF", "Dijkstra", "Bellman-Ford", 50)
    draw_graph_density([results[1], results[0]], "Graph SPF", "Dijkstra", "Bellman-Ford", 75)
    draw_graph_density([results[1], results[0]], "Graph SPF", "Dijkstra", "Bellman-Ford", 99)


if __name__ == '__main__':
    main()
