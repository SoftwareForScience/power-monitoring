import sendRequest
import time


ip_path = 'C:/Users/Brendan van Walstijn/Documents/Power Monitoring/IPaddresses.txt'
data_path = "C:/Users/Brendan van Walstijn/Documents/Power Monitoring/SavedData.txt"
open(data_path, 'w').close()
# graph = plt.plot([],[])


def call_pi():
    # send get request to pi's
    sendRequest.get_request('http://192.168.1.10:8000/graph')
    # visualize the data

    # call function again
    time.sleep(0.125)
    call_pi()


# def update_plot():
#    open(data_path, 'r')

#    graph.set_xdata(numpy.append(graph.get_xdata(), new_data))
#    graph.set_ydata(numpy.append(graph.get_ydata(), new_data))
#    plt.draw()


call_pi()