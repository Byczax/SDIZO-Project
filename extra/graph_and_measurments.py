import matplotlib.pyplot as plt
import statistics
import os


def read_text_file(filepath):
    with open(filepath, 'r') as txt_file:
        my_list = [tuple(map(float, i.split(','))) for i in txt_file]
        graph_name = txt_file.name.split("\\")[7].split(".")[0]
        list_quantity = []
        list_time = []
        for par in my_list:
            list_quantity.append(par[0])
            list_time.append(par[1])
        list_time = [round(q, 1) for q in statistics.quantiles(list_time, n=10)]
        list_quantity = [round(q, 1) for q in statistics.quantiles(list_quantity, n=10)]
        pars = []
        for i in range(0, 9):
            pars.append([list_quantity[i], list_time[i]])
        draw_graph([list_quantity, list_time], graph_name)


def draw_graph(data, graph_name):
    plt.rcParams.update({'font.size': 20})
    plt.figure(num=None, figsize=(20, 8), dpi=400, facecolor='w', edgecolor='k')
    plt.plot(data[0], data[1], marker='o', linestyle='--', color='limegreen',
             label='Square', linewidth=4, markersize=16)
    plt.title(graph_name)
    plt.margins(x=None, y=None, tight=True)
    plt.ylabel("Time [ns]")
    plt.xlabel("Element quantity")
    plt.grid(True, color="lightgrey", alpha=0.5)
    save_path = graph_name + ".png"
    plt.savefig(save_path)  # save plot to file
    plt.show()  # show plots in IDE


if __name__ == '__main__':
    # folder_path = ["array", "doubleList"]
    folder_path = ["binaryHeap", "RBTree", "AVLTree"]
    for folder in folder_path:
        path = "D:\\Documents\\Programming\\Projects\\pythonTesting\\results\\" + folder
        os.chdir(path)
        for file in os.listdir():
            if file.endswith(".txt"):
                file_path = f"{path}\{file}"
                read_text_file(file_path)
