import serial
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np


ser = serial.Serial("COM8", 115200, timeout=0.1)         # 1/timeout is the frequency at which the port is read
pwm = 55
vals = []
pwmdf = {}

plt.figure(figsize=(100,100))

while int(pwm)<= 255:
    data = ser.readline().decode().strip()
    if data:
        # print(data)
        if data.startswith('pwm:'):
            print(data)
            pwm = data.strip('pwm:')
            pwmdf[pwm] = pd.DataFrame(vals , columns = ['t','vel'], dtype = 'float')
            l = str(int(pwm)*12.45/255)+'v'
            plt.plot(pwmdf[pwm].t , pwmdf[pwm].vel, label = l )
            vals = []

            continue
        dataList = data.split('\t')
        print(dataList)
        vals.append(dataList)
plt.yticks(np.arange(0,3,0.1))
# plt.xticks(np.arange(0,40000,500), rotation = 90)
plt.grid()

plt.legend()
plt.show()

            
        


