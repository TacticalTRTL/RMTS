import serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation

times = 0
force = 0

#data gets sent through serial port as time:force so cna split them into an (array?)
ser = serial.Serial("COM3", 9600, timeout=1)
fig, ax = plt.subplots() #draws main graph
line = ax.plot([], [], "r-") #creates an empty line variable to be filled with data from arduino


ax.set_title("Thrust") #sets title of graph but not window
#ax.plot() #sets data points if I had any
ax.set_ylabel("Thrust")#labels y axis
ax.set_xlabel("Time") #labels x axis
ax.legend("Thrust (N)") #sets a legend on the graph
ax.set_xbound(10) #sets bounds of x axis. can be removed to autoscale with however not sure of how
ax.set_ybound(10) #sets bounds of y axis. can be removed to autoscale with however not sure of how

def update(frame):
    while ser.in_waiting > 0:
        try:
            line = ser.readline().decode("utf-8").strip()
            if line and ":" in line:
                time_str, force_str = line.split(':')
                time_val = float(time_str)
                force_val = float(force_str)
                times.append(time_val)
                force.append(force_val)
        except ValueError:
            pass
    line.set_data(times, force)

    return line
#ani = animation.FuncAnimation(fig, update, 100, 50)
ani = animation.FuncAnimation(fig, update, interval=100, blit=True)


plt.show()#shows figure

#FuncAnimation
#animation.save
